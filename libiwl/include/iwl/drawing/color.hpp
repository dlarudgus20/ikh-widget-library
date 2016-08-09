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
    static constexpr color from_argb(std::uint_fast32_t code)
    {
        return color {
            (code >> 24) / 255.f,
            ((code >> 16) & 0xff) / 255.f,
            ((code >> 8) & 0xff) / 255.f,
            (code & 0xff) / 255.f
        };
    }
    static constexpr color from_rgb(std::uint_fast32_t code)
    {
        return from_argb(0xff000000 | code);
    }
};
inline namespace literals
{
    constexpr color operator ""_color(unsigned long long code)
    {
        return color::from_argb(static_cast<std::uint_fast32_t>(code));
    }
}

struct colors
{
    colors() = delete;
#define DEF_COLOR(name, colobj) static constexpr const color name() { return colobj; }
    DEF_COLOR(alice_blue, 0xfff0f8ff_color)
    DEF_COLOR(antique_white, 0xfffaebd7_color)
    DEF_COLOR(aqua, 0xff00fffff_color)
    DEF_COLOR(aquamarine, 0xff7fffd4_color)
    DEF_COLOR(azure, 0xfff0ffff_color)
    DEF_COLOR(beige, 0xfff5f5dc_color)
    DEF_COLOR(bisque, 0xffffe5c4_color)
    DEF_COLOR(black, 0xff000000_color)
    DEF_COLOR(blanched_almond, 0xffffebcd_color)
    DEF_COLOR(blue, 0xff0000ff_color)
    DEF_COLOR(blue_violet, 0xff8a2be2_color)
    DEF_COLOR(brown, 0xff8a2be2_color)
    DEF_COLOR(burly_wood, 0xffde8887_color)
    DEF_COLOR(cadet_blue, 0xff5f9ea0_color)
    DEF_COLOR(chartreuse, 0xff7fff00_color)
    DEF_COLOR(chocolate, 0xffd2691e_color)
    DEF_COLOR(coral, 0xffff7f50_color)
    DEF_COLOR(cornflower_blue, 0xff6495ed_color)
    DEF_COLOR(cornsilk, 0xfffff8dc_color)
    DEF_COLOR(crimson, 0xffdc143c_color)
    DEF_COLOR(cyan, 0xff00ffff_color)
    DEF_COLOR(dark_blue, 0xff00008b_color)
    DEF_COLOR(dark_cyan, 0xff008b8b_color)
    DEF_COLOR(DarkGoldenrod, 0xFFB8860B_color)
    DEF_COLOR(DarkGray, 0xffa9a9a9_color)
    DEF_COLOR(DarkGreen, 0xff006400_color)
    DEF_COLOR(DarkKhaki, 0xffbdb76b_color)
    DEF_COLOR(DarkMagenta, 0xff8b008b_color)
    DEF_COLOR(DarkOliveGreen, 0xff556b2f_color)
    DEF_COLOR(DarkOrange, 0xffff8c00_color)
    DEF_COLOR(DarkOrchid, 0xff9932cc_color)
    DEF_COLOR(DarkRed, 0xff8b0000_color)
    DEF_COLOR(DarkSalmon, 0xffe9967a_color)
    DEF_COLOR(DarkSeaGreen, 0xff8fbc8f_color)
    DEF_COLOR(DarkSlateBlue, 0xff483d8b_color)
    DEF_COLOR(DarkSlateGray, 0xff2f4f4f_color)
    DEF_COLOR(DarkTurquoise, 0xff00ced1_color)
    DEF_COLOR(DarkViolet, 0xff9400d3_color)
    DEF_COLOR(DeepPink, 0xffff1493_color)
    DEF_COLOR(DeepSkyBlue, 0xff00bfff_color)
    DEF_COLOR(DimGray, 0xff696969_color)
    DEF_COLOR(DodgerBlue, 0xff1e90ff_color)
    DEF_COLOR(Firebrick, 0xffb22222_color)
    DEF_COLOR(FloralWhite, 0xfffffaf0_color)
    DEF_COLOR(ForestGreen, 0xff228b22_color)
    DEF_COLOR(Fuchsia, 0xffff00ff_color)
    DEF_COLOR(Gainsboro, 0xffdcdcdc_color)
    DEF_COLOR(GhostWhite, 0xfff8f8ff_color)
    DEF_COLOR(Gold, 0xffffd700_color)
    DEF_COLOR(Goldenrod, 0xffdaa520_color)
    DEF_COLOR(Gray, 0xff808080_color)
    DEF_COLOR(Green, 0xff008000_color)
    DEF_COLOR(GreenYellow, 0xffadff2f_color)
    DEF_COLOR(Honeydew, 0xfff0fff0_color)
    DEF_COLOR(HotPink, 0xffff69b4_color)
    DEF_COLOR(IndianRed, 0xffcd5c5c_color)
    DEF_COLOR(Indigo, 0xff4b0082_color)
    DEF_COLOR(Ivory, 0xfffffff0_color)
    DEF_COLOR(Khaki, 0xfff0e68c_color)
    DEF_COLOR(Lavender, 0xffe6e6fa_color)
    DEF_COLOR(LavenderBlush, 0xfffff0f5_color)
    DEF_COLOR(LawnGreen, 0xff7cfc00_color)
    DEF_COLOR(LemonChiffon, 0xfffffacd_color)
    DEF_COLOR(LightBlue, 0xffadd8e6_color)
    DEF_COLOR(LightCoral, 0xfff08080_color)
    DEF_COLOR(LightCyan, 0xffe0ffff_color)
    DEF_COLOR(LightGoldenrodYellow, 0xfffafad2_color)
    DEF_COLOR(LightGray, 0xffd3d3d3_color)
    DEF_COLOR(LightGreen, 0xff90ee90_color)
    DEF_COLOR(LightPink, 0xffffb6c1_color)
    DEF_COLOR(LightSalmon, 0xffffa07a_color)
    DEF_COLOR(LightSeaGreen, 0xff20b2aa_color)
    DEF_COLOR(LightSkyBlue, 0xff87cefa_color)
    DEF_COLOR(LightSlateGray, 0xff778899_color)
    DEF_COLOR(LightSteelBlue, 0xffb0c4de_color)
    DEF_COLOR(LightYellow, 0xffffffe0_color)
    DEF_COLOR(Lime, 0xff00ff00_color)
    DEF_COLOR(LimeGreen, 0xff32cd32_color)
    DEF_COLOR(Linen, 0xfffaf0e6_color)
    DEF_COLOR(Magenta, 0xffff00ff_color)
    DEF_COLOR(Maroon, 0xff800000_color)
    DEF_COLOR(MediumAquamarine, 0xff66cdaa_color)
    DEF_COLOR(MediumBlue, 0xff0000cd_color)
    DEF_COLOR(MediumOrchid, 0xffba55d3_color)
    DEF_COLOR(MediumPurple, 0xff9370db_color)
    DEF_COLOR(MediumSeaGreen, 0xff3cb371_color)
    DEF_COLOR(MediumSlateBlue, 0xff7b68ee_color)
    DEF_COLOR(MediumSpringGreen, 0xff00fa9a_color)
    DEF_COLOR(MediumTurquoise, 0xff48d1cc_color)
    DEF_COLOR(MediumVioletRed, 0xffc71585_color)
    DEF_COLOR(MidnightBlue, 0xff191970_color)
    DEF_COLOR(MintCream, 0xfff5fffa_color)
    DEF_COLOR(MistyRose, 0xffffe4e1_color)
    DEF_COLOR(Moccasin, 0xffffe4b5_color)
    DEF_COLOR(NavajoWhite, 0xffffdead_color)
    DEF_COLOR(Navy, 0xff000080_color)
    DEF_COLOR(OldLace, 0xfffdf5e6_color)
    DEF_COLOR(Olive, 0xff808000_color)
    DEF_COLOR(OliveDrab, 0xff6b8e23_color)
    DEF_COLOR(Orange, 0xffffa500_color)
    DEF_COLOR(OrangeRed, 0xffff4500_color)
    DEF_COLOR(Orchid, 0xffda70d6_color)
    DEF_COLOR(PaleGoldenrod, 0xffeee8aa_color)
    DEF_COLOR(PaleGreen, 0xff98fb98_color)
    DEF_COLOR(PaleTurquoise, 0xffafeeee_color)
    DEF_COLOR(PaleVioletRed, 0xffdb7093_color)
    DEF_COLOR(PapayaWhip, 0xffffefd5_color)
    DEF_COLOR(PeachPuff, 0xffffdab9_color)
    DEF_COLOR(Peru, 0xffcd853f_color)
    DEF_COLOR(Pink, 0xffffc0cb_color)
    DEF_COLOR(Plum, 0xffdda0dd_color)
    DEF_COLOR(PowderBlue, 0xffb0e0e6_color)
    DEF_COLOR(Purple, 0xff800080_color)
    DEF_COLOR(Red, 0xffff0000_color)
    DEF_COLOR(RosyBrown, 0xffbc8f8f_color)
    DEF_COLOR(RoyalBlue, 0xff4169e1_color)
    DEF_COLOR(SaddleBrown, 0xff8b4513_color)
    DEF_COLOR(Salmon, 0xfffa8072_color)
    DEF_COLOR(SandyBrown, 0xfff4a460_color)
    DEF_COLOR(SeaGreen, 0xff2e8b57_color)
    DEF_COLOR(SeaShell, 0xfffff5ee_color)
    DEF_COLOR(Sienna, 0xffa0522d_color)
    DEF_COLOR(Silver, 0xffc0c0c0_color)
    DEF_COLOR(SkyBlue, 0xff87ceeb_color)
    DEF_COLOR(SlateBlue, 0xff6a5acd_color)
    DEF_COLOR(SlateGray, 0xff708090_color)
    DEF_COLOR(Snow, 0xfffffafa_color)
    DEF_COLOR(SpringGreen, 0xff00ff7f_color)
    DEF_COLOR(SteelBlue, 0xff4682b4_color)
    DEF_COLOR(Tan, 0xffd2b48c_color)
    DEF_COLOR(Teal, 0xff008080_color)
    DEF_COLOR(Thistle, 0xffd8bfd8_color)
    DEF_COLOR(Tomato, 0xffff6347_color)
    DEF_COLOR(Turquoise, 0xff40e0d0_color)
    DEF_COLOR(Violet, 0xffee82ee_color)
    DEF_COLOR(Wheat, 0xfff5deb3_color)
    DEF_COLOR(White, 0xffffffff_color)
    DEF_COLOR(WhiteSmoke, 0xfff5f5f5_color)
    DEF_COLOR(Yellow, 0xffffff00_color)
    DEF_COLOR(YellowGreen, 0xff9acd32_color)
#undef DEF_COLOR
};

END_IWL()

#endif // IWL_DRAWING_COLOR_HPP_
