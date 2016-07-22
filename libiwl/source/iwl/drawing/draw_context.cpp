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
#include "iwl/drawing/draw_context.hpp"
#include "iwl/form.hpp"

namespace
{
    bool s_bGlewInited = false;
}

BEGIN_IWL()

void draw_context::initialize(form& frm)
{
    HWND hWnd = (HWND)frm.native_handle();
    HDC hdc = ::GetDC(hWnd);

    PIXELFORMATDESCRIPTOR pfd;
    std::memset(&pfd, 0, sizeof(pfd));
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = 32;
    pfd.cDepthBits = 24;
    pfd.cStencilBits = 8;
    pfd.iLayerType = PFD_MAIN_PLANE;

    int iPixelFormat = ::ChoosePixelFormat(hdc, &pfd);
    if (iPixelFormat == 0)
        throw draw_context_creation_error("opengl is not supported");

    if (!::SetPixelFormat(hdc, iPixelFormat, &pfd))
        throw draw_context_creation_error("opengl is not supported");

    HGLRC hFakeRC = ::wglCreateContext(hdc);
    ::wglMakeCurrent(hdc, hFakeRC);

    if (!s_bGlewInited)
    {
        if (::glewInit() != GLEW_OK)
            throw draw_context_creation_error("cannot initialize glew");
        s_bGlewInited = true;
    }

    ::wglMakeCurrent(nullptr, nullptr);
    ::wglDeleteContext(hFakeRC);

    if (!WGLEW_ARB_create_context || !WGLEW_ARB_pixel_format)
        throw draw_context_creation_error("opengl 3.3 is not supported");

    const int pixel_attribs[] = {
        WGL_DRAW_TO_WINDOW_ARB, GL_TRUE,
        WGL_SUPPORT_OPENGL_ARB, GL_TRUE,
        WGL_DOUBLE_BUFFER_ARB, GL_TRUE,
        WGL_PIXEL_TYPE_ARB, WGL_TYPE_RGBA_ARB,
        WGL_COLOR_BITS_ARB, 32,
        WGL_DEPTH_BITS_ARB, 24,
        WGL_STENCIL_BITS_ARB, 8,
        0
    };
    const int context_attribs[] = {
        WGL_CONTEXT_MAJOR_VERSION_ARB, 3,
        WGL_CONTEXT_MINOR_VERSION_ARB, 3,
        WGL_CONTEXT_FLAGS_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
        0
    };

    UINT iNumFormats;
    ::wglChoosePixelFormatARB(hdc, pixel_attribs, nullptr, 1, &iPixelFormat, &iNumFormats);

    if (!::SetPixelFormat(hdc, iPixelFormat, &pfd))
        throw draw_context_creation_error("opengl 3.3 is not supported");

    m_context = (native_drawing_context)::wglCreateContextAttribsARB(hdc, 0, context_attribs);
    if (m_context == nullptr)
        throw draw_context_creation_error("opengl 3.3 is not supported");
}

END_IWL()
