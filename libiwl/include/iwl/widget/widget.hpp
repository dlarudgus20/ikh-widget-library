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

#ifndef IWL_WIDGET_WIDGET_HPP_
#define IWL_WIDGET_WIDGET_HPP_

#include "../defines.hpp"
#include "../event.hpp"
#include "../drawing/types.hpp"

BEGIN_IWL()

class form;
class graphics;

namespace detail
{
    struct onload_invoker
    {
        template <typename ...Args>
        bool operator ()(const std::function<void (bool&)>& fn, bool& succeeded)
        {
            fn(succeeded);
            return succeeded;
        }
        void result() { }
    };
}

class widget : private boost::noncopyable
{
private:
    form& m_frm;
    ::iwl::size m_size;

protected:
    explicit widget(form& frm);

public:
    virtual ~widget() = 0;

    form& parent_form() const;
    const ::iwl::size& size() const;
    void size(const ::iwl::size& sz);

    event<void (bool& succeeded), detail::onload_invoker> on_load;
    event<void (graphics& g)> on_paint;
    event<void (const ::iwl::size& sz)> on_size;

private:
    virtual void size_changed(const ::iwl::size& sz);
};

END_IWL()

#endif // IWL_WIDGET_WIDGET_HPP_
