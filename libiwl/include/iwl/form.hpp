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
#include "drawing/draw_init.hpp"

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
	native_window_handle m_wnd;

	draw_init m_draw_init;

public:
	explicit form(const form_style& style = { });

	void show();

	native_window_handle native_handle() const;
};

inline native_window_handle form::native_handle() const
{
	return m_wnd;
}

END_IWL()

#endif // IWL_FORM_HPP_
