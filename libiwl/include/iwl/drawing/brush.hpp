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

#ifndef IWL_DRAWING_BRUSH_HPP_
#define IWL_DRAWING_BRUSH_HPP_

#include "../defines.hpp"

BEGIN_IWL()

class brush
{
public:
    virtual ~brush() = 0;
};

class solid_brush : public brush
{
private:
    class impl;
    std::unique_ptr<impl> m_pimpl;

public:
    virtual ~solid_brush();

    void swap(solid_brush& other) noexcept { m_pimpl.swap(other.m_pimpl); }
};

class hatch_brush : public brush
{
private:
    class impl;
    std::unique_ptr<impl> m_pimpl;

public:
    virtual ~hatch_brush();

    void swap(hatch_brush& other) noexcept { m_pimpl.swap(other.m_pimpl); }
};

class linear_gradient_brush : public brush
{
private:
    class impl;
    std::unique_ptr<impl> m_pimpl;

public:
    virtual ~linear_gradient_brush();

    void swap(linear_gradient_brush& other) noexcept { m_pimpl.swap(other.m_pimpl); }
};

class path_gradient_brush : public brush
{
private:
    class impl;
    std::unique_ptr<impl> m_pimpl;

public:
    virtual ~path_gradient_brush();

    void swap(path_gradient_brush& other) noexcept { m_pimpl.swap(other.m_pimpl); }
};

class texture_brush : public brush
{
private:
    class impl;
    std::unique_ptr<impl> m_pimpl;

public:
    virtual ~solid_brush();

    void swap(texture_brush& other) noexcept { m_pimpl.swap(other.m_pimpl); }
};

namespace std
{
    template <>
    void swap(solid_brush& a, solid_brush& b) noexcept { a.swap(b); }
    template <>
    void swap(hatch_brush& a, hatch_brush& b) noexcept { a.swap(b); }
    template <>
    void swap(linear_gradient_brush& a, linear_gradient_brush& b) noexcept { a.swap(b); }
    template <>
    void swap(path_gradient_brush& a, path_gradient_brush& b) noexcept { a.swap(b); }
    template <>
    void swap(texture_brush& a, texture_brush& b) noexcept { a.swap(b); }
}

END_IWL()

#endif // IWL_DRAWING_BRUSH_HPP_
