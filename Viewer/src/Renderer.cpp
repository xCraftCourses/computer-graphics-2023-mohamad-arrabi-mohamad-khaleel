#define _USE_MATH_DEFINES
#include <cmath>
#include <algorithm>

#include "Renderer.h"
#include "InitShader.h"

#define INDEX(width,x,y,c) ((x)+(y)*(width))*3+(c)
#define Z_INDEX(width,x,y) ((x)+(y)*(width))
// test
Renderer::Renderer(int viewport_width, int viewport_height) :
	viewport_width(viewport_width),
	viewport_height(viewport_height)
{
	InitOpenglRendering();
	CreateBuffers(viewport_width, viewport_height);
}

Renderer::~Renderer()
{
	delete[] color_buffer;
}

void Renderer::PutPixel(int i, int j, const glm::vec3& color)
{
	if (i < 0) return; if (i >= viewport_width) return;
	if (j < 0) return; if (j >= viewport_height) return;
	
	color_buffer[INDEX(viewport_width, i, j, 0)] = color.x;
	color_buffer[INDEX(viewport_width, i, j, 1)] = color.y;
	color_buffer[INDEX(viewport_width, i, j, 2)] = color.z;
}

void Renderer::DrawLine(const glm::ivec2& p1, const glm::ivec2& p2, const glm::vec3& color)
{
	// TODO: Implement bresenham algorithm
	// https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm
	GLfloat a, e, p, q, x1, y1, x2, y2;
	if (p1.x > p2.x) {
		x1 = p2.x; y1 = p2.y;
		x2 = p1.x; y2 = p1.y;
	}
	else {
		x1 = p1.x; y1 = p1.y;
		x2 = p2.x; y2 = p2.y;
	}
	if (p1.x != p2.x)
		a = (float)(y2 - y1) / (float)(x2 - x1);
	p = x2 - x1; q = y2 - y1;
	e = -1 * p;
	if (x1 == x2) {
		if (q > 0) {
			while (y1 < y2 || y1 == y2) {
				PutPixel(x1, y1, color);
				y1++;
			}
		}
		else if (q < 0) {
			while (y1 > y2 || y1 == y2) {
				PutPixel(x1, y1, color);
				y1--;
			}
		}
	}
	else {
		if (a == 1) {
			while (x1 < x2 || x1 == x2) {
				PutPixel(x1, y1, color);
				x1++;
				y1++;
			}
		}
		if (a == 0) {
			while (x1 < x2 || x1 == x2) {
				PutPixel(x1, y1, color);
				x1++;
			}
		}
		if (a == -1) {
			while (x1 < x2 || x1 == x2) {
				PutPixel(x1, y1, color);
				x1++;
				y1--;
			}
		}
		if (0 < a && a < 1) {
			while (x1 < x2 || x1 == x2) {
				if (e > 0) {
					y1++;
					e = e - (2 * p);
				}
				PutPixel(x1, y1, color);
				x1++;
				e = e + (2 * q);
			}
		}
		if (a > 1) {
			while (y1 < y2 || y1 == y2) {
				if (e > 0) {
					x1++;
					e = e - (2 * q);
				}
				PutPixel(x1, y1, color);
				y1++;
				e = e + (2 * p);
			}
		}
		if (-1 < a && a < 0) {
			e = p;
			while (x1 < x2 || x1 == x2) {
				if (e < 0) {
					y1--;
					e = e + (2 * p);
				}
				PutPixel(x1, y1, color);
				x1++;
				e = e + (2 * q);
			}
		}
		if (a < -1) {
			while (y1 > y2 || y1 == y2) {
				if (e > 0) {
					x1++;
					e = e + (2 * q);
				}
				PutPixel(x1, y1, color);
				y1--;
				e = e + (2 * p);
			}
		}
	}

void Renderer::CreateBuffers(int w, int h)
{
	CreateOpenglBuffer(); //Do not remove this line.
	color_buffer = new float[3 * w * h];
	ClearColorBuffer(glm::vec3(0.0f, 0.0f, 0.0f));
}

//##############################
//##OpenGL stuff. Don't touch.##
//##############################

// Basic tutorial on how opengl works:
// http://www.opengl-tutorial.org/beginners-tutorials/tutorial-2-the-first-triangle/
// don't linger here for now, we will have a few tutorials about opengl later.
void Renderer::InitOpenglRendering()
{
	// Creates a unique identifier for an opengl texture.
	glGenTextures(1, &gl_screen_tex);

	// Same for vertex array object (VAO). VAO is a set of buffers that describe a renderable object.
	glGenVertexArrays(1, &gl_screen_vtc);

	GLuint buffer;

	// Makes this VAO the current one.
	glBindVertexArray(gl_screen_vtc);

	// Creates a unique identifier for a buffer.
	glGenBuffers(1, &buffer);

	// (-1, 1)____(1, 1)
	//	     |\  |
	//	     | \ | <--- The exture is drawn over two triangles that stretch over the screen.
	//	     |__\|
	// (-1,-1)    (1,-1)
	const GLfloat vtc[]={
		-1, -1,
		 1, -1,
		-1,  1,
		-1,  1,
		 1, -1,
		 1,  1
	};

	const GLfloat tex[]={
		0,0,
		1,0,
		0,1,
		0,1,
		1,0,
		1,1};

	// Makes this buffer the current one.
	glBindBuffer(GL_ARRAY_BUFFER, buffer);

	// This is the opengl way for doing malloc on the gpu. 
	glBufferData(GL_ARRAY_BUFFER, sizeof(vtc)+sizeof(tex), NULL, GL_STATIC_DRAW);

	// memcopy vtc to buffer[0,sizeof(vtc)-1]
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vtc), vtc);

	// memcopy tex to buffer[sizeof(vtc),sizeof(vtc)+sizeof(tex)]
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(vtc), sizeof(tex), tex);

	// Loads and compiles a sheder.
	GLuint program = InitShader( "vshader.glsl", "fshader.glsl" );

	// Make this program the current one.
	glUseProgram(program);

	// Tells the shader where to look for the vertex position data, and the data dimensions.
	GLint  vPosition = glGetAttribLocation( program, "vPosition" );
	glEnableVertexAttribArray( vPosition );
	glVertexAttribPointer( vPosition,2,GL_FLOAT,GL_FALSE,0,0 );

	// Same for texture coordinates data.
	GLint  vTexCoord = glGetAttribLocation( program, "vTexCoord" );
	glEnableVertexAttribArray( vTexCoord );
	glVertexAttribPointer( vTexCoord,2,GL_FLOAT,GL_FALSE,0,(GLvoid *)sizeof(vtc) );

	//glProgramUniform1i( program, glGetUniformLocation(program, "texture"), 0 );

	// Tells the shader to use GL_TEXTURE0 as the texture id.
	glUniform1i(glGetUniformLocation(program, "texture"),0);
}

