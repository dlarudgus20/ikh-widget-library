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

#ifndef GDIUTIL_H_
#define GDIUTIL_H_

#include "iwl/defines.hpp"
#include "iwl/drawing/types.hpp"
#include "iwl/drawing/color.hpp"

#include <windows.h>
#include <gdiplus.h>

namespace gdiutil
{
    inline Gdiplus::PointF gdi_pointf(const iwl::point& p)
    {
        return Gdiplus::PointF { p.x, p.y };
    }

    inline Gdiplus::RectF gdi_rectf(const iwl::rectangle& rt)
    {
        return Gdiplus::RectF { rt.x, rt.y, rt.width, rt.height };
    }

    inline Gdiplus::Color gdi_color(const iwl::color& c)
    {
        return Gdiplus::Color { static_cast<Gdiplus::ARGB>(c.argb()) };
    }
};

#endif // GDIUTIL_H_
