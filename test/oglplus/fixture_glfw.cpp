/*
 *  .file test/fixture_glfw.cpp
 *  Implements GLFW-based test fixture
 *
 *  Copyright 2011-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#include <oglplus/gl.hpp>

#include <GL/glfw.h>

#include <oglplus/config.hpp>

#include <stdexcept>
#include <cassert>

#include "fixture.hpp"

namespace oglplus {

class GLFWTestFixtureBase
{
public:
	GLFWTestFixtureBase(void)
	{
		if(!glfwInit())
			throw std::runtime_error("GLFW initialization error");
		if(!glfwOpenWindow(
			128, 128,
			8, 8, 8, 8,
			32, 8,
			GLFW_WINDOW
		)) throw std::runtime_error("Error creating GLFW window");
		glfwSetWindowTitle("OGLplus test");
	}

	~GLFWTestFixtureBase(void)
	{
		glfwTerminate();
	}
};

class GLFWTestFixture
 : public GLFWTestFixtureBase
{
private:
	oglplus::GLAPIInitializer gl_api_init;
public:
	GLFWTestFixture(void)
	 : GLFWTestFixtureBase()
	{ }
};

TestFixture::TestFixture(void)
 : _pimpl(static_cast<void*>(new GLFWTestFixture()))
{ }

TestFixture::TestFixture(TestFixture&& tmp)
 : _pimpl(tmp._pimpl)
{
	tmp._pimpl = nullptr;
}

TestFixture::~TestFixture(void)
{
	if(_pimpl) delete static_cast<GLFWTestFixture*>(_pimpl);
}

} // namespace oglplus
