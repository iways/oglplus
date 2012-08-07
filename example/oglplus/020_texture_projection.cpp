/**
 *  @example oglplus/020_texture_projection.cpp
 *  @brief Shows how to project a texture on a cube
 *
 *  @oglplus_screenshot{020_texture_projection}
 *
 *  Copyright 2008-2012 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#include <oglplus/gl.hpp>
#include <oglplus/all.hpp>
#include <oglplus/shapes/cube.hpp>
#include <oglplus/images/load.hpp>
#include <oglplus/bound/texture.hpp>

#include <cmath>

#include "example.hpp"

namespace oglplus {

class CubeExample : public Example
{
private:
	// helper object building cube vertex attributes
	shapes::Cube make_cube;
	// helper object encapsulating cube drawing instructions
	shapes::DrawingInstructions cube_instr;
	// indices pointing to cube primitive elements
	shapes::Cube::IndexArray cube_indices;

	// wrapper around the current OpenGL context
	Context gl;

	// Vertex shader
	VertexShader vs;

	// Fragment shader
	FragmentShader fs;

	// Program
	Program prog;

	// Handles to uniforms in prog
	LazyUniform<Vec3f> light_pos;
	LazyUniform<Mat4f>
		projection_matrix,
		tex_projection_matrix,
		model_matrix;

	// A vertex array object for the rendered cube
	VertexArray cube;

	// VBOs for the cube's vertex attributes
	Buffer verts, normals;

	// The stained glass texture
	Texture tex;
public:
	CubeExample(void)
	 : cube_instr(make_cube.Instructions())
	 , cube_indices(make_cube.Indices())
	 , light_pos(prog, "LightPos")
	 , projection_matrix(prog, "ProjectionMatrix")
	 , tex_projection_matrix(prog, "TexProjectionMatrix")
	 , model_matrix(prog, "ModelMatrix")
	{
		// Set the vertex shader source
		vs.Source(
			"#version 330\n"
			"uniform mat4 ProjectionMatrix, CameraMatrix, ModelMatrix;"
			"uniform mat4 TexProjectionMatrix;"
			"in vec4 Position;"
			"in vec3 Normal;"
			"out vec3 vertNormal;"
			"out vec3 vertLight;"
			"out vec4 vertTexCoord;"
			"uniform vec3 LightPos;"
			"void main(void)"
			"{"
			"	vertNormal = ("
			"		ModelMatrix *"
			"		vec4(-Normal, 0.0)"
			"	).xyz;"
			"	vertLight = ("
			"		vec4(LightPos, 0.0)-"
			"		ModelMatrix * Position"
			"	).xyz;"
			"	vertTexCoord = "
			"		TexProjectionMatrix *"
			"		ModelMatrix *"
			"		Position;"
			"	gl_Position = "
			"		ProjectionMatrix *"
			"		CameraMatrix *"
			"		ModelMatrix *"
			"		Position;"
			"}"
		);
		// compile it
		vs.Compile();

		// set the fragment shader source
		fs.Source(
			"#version 330\n"
			"uniform sampler2D TexUnit;"
			"in vec3 vertNormal;"
			"in vec3 vertLight;"
			"in vec4 vertTexCoord;"
			"out vec4 fragColor;"
			"void main(void)"
			"{"
			"	float l = length(vertLight);"
			"	float d = l != 0.0 ? dot("
			"		vertNormal, "
			"		normalize(vertLight)"
			"	) / l : 0.0;"
			"	float i = 0.1 + 4.2*max(d, 0.0);"
			"	vec2 coord = vertTexCoord.st/vertTexCoord.q;"
			"	vec4 t  = texture(TexUnit, coord*0.5 + 0.5);"
			"	fragColor = vec4(t.rgb*i*sqrt(1.0-t.a), 1.0);"
			"}"
		);
		// compile it
		fs.Compile();

		// attach the shaders to the program
		prog.AttachShader(vs);
		prog.AttachShader(fs);
		// link and use it
		prog.Link();
		prog.Use();

		// bind the VAO for the cube
		cube.Bind();

		verts.Bind(Buffer::Target::Array);
		{
			std::vector<GLfloat> data;
			GLuint n_per_vertex = make_cube.Positions(data);
			Buffer::Data(Buffer::Target::Array, data);
			VertexAttribArray attr(prog, "Position");
			attr.Setup(n_per_vertex, DataType::Float);
			attr.Enable();
		}

		normals.Bind(Buffer::Target::Array);
		{
			std::vector<GLfloat> data;
			GLuint n_per_vertex = make_cube.Normals(data);
			Buffer::Data(Buffer::Target::Array, data);
			VertexAttribArray attr(prog, "Normal");
			attr.Setup(n_per_vertex, DataType::Float);
			attr.Enable();
		}

		// setup the texture
		{
			auto bound_tex = Bind(tex, Texture::Target::_2D);
			bound_tex.Image2D(images::LoadTexture("flower_glass"));
			bound_tex.GenerateMipmap();
			bound_tex.BorderColor(Vec4f(1.0f, 1.0f, 1.0f, 0.0f));
			bound_tex.MinFilter(TextureMinFilter::LinearMipmapLinear);
			bound_tex.MagFilter(TextureMagFilter::Linear);
			bound_tex.WrapS(TextureWrap::ClampToBorder);
			bound_tex.WrapT(TextureWrap::ClampToBorder);
		}
		//
		UniformSampler(prog, "TexUnit").Set(0);
		Uniform<Mat4f>(prog, "CameraMatrix").Set(
			CamMatrixf::LookingAt(Vec3f(0.0f, 1.0f, 2.0f), Vec3f())
		);
		//
		gl.ClearColor(0.1f, 0.1f, 0.1f, 0.0f);
		gl.ClearDepth(1.0f);
		gl.Enable(Capability::DepthTest);
		gl.Enable(Capability::CullFace);
		gl.FrontFace(make_cube.FaceWinding());
	}

	void Reshape(size_t width, size_t height)
	{
		gl.Viewport(width, height);
		prog.Use();
		projection_matrix.Set(
			CamMatrixf::PerspectiveX(
				Degrees(48),
				double(width)/height,
				1, 100
			)
		);
	}

	void Render(double time)
	{
		gl.Clear().ColorBuffer().DepthBuffer();
		//
		Vec3f lightPos(-1.0f, 2.0f, 2.0f);
		lightPos *= (1.0f - SineWave(time/5.0f)*0.4f);
		light_pos = lightPos;

		tex_projection_matrix.Set(
			CamMatrixf::PerspectiveX(Degrees(10), 1.0, 1, 100) *
			CamMatrixf::LookingAt(lightPos, Vec3f())
		);

		// set the model matrix
		model_matrix.Set(
			ModelMatrixf::RotationY(FullCircles(time * 0.1))
		);

		cube.Bind();
		gl.CullFace(Face::Front);
		cube_instr.Draw(cube_indices);
	}

	bool Continue(double time)
	{
		return time < 30.0;
	}
};

std::unique_ptr<Example> makeExample(const ExampleParams& /*params*/)
{
	return std::unique_ptr<Example>(new CubeExample);
}

} // namespace oglplus
