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
#include "iwl/bedrock/draw_context.hpp"
#include "iwl/bedrock/window.hpp"

#include "gdiutil.h"

namespace
{
    using namespace iwl::bedrock;

    struct context_t
    {
        ULONG_PTR gpToken;
        Gdiplus::GdiplusStartupInput gsi;
        context_t()
        {
            if (Gdiplus::GdiplusStartup(&gpToken, &gsi, nullptr) != Gdiplus::Ok)
                throw draw_context_creation_error("cannot initialize gdi+");
        }
        ~context_t()
        {
            Gdiplus::GdiplusShutdown(gpToken);
        }
    };
    std::weak_ptr<context_t> s_ptr_context;
}

BEGIN_IWL()

namespace bedrock
{
    draw_context::~draw_context()
    {
        if (m_ptr_wnd)
            deinitialize();
    }

    void draw_context::initialize(window& wnd)
    {
        m_ptr_wnd = &wnd;

        auto pc = s_ptr_context.lock();
        if (!pc)
        {
            pc = std::make_shared<context_t>();
            s_ptr_context = pc;
        }
        m_ptr_context = std::move(pc);
    }

    void draw_context::deinitialize()
    {
        m_ptr_wnd = nullptr;
        m_ptr_context.reset();
    }
}

END_IWL()