void Renderer::CreateOpenglBuffer()
{
	// Makes GL_TEXTURE0 the current active texture unit
	glActiveTexture(GL_TEXTURE0);

	// Makes glScreenTex (which was allocated earlier) the current texture.
	glBindTexture(GL_TEXTURE_2D, gl_screen_tex);

	// malloc for a texture on the gpu.
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, viewport_width, viewport_height, 0, GL_RGB, GL_FLOAT, NULL);
	glViewport(0, 0, viewport_width, viewport_height);
}

void Renderer::SwapBuffers()
{
	// Makes GL_TEXTURE0 the current active texture unit
	glActiveTexture(GL_TEXTURE0);

	// Makes glScreenTex (which was allocated earlier) the current texture.
	glBindTexture(GL_TEXTURE_2D, gl_screen_tex);

	// memcopy's colorBuffer into the gpu.
	glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, viewport_width, viewport_height, GL_RGB, GL_FLOAT, color_buffer);

	// Tells opengl to use mipmapping
	glGenerateMipmap(GL_TEXTURE_2D);

	// Make glScreenVtc current VAO
	glBindVertexArray(gl_screen_vtc);

	// Finally renders the data.
	glDrawArrays(GL_TRIANGLES, 0, 6);
}

void Renderer::ClearColorBuffer(const glm::vec3& color)
{
	for (int i = 0; i < viewport_width; i++)
	{
		for (int j = 0; j < viewport_height; j++)
		{
			PutPixel(i, j, color);
		}
	}
}

