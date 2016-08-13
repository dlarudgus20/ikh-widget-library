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

#include "pch.h"
#include "iwl/widget/form.hpp"
#include "iwl/drawing/graphics.hpp"
#include "iwl/drawing/brush.hpp"

BEGIN_IWL()

form::form(const form_style& style /* = { } */)
    : widget { *this }
{
    auto proc = [this](auto&& args) {
        return boost::apply_visitor(
            [this](auto& args) { return this->wndproc_handler(args); },
            args);
    };

    const char* errmsg;
    if (!m_wnd.create(proc, errmsg))
        throw form_creation_error(errmsg);

    m_ptr_background = &brushes::green();
}

void form::show()
{
    m_wnd.show();
}

bedrock::window& form::bedrock()
{
    return m_wnd;
}
const bedrock::window& form::bedrock() const
{
    return m_wnd;
}

void form::background(const brush& b)
{
    m_ptr_background = &b;
}
const brush& form::background() const
{
    return *m_ptr_background;
}

bedrock::wndproc_result form::wndproc_handler(bedrock::load_args& args)
{
    bool succeeded = true;
    on_load.emit(succeeded);
    if (succeeded)
        return bedrock::wndproc_result::succeeded;
    else
        return bedrock::wndproc_result::failed;
}

bedrock::wndproc_result form::wndproc_handler(bedrock::paint_args& args)
{
    auto sz = m_wnd.size();
    args.g.fill_rectangle(rectangle { 0, 0, sz.width, sz.height }, *m_ptr_background);
    on_paint.emit(args.g);
    return bedrock::wndproc_result::succeeded;
}

bedrock::wndproc_result form::wndproc_handler(bedrock::size_args& args)
{
    size(args.size);
    return bedrock::wndproc_result::succeeded;
}

void form::size_changed(const ::iwl::size& sz)
{
    if (m_wnd.size() != sz)
    {
        m_wnd.size(sz);
    }
}

END_IWL()
