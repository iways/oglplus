/*
 *  .file eglplus/enums/context_flag_names.ipp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/eglplus/context_flag.txt' instead.
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

namespace enums {
EGLPLUS_LIB_FUNC StrLit _ValueName(
	ContextFlag*,
	EGLenum value
)
#if (!EGLPLUS_LINK_LIBRARY || defined(EGLPLUS_IMPLEMENTING_LIBRARY)) && \
	!defined(EGLPLUS_IMPL_EVN_CONTEXTFLAG)
#define EGLPLUS_IMPL_EVN_CONTEXTFLAG
{
switch(value)
{
#if defined EGL_CONTEXT_OPENGL_DEBUG_BIT_KHR
	case EGL_CONTEXT_OPENGL_DEBUG_BIT_KHR: return StrLit("CONTEXT_OPENGL_DEBUG_BIT_KHR");
#endif
#if defined EGL_CONTEXT_OPENGL_FORWARD_COMPATIBLE_BIT_KHR
	case EGL_CONTEXT_OPENGL_FORWARD_COMPATIBLE_BIT_KHR: return StrLit("CONTEXT_OPENGL_FORWARD_COMPATIBLE_BIT_KHR");
#endif
#if defined EGL_CONTEXT_OPENGL_ROBUST_ACCESS_BIT_KHR
	case EGL_CONTEXT_OPENGL_ROBUST_ACCESS_BIT_KHR: return StrLit("CONTEXT_OPENGL_ROBUST_ACCESS_BIT_KHR");
#endif
	default:;
}
EGLPLUS_FAKE_USE(value);
return StrLit();
}
#else
;
#endif
} // namespace enums

