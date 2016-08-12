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
#include "color.hpp"

BEGIN_IWL()

namespace detail
{
    struct native_brush_handle_impl { };
}
using native_brush_handle = detail::native_brush_handle_impl*;

class brush
{
    friend class solid_brush;
    friend class hatch_brush;
    friend class linear_gradient_brush;
    //friend class path_gradient_brush;
    //friend class texture_brush;

private:
    native_brush_handle m_native;
    brush() = default;

public:
    virtual ~brush() = 0;
};

class solid_brush : public brush
{
public:
    explicit solid_brush(const color& c);

    void swap(solid_brush& other) noexcept;
};

class hatch_brush : public brush
{
public:
    enum style
    {
        hatch_style_horizontal                  = 0,
        hatch_style_vertical                    = 1,
        hatch_style_forward_diagonal            = 2,
        hatch_style_backward_diagonal           = 3,
        hatch_style_cross                       = 4,
        hatch_style_diagonal_cross              = 5,
        hatch_style05_percent                   = 6,
        hatch_style10_percent                   = 7,
        hatch_style20_percent                   = 8,
        hatch_style25_percent                   = 9,
        hatch_style30_percent                   = 10,
        hatch_style40_percent                   = 11,
        hatch_style50_percent                   = 12,
        hatch_style60_percent                   = 13,
        hatch_style70_percent                   = 14,
        hatch_style75_percent                   = 15,
        hatch_style80_percent                   = 16,
        hatch_style90_percent                   = 17,
        hatch_style_light_downward_diagonal     = 18,
        hatch_style_light_upward_diagonal       = 19,
        hatch_style_dark_downward_diagonal      = 20,
        hatch_style_dark_upward_diagonal        = 21,
        hatch_style_wide_downward_diagonal      = 22,
        hatch_style_wide_upward_diagonal        = 23,
        hatch_style_light_vertical              = 24,
        hatch_style_light_horizontal            = 25,
        hatch_style_narrow_vertical             = 26,
        hatch_style_narrow_horizontal           = 27,
        hatch_style_dark_vertical               = 28,
        hatch_style_dark_horizontal             = 29,
        hatch_style_dashed_downward_diagonal    = 30,
        hatch_style_dashed_upward_diagonal      = 31,
        hatch_style_dashed_horizontal           = 32,
        hatch_style_dashed_vertical             = 33,
        hatch_style_small_confetti              = 34,
        hatch_style_large_confetti              = 35,
        hatch_style_zig_zag                     = 36,
        hatch_style_wave                        = 37,
        hatch_style_diagonal_brick              = 38,
        hatch_style_horizontal_brick            = 39,
        hatch_style_weave                       = 40,
        hatch_style_plaid                       = 41,
        hatch_style_divot                       = 42,
        hatch_style_dotted_grid                 = 43,
        hatch_style_dotted_diamond              = 44,
        hatch_style_shingle                     = 45,
        hatch_style_trellis                     = 46,
        hatch_style_sphere                      = 47,
        hatch_style_small_grid                  = 48,
        hatch_style_small_checker_board         = 49,
        hatch_style_large_checker_board         = 50,
        hatch_style_outlined_diamond            = 51,
        hatch_style_solid_diamond               = 52,
        hatch_style_total                       = 53,
        hatch_style_large_grid                  = hatch_style_cross,
        hatch_style_min                         = hatch_style_horizontal,
        hatch_style_max                         = hatch_style_total - 1
    };

    hatch_brush(style st, const color& fore, const color& back);

    void swap(hatch_brush& other) noexcept;
};
/*
class linear_gradient_brush : public brush
{
public:
    void swap(linear_gradient_brush& other) noexcept;
};

class path_gradient_brush : public brush
{
public:
    void swap(path_gradient_brush& other) noexcept;
};

class texture_brush : public brush
{
private:
    class impl;
    std::unique_ptr<impl> m_pimpl;

public:
    void swap(texture_brush& other) noexcept;
};
*/
inline void swap(solid_brush& a, solid_brush& b) noexcept { a.swap(b); }
inline void swap(hatch_brush& a, hatch_brush& b) noexcept { a.swap(b); }
inline void swap(linear_gradient_brush& a, linear_gradient_brush& b) noexcept { a.swap(b); }
//inline void swap(path_gradient_brush& a, path_gradient_brush& b) noexcept { a.swap(b); }
//inline void swap(texture_brush& a, texture_brush& b) noexcept { a.swap(b); }

END_IWL()

#endif // IWL_DRAWING_BRUSH_HPP_
