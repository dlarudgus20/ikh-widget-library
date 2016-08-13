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

    native_brush_handle native_handle() const;
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
//inline void swap(linear_gradient_brush& a, linear_gradient_brush& b) noexcept { a.swap(b); }
//inline void swap(path_gradient_brush& a, path_gradient_brush& b) noexcept { a.swap(b); }
//inline void swap(texture_brush& a, texture_brush& b) noexcept { a.swap(b); }

struct brushes
{
    brushes() = delete;

#define DEF_BRUSH(name, colobj) \
    static const solid_brush& name() \
    { \
        static solid_brush brush { colobj }; \
        return brush; \
    }

    DEF_BRUSH(alice_blue, 0xfff0f8ff_argb)
    DEF_BRUSH(antique_white, 0xfffaebd7_argb)
    DEF_BRUSH(aqua, 0xff00fffff_argb)
    DEF_BRUSH(aquamarine, 0xff7fffd4_argb)
    DEF_BRUSH(azure, 0xfff0ffff_argb)
    DEF_BRUSH(beige, 0xfff5f5dc_argb)
    DEF_BRUSH(bisque, 0xffffe5c4_argb)
    DEF_BRUSH(black, 0xff000000_argb)
    DEF_BRUSH(blanched_almond, 0xffffebcd_argb)
    DEF_BRUSH(blue, 0xff0000ff_argb)
    DEF_BRUSH(blue_violet, 0xff8a2be2_argb)
    DEF_BRUSH(brown, 0xff8a2be2_argb)
    DEF_BRUSH(burly_wood, 0xffde8887_argb)
    DEF_BRUSH(cadet_blue, 0xff5f9ea0_argb)
    DEF_BRUSH(chartreuse, 0xff7fff00_argb)
    DEF_BRUSH(chocolate, 0xffd2691e_argb)
    DEF_BRUSH(coral, 0xffff7f50_argb)
    DEF_BRUSH(cornflower_blue, 0xff6495ed_argb)
    DEF_BRUSH(cornsilk, 0xfffff8dc_argb)
    DEF_BRUSH(crimson, 0xffdc143c_argb)
    DEF_BRUSH(cyan, 0xff00ffff_argb)
    DEF_BRUSH(dark_blue, 0xff00008b_argb)
    DEF_BRUSH(dark_cyan, 0xff008b8b_argb)
    DEF_BRUSH(dark_goldenrod, 0xffb8860b_argb)
    DEF_BRUSH(dark_gray, 0xffa9a9a9_argb)
    DEF_BRUSH(dark_green, 0xff006400_argb)
    DEF_BRUSH(dark_khaki, 0xffbdb76b_argb)
    DEF_BRUSH(dark_magenta, 0xff8b008b_argb)
    DEF_BRUSH(dark_olive_green, 0xff556b2f_argb)
    DEF_BRUSH(dark_orange, 0xffff8c00_argb)
    DEF_BRUSH(dark_orchid, 0xff9932cc_argb)
    DEF_BRUSH(dark_red, 0xff8b0000_argb)
    DEF_BRUSH(dark_salmon, 0xffe9967a_argb)
    DEF_BRUSH(dark_sea_green, 0xff8fbc8f_argb)
    DEF_BRUSH(dark_slate_blue, 0xff483d8b_argb)
    DEF_BRUSH(dark_slate_gray, 0xff2f4f4f_argb)
    DEF_BRUSH(dark_turquoise, 0xff00ced1_argb)
    DEF_BRUSH(dark_violet, 0xff9400d3_argb)
    DEF_BRUSH(deep_pink, 0xffff1493_argb)
    DEF_BRUSH(deep_sky_blue, 0xff00bfff_argb)
    DEF_BRUSH(dim_gray, 0xff696969_argb)
    DEF_BRUSH(dodger_blue, 0xff1e90ff_argb)
    DEF_BRUSH(firebrick, 0xffb22222_argb)
    DEF_BRUSH(floral_white, 0xfffffaf0_argb)
    DEF_BRUSH(forest_green, 0xff228b22_argb)
    DEF_BRUSH(fuchsia, 0xffff00ff_argb)
    DEF_BRUSH(gainsboro, 0xffdcdcdc_argb)
    DEF_BRUSH(ghost_white, 0xfff8f8ff_argb)
    DEF_BRUSH(gold, 0xffffd700_argb)
    DEF_BRUSH(goldenrod, 0xffdaa520_argb)
    DEF_BRUSH(gray, 0xff808080_argb)
    DEF_BRUSH(green, 0xff008000_argb)
    DEF_BRUSH(green_yellow, 0xffadff2f_argb)
    DEF_BRUSH(honeydew, 0xfff0fff0_argb)
    DEF_BRUSH(hot_pink, 0xffff69b4_argb)
    DEF_BRUSH(indian_red, 0xffcd5c5c_argb)
    DEF_BRUSH(indigo, 0xff4b0082_argb)
    DEF_BRUSH(ivory, 0xfffffff0_argb)
    DEF_BRUSH(khaki, 0xfff0e68c_argb)
    DEF_BRUSH(lavender, 0xffe6e6fa_argb)
    DEF_BRUSH(lavender_blush, 0xfffff0f5_argb)
    DEF_BRUSH(lawn_green, 0xff7cfc00_argb)
    DEF_BRUSH(lemon_chiffon, 0xfffffacd_argb)
    DEF_BRUSH(light_blue, 0xffadd8e6_argb)
    DEF_BRUSH(light_coral, 0xfff08080_argb)
    DEF_BRUSH(light_cyan, 0xffe0ffff_argb)
    DEF_BRUSH(light_goldenrod_yellow, 0xfffafad2_argb)
    DEF_BRUSH(light_gray, 0xffd3d3d3_argb)
    DEF_BRUSH(light_green, 0xff90ee90_argb)
    DEF_BRUSH(light_pink, 0xffffb6c1_argb)
    DEF_BRUSH(light_salmon, 0xffffa07a_argb)
    DEF_BRUSH(light_sea_green, 0xff20b2aa_argb)
    DEF_BRUSH(light_sky_blue, 0xff87cefa_argb)
    DEF_BRUSH(light_slate_gray, 0xff778899_argb)
    DEF_BRUSH(light_steel_blue, 0xffb0c4de_argb)
    DEF_BRUSH(light_yellow, 0xffffffe0_argb)
    DEF_BRUSH(lime, 0xff00ff00_argb)
    DEF_BRUSH(lime_green, 0xff32cd32_argb)
    DEF_BRUSH(linen, 0xfffaf0e6_argb)
    DEF_BRUSH(magenta, 0xffff00ff_argb)
    DEF_BRUSH(maroon, 0xff800000_argb)
    DEF_BRUSH(medium_aquamarine, 0xff66cdaa_argb)
    DEF_BRUSH(medium_blue, 0xff0000cd_argb)
    DEF_BRUSH(medium_orchid, 0xffba55d3_argb)
    DEF_BRUSH(medium_purple, 0xff9370db_argb)
    DEF_BRUSH(medium_sea_green, 0xff3cb371_argb)
    DEF_BRUSH(medium_slate_blue, 0xff7b68ee_argb)
    DEF_BRUSH(medium_spring_green, 0xff00fa9a_argb)
    DEF_BRUSH(medium_turquoise, 0xff48d1cc_argb)
    DEF_BRUSH(medium_violet_red, 0xffc71585_argb)
    DEF_BRUSH(midnight_blue, 0xff191970_argb)
    DEF_BRUSH(mint_cream, 0xfff5fffa_argb)
    DEF_BRUSH(misty_rose, 0xffffe4e1_argb)
    DEF_BRUSH(moccasin, 0xffffe4b5_argb)
    DEF_BRUSH(navajo_white, 0xffffdead_argb)
    DEF_BRUSH(navy, 0xff000080_argb)
    DEF_BRUSH(old_lace, 0xfffdf5e6_argb)
    DEF_BRUSH(olive, 0xff808000_argb)
    DEF_BRUSH(olive_drab, 0xff6b8e23_argb)
    DEF_BRUSH(orange, 0xffffa500_argb)
    DEF_BRUSH(orange_red, 0xffff4500_argb)
    DEF_BRUSH(orchid, 0xffda70d6_argb)
    DEF_BRUSH(pale_goldenrod, 0xffeee8aa_argb)
    DEF_BRUSH(pale_green, 0xff98fb98_argb)
    DEF_BRUSH(pale_turquoise, 0xffafeeee_argb)
    DEF_BRUSH(pale_violet_red, 0xffdb7093_argb)
    DEF_BRUSH(papaya_whip, 0xffffefd5_argb)
    DEF_BRUSH(peach_puff, 0xffffdab9_argb)
    DEF_BRUSH(peru, 0xffcd853f_argb)
    DEF_BRUSH(pink, 0xffffc0cb_argb)
    DEF_BRUSH(plum, 0xffdda0dd_argb)
    DEF_BRUSH(powder_blue, 0xffb0e0e6_argb)
    DEF_BRUSH(purple, 0xff800080_argb)
    DEF_BRUSH(red, 0xffff0000_argb)
    DEF_BRUSH(rosy_brown, 0xffbc8f8f_argb)
    DEF_BRUSH(royal_blue, 0xff4169e1_argb)
    DEF_BRUSH(saddle_brown, 0xff8b4513_argb)
    DEF_BRUSH(salmon, 0xfffa8072_argb)
    DEF_BRUSH(sandy_brown, 0xfff4a460_argb)
    DEF_BRUSH(sea_green, 0xff2e8b57_argb)
    DEF_BRUSH(sea_shell, 0xfffff5ee_argb)
    DEF_BRUSH(sienna, 0xffa0522d_argb)
    DEF_BRUSH(silver, 0xffc0c0c0_argb)
    DEF_BRUSH(sky_blue, 0xff87ceeb_argb)
    DEF_BRUSH(slate_blue, 0xff6a5acd_argb)
    DEF_BRUSH(slate_gray, 0xff708090_argb)
    DEF_BRUSH(snow, 0xfffffafa_argb)
    DEF_BRUSH(spring_green, 0xff00ff7f_argb)
    DEF_BRUSH(steel_blue, 0xff4682b4_argb)
    DEF_BRUSH(tan, 0xffd2b48c_argb)
    DEF_BRUSH(teal, 0xff008080_argb)
    DEF_BRUSH(thistle, 0xffd8bfd8_argb)
    DEF_BRUSH(tomato, 0xffff6347_argb)
    DEF_BRUSH(turquoise, 0xff40e0d0_argb)
    DEF_BRUSH(violet, 0xffee82ee_argb)
    DEF_BRUSH(wheat, 0xfff5deb3_argb)
    DEF_BRUSH(white, 0xffffffff_argb)
    DEF_BRUSH(white_smoke, 0xfff5f5f5_argb)
    DEF_BRUSH(yellow, 0xffffff00_argb)
    DEF_BRUSH(yellow_green, 0xff9acd32_argb)

#undef DEF_BRUSH
};

END_IWL()

#endif // IWL_DRAWING_BRUSH_HPP_
