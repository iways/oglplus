/**
 *  @file oglplus/text/stb_truetype.hpp
 *  @brief Bitmap-font-based text rendering.
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_TEXT_STB_TRUETYPE_HPP
#define OGLPLUS_TEXT_STB_TRUETYPE_HPP

#include <oglplus/config.hpp>

#include <oglplus/text/bitmap_glyph/rendering.hpp>
#include <oglplus/text/bitmap_glyph/font.hpp>
#include <oglplus/text/stb_truetype/font_essence.hpp>

namespace oglplus {
namespace text {

typedef BitmapGlyphFontTpl<STBTTFontEssence> STBTrueTypeFont;
typedef BitmapGlyphRenderingTpl<STBTrueTypeFont> STBTrueTypeRendering;

} // namespace text
} // namespace oglplus

#endif // include guard
