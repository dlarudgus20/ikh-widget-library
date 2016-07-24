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

#ifndef IWL_FORM_HPP_
#define IWL_FORM_HPP_

#include "defines.hpp"
#include "bedrock/window.hpp"
#include "bedrock/draw_context.hpp"
#include "drawing/drawing.hpp"
#include "event.hpp"

BEGIN_IWL()

namespace detail
{
    struct native_window_handle_impl { };
}
using native_window_handle = detail::native_window_handle_impl*;

class form_creation_error : public std::runtime_error
{
public:
    explicit form_creation_error(const std::string& msg)
        : std::runtime_error { msg } { }
};

struct form_style
{
};

class form : private boost::noncopyable
{
private:
    bedrock::window m_wnd;
    bedrock::draw_context m_draw_context;

    boost::optional<iwl::drawing&> m_drawing;

public:
    explicit form(const form_style& style = { });

    void show();

    boost::optional<iwl::drawing&> drawing() const;
    void drawing(boost::optional<iwl::drawing&> d);

    event<form, void (bool& succeeded)> on_load;

private:
    bedrock::wndproc_result wndproc(bedrock::wndproc_msg msg, bedrock::wndproc_args& args);
};

inline boost::optional<iwl::drawing&> form::drawing() const
{
    return m_drawing;
}

inline void form::drawing(boost::optional<iwl::drawing&> d)
{
    m_drawing = d;
}

END_IWL()

#endif // IWL_FORM_HPP_
