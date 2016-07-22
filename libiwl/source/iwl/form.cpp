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

namespace
{
    using namespace iwl;

    LRESULT CALLBACK WndProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam);

    std::wstring style_wndcls(const form_style& style, WNDCLASSEX& wc)
    {
        static unsigned id = 0;

        std::wstring strcls = L"ikh-widget-library_win32_wndcls_" + std::to_wstring(id);
        id++;

        wc.cbSize = sizeof(wc);
        wc.cbClsExtra = 0;
        wc.cbWndExtra = 0;
        wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
        wc.hCursor = ::LoadCursor(nullptr, IDC_ARROW);
        wc.hIcon = ::LoadIcon(nullptr, IDI_APPLICATION);
        wc.hIconSm = nullptr;
        wc.hInstance = ::GetModuleHandle(nullptr);
        wc.lpfnWndProc = WndProc;
        wc.lpszMenuName = nullptr;
        wc.style = CS_VREDRAW | CS_HREDRAW | CS_OWNDC;
        wc.lpszClassName = strcls.c_str();

        if (::RegisterClassEx(&wc) == 0)
            throw form_creation_error("failed in registering window class");

        return strcls;
    }
    void style_createstruct(const form_style& style, CREATESTRUCT& cs)
    {
        cs.dwExStyle = 0;
        cs.lpszName = L"form";
        cs.style = WS_OVERLAPPEDWINDOW;
        cs.x = CW_USEDEFAULT;
        cs.y = CW_USEDEFAULT;
        cs.cx = CW_USEDEFAULT;
        cs.cy = CW_USEDEFAULT;
        cs.hwndParent = nullptr;
        cs.hMenu = nullptr;
    }
    LRESULT CALLBACK WndProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
    {
        return ::DefWindowProc(hWnd, iMsg, wParam, lParam);
    }
}

BEGIN_IWL()

form::form(const form_style& style /* = { } */)
{
    WNDCLASSEX wc;
    std::wstring strcls = style_wndcls(style, wc);

    CREATESTRUCT cs;
    style_createstruct(style, cs);

    m_wnd = (native_window_handle)::CreateWindowEx(
        cs.dwExStyle, strcls.c_str(), cs.lpszName, cs.style,
        cs.x, cs.y, cs.cx, cs.cy,
        cs.hwndParent, cs.hMenu, ::GetModuleHandle(nullptr),
        this);
    if (m_wnd == nullptr)
        throw form_creation_error("failed in creating window");

    m_draw_context.initialize(*this);
}

void form::show()
{
    ::ShowWindow((HWND)m_wnd, SW_NORMAL);
}

END_IWL()
