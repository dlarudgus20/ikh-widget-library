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
#include "iwl/bedrock/window.hpp"

#include <windows.h>

BEGIN_IWL()

namespace bedrock
{
    bool window::create(wndproc_t wndproc, const char*& errmsg)
    {
        m_wndproc = wndproc;

        static unsigned id = 0;

        std::wstring strcls = L"ikh-widget-library_win32_wndcls_" + std::to_wstring(id);
        id++;

        WNDCLASSEXW wc;
        wc.cbSize = sizeof(wc);
        wc.cbClsExtra = 0;
        wc.cbWndExtra = sizeof(window*);
        wc.hbrBackground = nullptr;
        wc.hCursor = ::LoadCursorW(nullptr, IDC_ARROW);
        wc.hIcon = ::LoadIconW(nullptr, IDI_APPLICATION);
        wc.hIconSm = nullptr;
        wc.hInstance = ::GetModuleHandleW(nullptr);
        wc.lpfnWndProc = reinterpret_cast<WNDPROC>(&window::native_wndproc);
        wc.lpszMenuName = nullptr;
        wc.style = CS_VREDRAW | CS_HREDRAW | CS_OWNDC;
        wc.lpszClassName = strcls.c_str();

        if (::RegisterClassExW(&wc) == 0)
        {
            errmsg = "failed in registering window class";
            return false;
        }

        CREATESTRUCTW cs;
        cs.dwExStyle = 0;
        cs.lpszName = L"form";
        cs.style = WS_OVERLAPPEDWINDOW;
        cs.x = CW_USEDEFAULT;
        cs.y = CW_USEDEFAULT;
        cs.cx = CW_USEDEFAULT;
        cs.cy = CW_USEDEFAULT;
        cs.hwndParent = nullptr;
        cs.hMenu = nullptr;

        HWND hWnd = ::CreateWindowExW(
            cs.dwExStyle, strcls.c_str(), cs.lpszName, cs.style,
            cs.x, cs.y, cs.cx, cs.cy,
            cs.hwndParent, cs.hMenu, ::GetModuleHandle(nullptr),
            this);
        m_wnd = reinterpret_cast<native_window_handle>(hWnd);
        if (m_wnd == nullptr)
        {
            errmsg = "failed in creating window";
            return false;
        }

        m_draw_context.initialize(*this);

        return true;
    }

    void window::show()
    {
        ::ShowWindow((HWND)m_wnd, SW_NORMAL);
    }

    std::uintptr_t __stdcall window::native_wndproc(native_window_handle wnd, std::uint32_t iMsg, std::uintptr_t wParam, std::uintptr_t lParam)
    {
        HWND hWnd = reinterpret_cast<HWND>(wnd);

        LPCREATESTRUCTW lpcs;

        switch (iMsg)
        {
            case WM_NCCREATE:
                lpcs = reinterpret_cast<LPCREATESTRUCTW>(lParam);
                ::SetWindowLongPtrW(hWnd, 0, reinterpret_cast<LONG_PTR>(lpcs->lpCreateParams));
                return ::DefWindowProc(hWnd, iMsg, wParam, lParam);
        }

        window* ptr_wnd = reinterpret_cast<window*>(::GetWindowLongPtrW(hWnd, 0));
        auto& wndproc = ptr_wnd->m_wndproc;
        wndproc_args args;

        PAINTSTRUCT ps;

        switch (iMsg)
        {
            case WM_CREATE:
                if (wndproc(wndproc_msg::load, args) == succeeded)
                    return 0;
                else
                    return -1;
            case WM_PAINT:
                ::BeginPaint(hWnd, &ps);
                args.paint.clipping = {
                    static_cast<float>(ps.rcPaint.left), static_cast<float>(ps.rcPaint.top),
                    static_cast<float>(ps.rcPaint.right), static_cast<float>(ps.rcPaint.bottom) };
                wndproc(wndproc_msg::paint, args);
                ::EndPaint(hWnd, &ps);
                return 0;
        }

        return ::DefWindowProc(hWnd, iMsg, wParam, lParam);
    }
}

END_IWL()
