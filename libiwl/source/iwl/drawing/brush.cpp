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
#include "iwl/drawing/brush.hpp"

#include <gdiplus.h>

BEGIN_IWL()

brush::~brush() = default;

struct solid_brush::impl
{
    Gdiplus::SolidBrush _brush;
};

solid_brush::~solid_brush()
{

}

void solid_brush::swap(solid_brush& other) noexcept
{
    m_pimpl.swap(other.m_pimpl);
}

struct hatch_brush::impl
{
    Gdiplus::HatchBrush _brush;
};

hatch_brush::~hatch_brush()
{

}

void hatch_brush::swap(hatch_brush& other) noexcept
{
    m_pimpl.swap(other.m_pimpl);
}

struct linear_gradient_brush::impl
{
    Gdiplus::LinearGradientBrush _brush;
};

linear_gradient_brush::~linear_gradient_brush()
{

}

void linear_gradient_brush::swap(linear_gradient_brush& other) noexcept
{
    m_pimpl.swap(other.m_pimpl);
}

struct path_gradient_brush::impl
{
    Gdiplus::PathGradientBrush _brush;
};

path_gradient_brush::~path_gradient_brush()
{

}

void path_gradient_brush::swap(path_gradient_brush& other) noexcept
{
    m_pimpl.swap(other.m_pimpl);
}

struct texture_brush::impl
{
    Gdiplus::TextureBrush _brush;
};

texture_brush::~texture_brush()
{

}

void texture_brush::swap(texture_brush& other) noexcept
{
    m_pimpl.swap(other.m_pimpl);
}

END_IWL()
