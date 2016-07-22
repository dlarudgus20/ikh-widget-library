// Copyright (c) 2014, Im Kyeong-Hyeon
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
// * Redistributions of source code must retain the above copyright notice, this
//   list of conditions and the following disclaimer.
//
// * Redistributions in binary form must reproduce the above copyright notice,
//   this list of conditions and the following disclaimer in the documentation
//   and/or other materials provided with the distribution.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
// FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
// DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
// SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
// CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
// OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#ifndef IWL_EVENT_HPP_
#define IWL_EVENT_HPP_

#include "defines.hpp"

BEGIN_IWL()

template <typename Owner, typename F> class event;
template <typename F> class event_slot;

template <typename Owner, typename ...Args>
class event<Owner, void(Args...)> final : private boost::noncopyable
{
    friend Owner;
public:
    typedef void fn_type(Args...);
    typedef std::function<fn_type> fn_obj_type;

private:
    std::vector<fn_obj_type> _m_lst_fn_fixed;
    std::vector<std::weak_ptr<fn_obj_type> > _m_lst_fn_removable;

public:
    event() = default;
    event(event&& other)
        : _m_lst_fn_fixed(std::move(other._m_lst_fn_fixed))
        , _m_lst_fn_removable(std::move(other._m_lst_fn_removable))
    {
    }
    template <typename O>
    event(event<O, void(Args...)>&& other)
        : _m_lst_fn_fixed(std::move(other._m_lst_fn_fixed))
        , _m_lst_fn_removable(std::move(other._m_lst_fn_removable))
    {
    }
    event& operator =(event&& other)
    {
        _m_lst_fn_fixed = std::move(other._m_lst_fn_fixed);
        _m_lst_fn_removable = std::move(other._m_lst_fn_removable);
        return *this;
    }
    template <typename O>
    event& operator =(event<O, void(Args...)>&& other)
    {
        _m_lst_fn_fixed = std::move(other._m_lst_fn_fixed);
        _m_lst_fn_removable = std::move(other._m_lst_fn_removable);
        return *this;
    }
    void swap(event& other) noexcept
    {
        _m_lst_fn_fixed.swap(other._m_lst_fn_fixed);
        _m_lst_fn_removable.swap(other._m_lst_fn_removable);
    }
    template <typename O>
    void swap(event<O, void(Args...)>& other) noexcept
    {
        _m_lst_fn_fixed.swap(other._m_lst_fn_fixed);
        _m_lst_fn_removable.swap(other._m_lst_fn_removable);
    }

    template <typename F, typename = std::enable_if<
        std::is_convertible<std::remove_reference_t<F>, fn_obj_type>::value
        >>
    event& operator +=(F&& fn)
    {
        _m_lst_fn_fixed.emplace_back(
            std::forward<F>(fn));
        return *this;
    }

    event& operator +=(event_slot<void(Args...)>& efp);
    event& operator -=(event_slot<void(Args...)>& efp);

    void clear()
    {
        _m_lst_fn_fixed.clear();
        _m_lst_fn_removable.clear();
    }

    bool empty() const
    {
        return _m_lst_fn_fixed.empty() && _m_lst_fn_removable.empty();
    }

private:
    template <typename ...Args2>
    void fire(Args2&&... args)
    {
        _m_lst_fn_removable.erase(
            std::remove_if(_m_lst_fn_removable.begin(), _m_lst_fn_removable.end(),
                [](const std::weak_ptr<fn_obj_type>& item) { return item.expired(); }),
            _m_lst_fn_removable.end());

        for (const fn_obj_type& fn : _m_lst_fn_fixed)
        {
            fn(std::forward<Args2>(args)...);
        }
        for (const std::weak_ptr<fn_obj_type>& fn : _m_lst_fn_removable)
        {
            auto sptr = fn.lock();
            assert(sptr);
            (*sptr.get())(std::forward<Args2>(args)...);
        }
    }
};

template <typename ...Args>
class event_slot<void(Args...)>
{
public:
    typedef void fn_type(Args...);
    typedef std::function<fn_type> fn_obj_type;

private:
    std::shared_ptr<fn_obj_type> m_pfn;

public:
    event_slot() = default;
    template <typename F> event_slot(F&& f)
        : m_pfn(std::make_shared<fn_obj_type>(std::forward<F>(f)))
    {

    }

    template <typename F>
    event_slot& set(F&& f)
    {
        m_pfn = std::make_shared<event_slot>(
            std::forward<F>(f));
        return *this;
    }

    const std::shared_ptr<fn_obj_type>& get_ptr() const
    {
        return m_pfn;
    }
};

template <typename Owner, typename ...Args>
event<Owner, void(Args...)>& event<Owner, void(Args...)>::operator +=(
    event_slot<typename event<Owner, void(Args...)>::fn_type>& fn)
{
    _m_lst_fn_removable.emplace_back(fn.get_ptr());
    return *this;
}

template <typename Owner, typename ...Args>
event<Owner, void(Args...)>& event<Owner, void(Args...)>::operator -=(
    event_slot<typename event<Owner, void(Args...)>::fn_type>& fn)
{
    bool succeeded = false;
    auto it = std::remove_if(_m_lst_fn_removable.begin(), _m_lst_fn_removable.end(),
        [&fn, &succeeded](const std::weak_ptr<fn_obj_type>& item) {
            auto sptr = item.lock();

            if (sptr == fn.get_ptr())   // found
                return (succeeded = true);
            else if (!sptr)             // expired
                return true;
            else                        // otherwise
                return false;
        });
    _m_lst_fn_removable.erase(it, _m_lst_fn_removable.end());

    if (!succeeded)
        throw std::invalid_argument("'fn' of event<>::operator -=()");

    return *this;
}

END_IWL()

#endif // IWL_EVENT_HPP_
