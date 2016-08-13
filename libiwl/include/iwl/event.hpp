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

// event_invoker_last

template <typename Proto>
struct event_invoker_last;
template <typename Result, typename... Args>
struct event_invoker_last<Result (Args...)>
{
    template <typename ...Args2>
    bool operator ()(const std::function<Result (Args2...)>& fn, Args2&&... args)
    {
        m_rs = fn(std::forward<Args2>(args)...);
        return true;
    }
    Result& result()
    {
        return m_rs;
    }
private:
    Result m_rs { }; // initialize by default value
};
template <typename... Args>
struct event_invoker_last<void (Args...)>
{
    template <typename... Args2>
    bool operator ()(const std::function<void (Args2...)>& fn, Args2&&... args)
    {
        fn(std::forward<Args2>(args)...);
        return true;
    }
    void result() { }
};

// event & detail::event_base forward declaration
template <typename Proto, typename Invoker = event_invoker_last<Proto>>
class event;

namespace detail
{
    template <typename Result, typename ...Args>
    class event_base;
}

// event_slot declaration

class event_slot final
{
private:
    std::size_t m_id;

public:
    static event_slot from_id(std::size_t id)
    {
        event_slot s;
        s.m_id = id;
        return s;
    }
    std::size_t id() const { return m_id; }

    event_slot() noexcept : m_id { 0 } { };
    bool empty() const { return (m_id == 0); }
};

template <typename Proto>
class scoped_event_slot;
template <typename Result, typename... Args>
class scoped_event_slot<Result (Args...)> final : private boost::noncopyable
{
private:
    event_slot m_slot;
    detail::event_base<Result, Args...>* m_ptr_evt;

    void destroy();

public:
    scoped_event_slot() noexcept;
    explicit scoped_event_slot(detail::event_base<Result, Args...>& evt, const event_slot& s = { }) noexcept;

    template <typename Invoker>
    explicit scoped_event_slot(event<Result (Args...), Invoker>& evt, const event_slot& s = { }) noexcept
        : scoped_event_slot { static_cast<detail::event_base<Result (Args...)>&>(evt), s } { }

    ~scoped_event_slot();

    scoped_event_slot(scoped_event_slot&& other) noexcept;
    scoped_event_slot& operator =(scoped_event_slot&& other) noexcept;
    void swap(scoped_event_slot& other) noexcept;

    const event_slot& get() const;
    event_slot release();
};


// event & detail::event_base implementation
namespace detail
{
    template <typename Result, typename... Args>
    class event_base : private boost::noncopyable
    {
    public:
        using fn_type = Result (Args...);
        using fn_obj_type = std::function<fn_type>;

        using slot = event_slot;
        using scoped_slot = scoped_event_slot<Result (Args...)>;

    protected:
        struct fn_node
        {
            fn_node* prev;
            fn_node* next;
            bool removed;
            bool just_added;
            bool emiting; // only valid if this == m_lst
            fn_obj_type fn;

            fn_node() = default;
            template <typename U>
            explicit fn_node(U&& u) : fn { std::forward<U>(u) } { }
        };

        fn_node* m_lst = nullptr;

        void destroy()
        {
            fn_node* node = m_lst;
            if (!node)
                return;

            assert(!m_lst->emiting && "destroying event object while emit()");

            do
            {
                fn_node* after = node->next;
                delete node;
                node = after;
            }
            while (node != m_lst);

            m_lst = nullptr;
        }

        bool is_emitting() const
        {
            return (m_lst && m_lst->emiting);
        }

        event_base() = default;
        ~event_base() { destroy(); }

        event_base(event_base&& other) noexcept
            : m_lst { other.m_lst }
        {
            assert(!other.is_emitting() && "moving event object while emit()");

            other.m_lst = nullptr;
        }
        event_base& operator =(event_base&& other) noexcept
        {
            assert(!other.is_emitting() && "moving event object while emit()");

            destroy();
            m_lst = other.m_lst;
            other.m_lst = nullptr;
            return *this;
        }

    public:
        void swap(event_base& other) noexcept
        {
            assert(!is_emitting() && "swapping event object while emit()");
            assert(!other.is_emitting() && "swapping event object while emit()");

            using std::swap;
            swap(m_lst, other.m_lst);
        }

        template <typename F>
        slot add(F&& fn)
        {
            return add_scoped(std::forward<F>(fn)).release();
        }

        template <typename F>
        scoped_slot add_scoped(F&& fn)
        {
            fn_node* item = new fn_node { std::forward<F>(fn) };

            if (!m_lst)
            {
                item->prev = item;
                item->next = item;
                item->removed = false;
                item->just_added = false;
                item->emiting = false;
                m_lst = item;
            }
            else
            {
                item->prev = m_lst->prev;
                item->next = m_lst;
                item->removed = false;
                item->just_added = m_lst->emiting;
                item->emiting = false;

                m_lst->prev->next = item;
                m_lst->prev = item;
            }

            return scoped_slot { *this, slot::from_id(reinterpret_cast<std::size_t>(item)) };
        }

