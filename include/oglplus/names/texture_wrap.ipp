/*
 *  .file oglplus/names/texture_wrap.ipp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/texture_wrap.txt' instead.
 *
 *  Copyright 2010-2012 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

switch(GLenum(value))
{
#if defined GL_CLAMP_TO_EDGE
	case GL_CLAMP_TO_EDGE: return "CLAMP_TO_EDGE";
#endif
#if defined GL_REPEAT
	case GL_REPEAT: return "REPEAT";
#endif
#if defined GL_CLAMP_TO_BORDER
	case GL_CLAMP_TO_BORDER: return "CLAMP_TO_BORDER";
#endif
#if defined GL_MIRRORED_REPEAT
	case GL_MIRRORED_REPEAT: return "MIRRORED_REPEAT";
#endif
	default:;
}
