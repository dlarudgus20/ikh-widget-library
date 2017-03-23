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

#ifndef IWL_WIDGET_WINDOW_HPP_
#define IWL_WIDGET_WINDOW_HPP_

#include "../defines.hpp"
#include "fragment.hpp"
#include "../drawing/graphics.hpp"
#include "../drawing/types.hpp"

BEGIN_IWL()

class brush;

namespace detail
{
    struct native_window_handle_impl { };
}
using native_window_handle = detail::native_window_handle_impl*;

class window_creation_error : public std::runtime_error
{
public:
    explicit window_creation_error(const std::string& msg)
        : std::runtime_error { msg } { }
};

struct window_style
{
};

class window : public fragment
{
public:
    window(const fragment_style& fstyle = { }, const window_style& wstyle = { });
    void show();

    const sizef& size() const override;
    void size(const sizef& sz) override;

    native_window_handle native_handle() const;

private:
    static std::uintptr_t __stdcall native_wndproc(
        native_window_handle wnd, std::uint32_t iMsg, std::uintptr_t wParam, std::uintptr_t lParam);

    native_window_handle m_wnd = nullptr;
    bool m_created = false;

    sizef m_size;
};

END_IWL()

#endif // IWL_WIDGET_WINDOW_HPP_
