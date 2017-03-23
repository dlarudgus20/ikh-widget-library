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

#ifndef IWL_DRAWING_GRAPHICS_HPP_
#define IWL_DRAWING_GRAPHICS_HPP_

#include "../defines.hpp"
#include "types.hpp"
#include "brush.hpp"

BEGIN_IWL()

class widget;
class window;

namespace detail
{
    struct native_graphics_handle_impl { };
}
using native_graphics_handle = detail::native_graphics_handle_impl*;

class graphics_creation_error : public std::runtime_error
{
public:
    explicit graphics_creation_error(const std::string& msg)
        : std::runtime_error { msg } { }
};

class graphics : private boost::noncopyable
{
    friend window;

public:
    ~graphics();

    static graphics from_widget(widget& wd);

    graphics(graphics&& other) noexcept;
    graphics& operator =(graphics&& other) noexcept;
    void swap(graphics& other) noexcept;

    void fill_rectangle(const rectanglef& rt, const brush& b);

private:
    static void check_gdi_startup();

    explicit graphics(native_graphics_handle handle);
    void destroy();

    native_graphics_handle m_handle;
};

inline void swap(graphics& a, graphics& b) noexcept
{
    a.swap(b);
}

END_IWL()

#endif // IWL_DRAWING_GRAPHICS_HPP_
