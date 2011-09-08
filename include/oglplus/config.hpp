/**
 *  @file oglplus/config.hpp
 *  @brief Compile-time configuration options
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2011 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef OGLPLUS_CONFIG_1107121519_HPP
#define OGLPLUS_CONFIG_1107121519_HPP

namespace oglplus {

//TODO: detect support by compiler and define only if necessary
#define nullptr 0
#define constexpr const

#ifndef OGLPLUS_DONT_TEST_OBJECT_TYPE
#define OGLPLUS_DONT_TEST_OBJECT_TYPE 0
#endif

#ifndef OGLPLUS_NO_OBJECT_NAMES
#define OGLPLUS_NO_OBJECT_NAMES 0
#endif

} // namespace oglplus

#endif // include guard
