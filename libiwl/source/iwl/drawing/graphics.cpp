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
#include "iwl/drawing/graphics.hpp"
#include "iwl/widget/widget.hpp"
#include "iwl/widget/form.hpp"

#include <windows.h>

BEGIN_IWL()

graphics::graphics(graphics&& other)
{
    m_handle = other.m_handle;
    other.m_handle = nullptr;
}

graphics& graphics::operator =(graphics&& other)
{
    m_handle = other.m_handle;
    other.m_handle = nullptr;
    return *this;
}

void graphics::swap(graphics& other) noexcept
{
    std::swap(m_handle, other.m_handle);
}

graphics graphics::from_handle(native_graphics_handle handle)
{
    graphics g;
    g.m_handle = handle;
    return g;
}

graphics graphics::from_widget(widget& wd)
{
    return wd.parent_form().bedrock().create_graphics();
}

END_IWL()
