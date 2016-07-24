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
#include "iwl/form.hpp"

BEGIN_IWL()

form::form(const form_style& style /* = { } */)
{
    auto proc = [this](auto&& msg, auto&& args) { return wndproc(msg, args); };

    const char* errmsg;
    if (!m_wnd.create(proc, errmsg))
        throw form_creation_error(errmsg);

    m_draw_context.initialize(m_wnd);
}

void form::show()
{
    m_wnd.show();
}

inline bedrock::wndproc_result form::wndproc(bedrock::wndproc_msg msg, bedrock::wndproc_args& args)
{
    bool succeeded;

    switch (msg)
    {
        case bedrock::wndproc_msg::load:
            succeeded = true;
            on_load.fire_with_observer(
                [&]() { return succeeded; },
                succeeded);
            return (succeeded ? bedrock::wndproc_result::succeeded : bedrock::wndproc_result::failed);
        case bedrock::wndproc_msg::paint:
            if (m_drawing)
                m_drawing->draw(args.paint.clipping);
            return bedrock::wndproc_result::succeeded;
        default:
            return bedrock::wndproc_result::succeeded;
    }
}


END_IWL()
