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

BEGIN_IWL()

form::form(const form_style& style /* = { } */)
    : widget { *this }
{
    auto proc = [this](auto&& args) { return this->wndproc(args); };

    const char* errmsg;
    if (!m_wnd.create(proc, errmsg))
        throw form_creation_error(errmsg);
}

void form::show()
{
    m_wnd.show();
}

inline bedrock::wndproc_result form::wndproc(bedrock::wndproc_args& args)
{
    return boost::apply_visitor(
        [this](auto& args) { return this->wndproc_handler(args); },
        args);
}

bedrock::wndproc_result form::wndproc_handler(bedrock::load_args& args)
{
    if (fire_load())
        return bedrock::wndproc_result::succeeded;
    else
        return bedrock::wndproc_result::failed;
}

bedrock::wndproc_result form::wndproc_handler(bedrock::paint_args& args)
{
    fire_paint(args.g);
    return bedrock::wndproc_result::succeeded;
}

END_IWL()
