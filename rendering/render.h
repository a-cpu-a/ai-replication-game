/*
    program name: ai-replication-game, a game where you can train ais to do stuff in a 3d world, and make them create copies
    Copyright (C) 2022  a-cpu-a

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.

    you can contact me electronicly by making a issue at https://github.com/a-cpu-a/ai-replication-game/issues/new
*/
#pragma once

#include "vec2.h"
#include "color3.h"
#include "Uniform.h"
#include "Shader.h"
#include "Layout.h"
#include "VertexBuffer.h"

#define TWO_PI 6.28318531
#define PI 3.14159265

namespace rendering
{

	extern std::vector<Shader*> shaders;

	extern UniformColor3 color3Uniform;// = UniformColor3("Color3");
	extern rendering::UniformInt baseColorTextureUniform;
	extern rendering::UniformInt baseColorCutoutTextureUniform;

	extern Shader colored2DShader;// = Shader("assets/shaders/2d_colored.vsh", "assets/shaders/2d_colored.fsh");
	extern Layout colored2DLayout;// = Layout({ 2,0 });
	extern VertexBuffer quadVertexBuffer;// = VertexBuffer(GL_DYNAMIC_DRAW, { 0.0f,0.0f, 0.0f,0.0f,   0.0f,0.0f, 0.0f,0.0f,   0.0f,0.0f, 0.0f,0.0f });


	extern Shader colored2DCircleShader;// = Shader("assets/shaders/2d_colored.vsh", "assets/shaders/2d_colored.fsh");
	extern Layout colored2DCircleLayout;// = Layout({ 2,0 });
	extern VertexBuffer circleVertexBuffer;// = VertexBuffer(GL_DYNAMIC_DRAW, { 0.0f,0.0f, 0.0f,0.0f,   0.0f,0.0f, 0.0f,0.0f,   0.0f,0.0f, 0.0f,0.0f });


	extern rendering::Shader textured2DQuadShader;
	extern rendering::Shader texturedCutout2DQuadShader;

	extern rendering::Layout textured2DQuadLayout;
	extern rendering::VertexBuffer textured2DQuadVertexBuffer;

	inline void renderInit()
	{
		colored2DShader = Shader("assets/shaders/2d_colored.vsh", "assets/shaders/2d_colored.fsh");
		quadVertexBuffer = VertexBuffer(GL_DYNAMIC_DRAW, { 0.0f,0.0f,   0.0f,0.0f,   0.0f,0.0f,0.0f,0.0f,   0.0f,0.0f,   0.0f,0.0f });
		colored2DLayout = Layout({ 2,0 },quadVertexBuffer.id);

		colored2DCircleShader = Shader("assets/shaders/2d_circle_colored.vsh", "assets/shaders/2d_circle_colored.fsh");
		circleVertexBuffer = VertexBuffer(GL_DYNAMIC_DRAW, { 0.0f,0.0f, 0.0f,0.0f,  0.0f,0.0f, 0.0f,0.0f,  0.0f,0.0f, 0.0f,0.0f,0.0f,0.0f, 0.0f,0.0f,  0.0f,0.0f, 0.0f,0.0f,  0.0f,0.0f, 0.0f,0.0f });
		colored2DCircleLayout = Layout({ 2,2,0 }, circleVertexBuffer.id);

		textured2DQuadShader = Shader("assets/shaders/2d_tex.vsh", "assets/shaders/2d_tex.fsh");
		texturedCutout2DQuadShader = Shader("assets/shaders/2d_tex_cutout.vsh", "assets/shaders/2d_tex_cutout.fsh");
		textured2DQuadVertexBuffer = VertexBuffer(GL_DYNAMIC_DRAW, { 0.0f,0.0f, 0.0f,0.0f,  0.0f,0.0f, 0.0f,0.0f,  0.0f,0.0f, 0.0f,0.0f,0.0f,0.0f, 0.0f,0.0f,  0.0f,0.0f, 0.0f,0.0f,  0.0f,0.0f, 0.0f,0.0f });
		textured2DQuadLayout = Layout({ 2,2,0 }, textured2DQuadVertexBuffer.id);



		//add all shaders to shader list
		shaders.push_back(&colored2DShader);
		shaders.push_back(&colored2DCircleShader);
		
		color3Uniform = UniformColor3("Color3U",shaders);


		shaders.push_back(&texturedCutout2DQuadShader);
		baseColorCutoutTextureUniform = UniformInt("BaseColorCutout", shaders);

		shaders.push_back(&textured2DQuadShader);
		baseColorTextureUniform = UniformInt("BaseColor", shaders);

	}

