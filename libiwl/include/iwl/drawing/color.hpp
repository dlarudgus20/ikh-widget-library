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

#ifndef IWL_DRAWING_COLOR_HPP_
#define IWL_DRAWING_COLOR_HPP_

#include "../defines.hpp"

BEGIN_IWL()

struct color
{
    float a, r, g, b;

    static constexpr color from_argb(std::uint_fast32_t argb)
    {
        return color {
            (argb >> 24) / 255.f,
            ((argb >> 16) & 0xff) / 255.f,
            ((argb >> 8) & 0xff) / 255.f,
            (argb & 0xff) / 255.f
        };
    }
    static constexpr color from_rgb(std::uint_fast32_t rgb)
    {
        return from_argb(0xff000000 | rgb);
    }

    constexpr std::uint_fast32_t argb() const
    {
        return (static_cast<uint_fast32_t>(a * 255) << 24)
            | (static_cast<uint_fast32_t>(r * 255) << 16)
            | (static_cast<uint_fast32_t>(g * 255) << 8)
            | static_cast<uint_fast32_t>(b * 255);
    }
};
inline namespace literals
{
    constexpr color operator ""_argb(unsigned long long argb)
    {
        return color::from_argb(static_cast<std::uint_fast32_t>(argb));
    }
    constexpr color operator ""_rgb(unsigned long long rgb)
    {
        return color::from_rgb(static_cast<std::uint_fast32_t>(rgb));
    }
}

