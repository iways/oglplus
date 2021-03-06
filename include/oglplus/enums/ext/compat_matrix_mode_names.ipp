/*
 *  .file oglplus/enums/ext/compat_matrix_mode_names.ipp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/oglplus/ext/compat_matrix_mode.txt' instead.
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

namespace enums {
OGLPLUS_LIB_FUNC StrLit _ValueName(
	CompatibilityMatrixMode*,
	GLenum value
)
#if (!OGLPLUS_LINK_LIBRARY || defined(OGLPLUS_IMPLEMENTING_LIBRARY)) && \
	!defined(OGLPLUS_IMPL_EVN_COMPATIBILITYMATRIXMODE)
#define OGLPLUS_IMPL_EVN_COMPATIBILITYMATRIXMODE
{
switch(value)
{
#if defined GL_PROJECTION
	case GL_PROJECTION: return StrLit("PROJECTION");
#endif
#if defined GL_MODELVIEW
	case GL_MODELVIEW: return StrLit("MODELVIEW");
#endif
	default:;
}
OGLPLUS_FAKE_USE(value);
return StrLit();
}
#else
;
#endif
} // namespace enums