        bool remove(const slot& s)
        {
            if (!m_lst)
                return false;

            if (reinterpret_cast<std::size_t>(m_lst) == s.id())
            {
                if (m_lst->emiting)
                {
                    if (m_lst->removed)
                        return false;
                    m_lst->removed = true;
                }
                else
                {
                    delete m_lst;
                    m_lst = nullptr;
                }
                return true;
            }
            else
            {
                fn_node* node = m_lst->next;
                while (node != m_lst)
                {
                    if (reinterpret_cast<std::size_t>(node) == s.id())
                    {
                        if (node->emiting)
                        {
                            if (node->removed)
                                return false;
                            node->removed = true;
                        }
                        else
                        {
                            node->prev->next = node->next;
                            node->next->prev = node->prev;
                            delete node;
                        }
                        return true;
                    }
                    node = node->next;
                }
                return false;
            }
        }

        bool remove(scoped_slot& s)
        {
            bool ret = remove(s.get());
            if (ret)
                s.release();
            return ret;
        }

        bool empty() const
        {
            return (m_lst == nullptr);
        }
    };
}

template <typename Invoker, typename Result, typename... Args>
class event<Result (Args...), Invoker> final : public detail::event_base<Result, Args...>
{
private:
    using base_t = detail::event_base<Result, Args...>;
    using base_t::m_lst;
    using typename base_t::fn_node;

public:
    template <typename... Args2>
    auto emit(Args2&&... args)
    {
        Invoker invoker;

        if (m_lst)
        {
            m_lst->emiting = true;

            fn_node* node = m_lst;
            do
            {
                if (node->removed || node->just_added)
                    continue;

                if (!invoker(node->fn, std::forward<Args2>(args)...))
                    break;

                node = node->next;
            }
            while (node != m_lst);

            node = m_lst;
            do
            {
                if (node->just_added)
                {
                    node->just_added = false;
                }
                else if (node->removed)
                {
                    if (node->prev == node)
                    {
                        m_lst = nullptr;
                        delete node;
                        break;
                    }
                    else
                    {
                        node->prev->next = node->next;
                        node->next->prev = node->prev;
                        if (node == m_lst)
                            m_lst = node->next;
                        delete node;
                    }
                }
            }
            while (node != m_lst);
        }

        return invoker.result();
    }
};

template <typename Proto, typename Invoker>
void swap(event<Proto, Invoker>& a, event<Proto, Invoker>& b)
{
    a.swap(b);
}

// scoped_event_slot implementation

template <typename Result, typename... Args>
void scoped_event_slot<Result (Args...)>::destroy()
{
    if (!m_slot.empty())
        m_ptr_evt->remove(m_slot);
}

template <typename Result, typename... Args>
scoped_event_slot<Result (Args...)>::scoped_event_slot() noexcept
    : m_ptr_evt { nullptr }, m_slot { } { }

template <typename Result, typename... Args>
scoped_event_slot<Result (Args...)>::scoped_event_slot(
    detail::event_base<Result, Args...>& evt, const event_slot& s /* = { } */) noexcept
    : m_ptr_evt { &evt }, m_slot { s } { }

template <typename Result, typename... Args>
scoped_event_slot<Result (Args...)>::~scoped_event_slot()
{
    destroy();
}

template <typename Result, typename... Args>
scoped_event_slot<Result (Args...)>::scoped_event_slot(scoped_event_slot&& other) noexcept
    : m_ptr_evt { other.m_ptr_evt }, m_slot { other.m_slot }
{
    other.m_ptr_evt = nullptr;
    other.m_slot = event_slot { };
}

template <typename Result, typename... Args>
scoped_event_slot<Result (Args...)>& scoped_event_slot<Result (Args...)>::operator =(scoped_event_slot&& other) noexcept
{
    destroy();
    m_slot = other.m_slot;
    other.m_slot = event_slot { };
    m_ptr_evt = other.m_ptr_evt;
    other.m_ptr_evt = nullptr;
    return *this;
}

template <typename Result, typename... Args>
void scoped_event_slot<Result (Args...)>::swap(scoped_event_slot& other) noexcept
{
    using std::swap;
    swap(m_slot, other.m_slot);
    swap(m_ptr_evt, other.m_ptr_evt);
}

template <typename Proto>
void swap(scoped_event_slot<Proto>& a, scoped_event_slot<Proto>& b) noexcept
{
    a.swap(b);
}

template <typename Result, typename... Args>
const event_slot& scoped_event_slot<Result (Args...)>::get() const
{
    return m_slot;
}

template <typename Result, typename... Args>
event_slot scoped_event_slot<Result (Args...)>::release()
{
    event_slot s = m_slot;
    m_ptr_evt = nullptr;
    m_slot = event_slot { };
    return s;
}

END_IWL()

#endif // IWL_EVENT_HPP_