struct colors
{
    colors() = delete;
#define DEF_COLOR(name, colobj) static constexpr const color name() { return colobj; }
    DEF_COLOR(alice_blue, 0xfff0f8ff_argb)
    DEF_COLOR(antique_white, 0xfffaebd7_argb)
    DEF_COLOR(aqua, 0xff00fffff_argb)
    DEF_COLOR(aquamarine, 0xff7fffd4_argb)
    DEF_COLOR(azure, 0xfff0ffff_argb)
    DEF_COLOR(beige, 0xfff5f5dc_argb)
    DEF_COLOR(bisque, 0xffffe5c4_argb)
    DEF_COLOR(black, 0xff000000_argb)
    DEF_COLOR(blanched_almond, 0xffffebcd_argb)
    DEF_COLOR(blue, 0xff0000ff_argb)
    DEF_COLOR(blue_violet, 0xff8a2be2_argb)
    DEF_COLOR(brown, 0xff8a2be2_argb)
    DEF_COLOR(burly_wood, 0xffde8887_argb)
    DEF_COLOR(cadet_blue, 0xff5f9ea0_argb)
    DEF_COLOR(chartreuse, 0xff7fff00_argb)
    DEF_COLOR(chocolate, 0xffd2691e_argb)
    DEF_COLOR(coral, 0xffff7f50_argb)
    DEF_COLOR(cornflower_blue, 0xff6495ed_argb)
    DEF_COLOR(cornsilk, 0xfffff8dc_argb)
    DEF_COLOR(crimson, 0xffdc143c_argb)
    DEF_COLOR(cyan, 0xff00ffff_argb)
    DEF_COLOR(dark_blue, 0xff00008b_argb)
    DEF_COLOR(dark_cyan, 0xff008b8b_argb)
    DEF_COLOR(dark_goldenrod, 0xffb8860b_argb)
    DEF_COLOR(dark_gray, 0xffa9a9a9_argb)
    DEF_COLOR(dark_green, 0xff006400_argb)
    DEF_COLOR(dark_khaki, 0xffbdb76b_argb)
    DEF_COLOR(dark_magenta, 0xff8b008b_argb)
    DEF_COLOR(dark_olive_green, 0xff556b2f_argb)
    DEF_COLOR(dark_orange, 0xffff8c00_argb)
    DEF_COLOR(dark_orchid, 0xff9932cc_argb)
    DEF_COLOR(dark_red, 0xff8b0000_argb)
    DEF_COLOR(dark_salmon, 0xffe9967a_argb)
    DEF_COLOR(dark_sea_green, 0xff8fbc8f_argb)
    DEF_COLOR(dark_slate_blue, 0xff483d8b_argb)
    DEF_COLOR(dark_slate_gray, 0xff2f4f4f_argb)
    DEF_COLOR(dark_turquoise, 0xff00ced1_argb)
    DEF_COLOR(dark_violet, 0xff9400d3_argb)
    DEF_COLOR(deep_pink, 0xffff1493_argb)
    DEF_COLOR(deep_sky_blue, 0xff00bfff_argb)
    DEF_COLOR(dim_gray, 0xff696969_argb)
    DEF_COLOR(dodger_blue, 0xff1e90ff_argb)
    DEF_COLOR(firebrick, 0xffb22222_argb)
    DEF_COLOR(floral_white, 0xfffffaf0_argb)
    DEF_COLOR(forest_green, 0xff228b22_argb)
    DEF_COLOR(fuchsia, 0xffff00ff_argb)
    DEF_COLOR(gainsboro, 0xffdcdcdc_argb)
    DEF_COLOR(ghost_white, 0xfff8f8ff_argb)
    DEF_COLOR(gold, 0xffffd700_argb)
    DEF_COLOR(goldenrod, 0xffdaa520_argb)
    DEF_COLOR(gray, 0xff808080_argb)
    DEF_COLOR(green, 0xff008000_argb)
    DEF_COLOR(green_yellow, 0xffadff2f_argb)
    DEF_COLOR(honeydew, 0xfff0fff0_argb)
    DEF_COLOR(hot_pink, 0xffff69b4_argb)
    DEF_COLOR(indian_red, 0xffcd5c5c_argb)
    DEF_COLOR(indigo, 0xff4b0082_argb)
    DEF_COLOR(ivory, 0xfffffff0_argb)
    DEF_COLOR(khaki, 0xfff0e68c_argb)
    DEF_COLOR(lavender, 0xffe6e6fa_argb)
    DEF_COLOR(lavender_blush, 0xfffff0f5_argb)
    DEF_COLOR(lawn_green, 0xff7cfc00_argb)
    DEF_COLOR(lemon_chiffon, 0xfffffacd_argb)
    DEF_COLOR(light_blue, 0xffadd8e6_argb)
    DEF_COLOR(light_coral, 0xfff08080_argb)
    DEF_COLOR(light_cyan, 0xffe0ffff_argb)
    DEF_COLOR(light_goldenrod_yellow, 0xfffafad2_argb)
    DEF_COLOR(light_gray, 0xffd3d3d3_argb)
    DEF_COLOR(light_green, 0xff90ee90_argb)
    DEF_COLOR(light_pink, 0xffffb6c1_argb)
    DEF_COLOR(light_salmon, 0xffffa07a_argb)
    DEF_COLOR(light_sea_green, 0xff20b2aa_argb)
    DEF_COLOR(light_sky_blue, 0xff87cefa_argb)
    DEF_COLOR(light_slate_gray, 0xff778899_argb)
    DEF_COLOR(light_steel_blue, 0xffb0c4de_argb)
    DEF_COLOR(light_yellow, 0xffffffe0_argb)
    DEF_COLOR(lime, 0xff00ff00_argb)
    DEF_COLOR(lime_green, 0xff32cd32_argb)
    DEF_COLOR(linen, 0xfffaf0e6_argb)
    DEF_COLOR(magenta, 0xffff00ff_argb)
    DEF_COLOR(maroon, 0xff800000_argb)
    DEF_COLOR(medium_aquamarine, 0xff66cdaa_argb)
    DEF_COLOR(medium_blue, 0xff0000cd_argb)
    DEF_COLOR(medium_orchid, 0xffba55d3_argb)
    DEF_COLOR(medium_purple, 0xff9370db_argb)
    DEF_COLOR(medium_sea_green, 0xff3cb371_argb)
    DEF_COLOR(medium_slate_blue, 0xff7b68ee_argb)
    DEF_COLOR(medium_spring_green, 0xff00fa9a_argb)
    DEF_COLOR(medium_turquoise, 0xff48d1cc_argb)
    DEF_COLOR(medium_violet_red, 0xffc71585_argb)
    DEF_COLOR(midnight_blue, 0xff191970_argb)
    DEF_COLOR(mint_cream, 0xfff5fffa_argb)
    DEF_COLOR(misty_rose, 0xffffe4e1_argb)
    DEF_COLOR(moccasin, 0xffffe4b5_argb)
    DEF_COLOR(navajo_white, 0xffffdead_argb)
    DEF_COLOR(navy, 0xff000080_argb)
    DEF_COLOR(old_lace, 0xfffdf5e6_argb)
    DEF_COLOR(olive, 0xff808000_argb)
    DEF_COLOR(olive_drab, 0xff6b8e23_argb)
    DEF_COLOR(orange, 0xffffa500_argb)
    DEF_COLOR(orange_red, 0xffff4500_argb)
    DEF_COLOR(orchid, 0xffda70d6_argb)
    DEF_COLOR(pale_goldenrod, 0xffeee8aa_argb)
    DEF_COLOR(pale_green, 0xff98fb98_argb)
    DEF_COLOR(pale_turquoise, 0xffafeeee_argb)
    DEF_COLOR(pale_violet_red, 0xffdb7093_argb)
    DEF_COLOR(papaya_whip, 0xffffefd5_argb)
    DEF_COLOR(peach_puff, 0xffffdab9_argb)
    DEF_COLOR(peru, 0xffcd853f_argb)
    DEF_COLOR(pink, 0xffffc0cb_argb)
    DEF_COLOR(plum, 0xffdda0dd_argb)
    DEF_COLOR(powder_blue, 0xffb0e0e6_argb)
    DEF_COLOR(purple, 0xff800080_argb)
    DEF_COLOR(red, 0xffff0000_argb)
    DEF_COLOR(rosy_brown, 0xffbc8f8f_argb)
    DEF_COLOR(royal_blue, 0xff4169e1_argb)
    DEF_COLOR(saddle_brown, 0xff8b4513_argb)
    DEF_COLOR(salmon, 0xfffa8072_argb)
    DEF_COLOR(sandy_brown, 0xfff4a460_argb)
    DEF_COLOR(sea_green, 0xff2e8b57_argb)
    DEF_COLOR(sea_shell, 0xfffff5ee_argb)
    DEF_COLOR(sienna, 0xffa0522d_argb)
    DEF_COLOR(silver, 0xffc0c0c0_argb)
    DEF_COLOR(sky_blue, 0xff87ceeb_argb)
    DEF_COLOR(slate_blue, 0xff6a5acd_argb)
    DEF_COLOR(slate_gray, 0xff708090_argb)
    DEF_COLOR(snow, 0xfffffafa_argb)
    DEF_COLOR(spring_green, 0xff00ff7f_argb)
    DEF_COLOR(steel_blue, 0xff4682b4_argb)
    DEF_COLOR(tan, 0xffd2b48c_argb)
    DEF_COLOR(teal, 0xff008080_argb)
    DEF_COLOR(thistle, 0xffd8bfd8_argb)
    DEF_COLOR(tomato, 0xffff6347_argb)
    DEF_COLOR(turquoise, 0xff40e0d0_argb)
    DEF_COLOR(violet, 0xffee82ee_argb)
    DEF_COLOR(wheat, 0xfff5deb3_argb)
    DEF_COLOR(white, 0xffffffff_argb)
    DEF_COLOR(white_smoke, 0xfff5f5f5_argb)
    DEF_COLOR(yellow, 0xffffff00_argb)
    DEF_COLOR(yellow_green, 0xff9acd32_argb)
#undef DEF_COLOR
};

END_IWL()

#endif // IWL_DRAWING_COLOR_HPP_