	inline void clearScreen(color3 color)
	{
		glClearColor(color.r, color.g, color.b, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
	}

	inline void clearScreen(float red, float green, float blue, float alpha)
	{
		glClearColor(red, green, blue, alpha);
		glClear(GL_COLOR_BUFFER_BIT);
	}

	inline void clearScreen(float red, float green, float blue)
	{
		glClearColor(red, green, blue, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
	}

	inline void renderQuadRGB(vec2 bottomLeft, vec2 topLeft, vec2 topRight, vec2 bottomRight, color3 color)
	{

		const std::vector<float> vertices = {
			bottomLeft.x, bottomLeft.y,
			topLeft.x,    topLeft.y ,
			topRight.x,   topRight.y,

			topRight.x,    topRight.y,
			bottomRight.x, bottomRight.y,
			bottomLeft.x,  bottomLeft.y
		};

		color3Uniform.setValue(color);
		colored2DShader++; // shader
		colored2DLayout++; //layout

		quadVertexBuffer.updateData(vertices);
		//quadVertexBuffer++;

		glDrawArrays(GL_TRIANGLES, 0, 6);

		//quadVertexBuffer--;

		colored2DLayout--; //layout
		colored2DShader--; // shader
	}

	inline void renderTexCutout(std::vector<float> vertexData, VertexBuffer* vertexBuffer)
	{

		texturedCutout2DQuadShader++; // shader
		textured2DQuadLayout++; //layout

		//(*vertexBuffer).updateData(vertexData);
		const size_t size = vertexData.size();
		(*vertexBuffer).recreate(vertexData, size);
		//quadVertexBuffer++;

		glDrawArrays(GL_TRIANGLES, 0, size/4);

		//quadVertexBuffer--;

		textured2DQuadLayout--; //layout
		texturedCutout2DQuadShader--; // shader
	}

	inline void renderTex(std::vector<float> vertexData, VertexBuffer* vertexBuffer)
	{

		textured2DQuadShader++; // shader
		textured2DQuadLayout++; //layout

		//(*vertexBuffer).updateData(vertexData);
		const size_t size = vertexData.size();
		(*vertexBuffer).recreate(vertexData, size/4);
		//quadVertexBuffer++;

		glDrawArrays(GL_TRIANGLES, 0, size);

		//quadVertexBuffer--;

		textured2DQuadLayout--; //layout
		textured2DQuadShader--; // shader
	}

	inline void renderQuadTexCutout(vec2 bottomLeft, vec2 topRight, vec2 minUv, vec2 maxUv)
	{

		const std::vector<float> vertices = {
			bottomLeft.x,   bottomLeft.y,minUv.x,minUv.y,
			bottomLeft.x,     topRight.y,minUv.x,maxUv.y,
			topRight.x,       topRight.y,maxUv.x,maxUv.y,

			topRight.x,       topRight.y,maxUv.x,maxUv.y,
			topRight.x,     bottomLeft.y,maxUv.x,minUv.y,
			bottomLeft.x,   bottomLeft.y,minUv.x,minUv.y
		};


		texturedCutout2DQuadShader++; // shader
		textured2DQuadLayout++; //layout

		textured2DQuadVertexBuffer.updateData(vertices);
		//quadVertexBuffer++;

		glDrawArrays(GL_TRIANGLES, 0, 6);

		//quadVertexBuffer--;

		textured2DQuadLayout--; //layout
		texturedCutout2DQuadShader--; // shader
	}

	inline void renderQuadTex(vec2 bottomLeft, vec2 topRight, vec2 minUv, vec2 maxUv)
	{

		const std::vector<float> vertices = {
			bottomLeft.x,   bottomLeft.y,minUv.x,minUv.y,
			bottomLeft.x,     topRight.y,minUv.x,maxUv.y,
			topRight.x,       topRight.y,maxUv.x,maxUv.y,

			topRight.x,       topRight.y,maxUv.x,maxUv.y,
			topRight.x,     bottomLeft.y,maxUv.x,minUv.y,
			bottomLeft.x,   bottomLeft.y,minUv.x,minUv.y
		};

		textured2DQuadShader++; // shader
		textured2DQuadLayout++; //layout

		textured2DQuadVertexBuffer.updateData(vertices);
		//quadVertexBuffer++;

		glDrawArrays(GL_TRIANGLES, 0, 6);

		//quadVertexBuffer--;

		textured2DQuadLayout--; //layout
		textured2DQuadShader--; // shader
	}

	inline void renderCircleRGB(vec2 bottomLeft, vec2 topLeft, vec2 topRight, vec2 bottomRight, color3 color)
	{

		const std::vector<float> vertices = {
			bottomLeft.x,   bottomLeft.y,-1.0f,-1.0f,
			topLeft.x,         topLeft.y,-1.0f,1.0f,
			topRight.x,       topRight.y,1.0f,1.0f,

			topRight.x,       topRight.y,1.0f,1.0f,
			bottomRight.x, bottomRight.y,1.0f,-1.0f,
			bottomLeft.x,   bottomLeft.y,-1.0f,-1.0f
		};


		color3Uniform.setValue(color);
		colored2DCircleShader++; // shader
		colored2DCircleLayout++; //layout

		circleVertexBuffer.updateData(vertices);
		//quadVertexBuffer++;

		glDrawArrays(GL_TRIANGLES, 0, 6);

		//quadVertexBuffer--;

		colored2DCircleLayout--; //layout
		colored2DCircleShader--; // shader
	}
}
