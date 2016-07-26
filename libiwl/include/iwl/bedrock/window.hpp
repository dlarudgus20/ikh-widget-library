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

#ifndef IWL_BEDROCK_WINDOW_HPP_
#define IWL_BEDROCK_WINDOW_HPP_

#include "../defines.hpp"
#include "../bedrock/draw_context.hpp"
#include "../drawing/graphics.hpp"
#include "../drawing/types.hpp"

BEGIN_IWL()

namespace bedrock
{
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

    enum wndproc_result
    {
        succeeded,
        failed,
    };

    struct load_args { };
    struct paint_args
    {
        graphics g;
    };
    using wndproc_args = boost::variant<
        load_args,
        paint_args>;

    class window : private boost::noncopyable
    {
        using wndproc_t = std::function<wndproc_result (wndproc_args&)>;
    private:
        native_window_handle m_wnd = nullptr;
        draw_context m_draw_context;

        wndproc_t m_wndproc;

    public:
        bool create(wndproc_t wndproc, const char*& errmsg);
        void show();

        graphics create_graphics();

        native_window_handle native_handle() const;

    private:
        static std::uintptr_t __stdcall native_wndproc(
            native_window_handle wnd, std::uint32_t iMsg, std::uintptr_t wParam, std::uintptr_t lParam);
    };

    inline native_window_handle window::native_handle() const
    {
        return m_wnd;
    }
}

END_IWL()

#endif // IWL_BEDROCK_WINDOW_HPP_