void Renderer::Render(const Scene& scene)
{
	// TODO: Replace this code with real scene rendering code
	int half_width = viewport_width / 2;
	int half_height = viewport_height / 2;
	/*glm::ivec2 v1(700, 200);
	glm::ivec2 v2(100, 500);
	glm::ivec3 color(255, 0,0);
	DrawLine(v1, v2, color);
	return;*/
	int x, y;
	glm::ivec3 color(255, 0, 0);
	glm::ivec2 v1(400, 400);
	glm::ivec2 v2(400, 200);
	DrawLine(v1, v2, color);
	glm::ivec2 v3(380, 400);
	glm::ivec2 v4(400, 200);
	int x_circle = 380;
	int y_circle = 400;
	int r = 20;
	int alpha = 0;
	for (; alpha <= 360;)
		{
			x = x_circle + r * cos(alpha * M_PI / 180);//475
			y = y_circle + r * sin(alpha * M_PI / 180);//543
			v4[0] = x;
			v4[1] = y;
			DrawLine(v3, v4, color);
			alpha += 10;
		}
	glm::ivec2 v5(380, 200);
		glm::ivec2 v6(400, 200);
		x_circle = 380;
	y_circle = 200;
	r = 20;
	alpha = 0;
	for (; alpha <= 360;)
		{
			x = x_circle + r * cos(alpha * M_PI / 180);//475
			y = y_circle + r * sin(alpha * M_PI / 180);//543
			v6[0] = x;
			v6[1] = y;
			DrawLine(v5, v6, color);
			alpha += 10;

		}
	glm::ivec2 v7(400, 200);
		glm::ivec2 v8(500, 200);
	DrawLine(v7, v8, color);
	glm::ivec2 v9(600, 200);
	glm::ivec2 v10(500, 200);
	x_circle = 600;
	y_circle = 200;
	r = 100;
	alpha = 0;
	for (; alpha <= 360;)
		{
			x = x_circle + r * cos(alpha * M_PI / 180);//475
			y = y_circle + r * sin(alpha * M_PI / 180);//543
			v10[0] = x;
			v10[1] = y;
			DrawLine(v9, v10, color);
			alpha += 1;

		}
	glm::ivec2 v11(700, 200);
		glm::ivec2 v12(900, 200);
	DrawLine(v11, v12, color);
	glm::ivec2 v13(900, 200);
	glm::ivec2 v14(700, 200);
	x_circle = 900;
	y_circle = 200;
	r = 100;
	alpha = 0;
	for (; alpha <= 360;)
		{
			x = x_circle + r * cos(alpha * M_PI / 180);//475
			y = y_circle + r * sin(alpha * M_PI / 180);//543
			v14[0] = x;
			v14[1] = y;
			DrawLine(v13, v14, color);
			alpha += 1;
		}
	glm::ivec2 v15(1000, 200);
		glm::ivec2 v16(1100, 200);
		DrawLine(v15, v16, color);
	glm::ivec2 v17(1100, 200);
	glm::ivec2 v18(1100, 400);
	DrawLine(v17, v18, color);
	glm::ivec2 v19(1100, 200);
	glm::ivec2 v20(1150, 200);
	DrawLine(v19, v20, color);
	glm::ivec2 v21(1150, 200);
	glm::ivec2 v22(1150, 250);
	DrawLine(v21, v22, color);
	glm::ivec2 v23(1150, 250);
	glm::ivec2 v24(1100, 250);
	DrawLine(v23, v24, color);
	glm::ivec2 v25(1100, 350);
	glm::ivec2 v26(1150, 350);
	DrawLine(v25, v26, color);
	glm::ivec2 v27(1150, 350);
	glm::ivec2 v28(1150, 400);
	DrawLine(v27, v28, color);
	glm::ivec2 v29(1150, 400);
	glm::ivec2 v30(1100, 400);
	DrawLine(v29, v30, color);
	glm::ivec2 v31(1100, 400);
	glm::ivec2 v32(1000, 400);
	DrawLine(v31, v32, color);
	glm::ivec2 v33(1000, 400);
	glm::ivec2 v34(1000, 500);
	DrawLine(v33, v34, color);
	glm::ivec2 v35(1000, 500);
	glm::ivec2 v36(800, 500);
	DrawLine(v35, v36, color);
	glm::ivec2 v37(800, 500);
	glm::ivec2 v38(800, 400);
	DrawLine(v37, v38, color);
	glm::ivec2 v39(800, 400);
	glm::ivec2 v40(400, 400);
	DrawLine(v39, v40, color);
	// draw circle

}

int Renderer::GetViewportWidth() const
{
	return viewport_width;
}

int Renderer::GetViewportHeight() const
{
	return viewport_height;
}