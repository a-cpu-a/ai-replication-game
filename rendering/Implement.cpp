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
#define GLEW_STATIC

#include "render.h"

std::vector<rendering::Shader*> rendering::shaders;

rendering::UniformColor3 rendering::color3Uniform;// = rendering::UniformColor3("Color3");
rendering::UniformInt rendering::baseColorTextureUniform;
rendering::UniformInt rendering::baseColorCutoutTextureUniform;

rendering::Shader rendering::colored2DShader;// = rendering::Shader("assets/shaders/2d_colored.vsh", "assets/shaders/2d_colored.fsh");
rendering::Layout rendering::colored2DLayout;// = rendering::Layout({ 2,0 });
rendering::VertexBuffer rendering::quadVertexBuffer;// = rendering::VertexBuffer(GL_DYNAMIC_DRAW, { 0.0f,0.0f, 0.0f,0.0f,   0.0f,0.0f, 0.0f,0.0f,   0.0f,0.0f, 0.0f,0.0f });

rendering::Shader rendering::colored2DCircleShader;// = rendering::Shader("assets/shaders/2d_colored.vsh", "assets/shaders/2d_colored.fsh");
rendering::Layout rendering::colored2DCircleLayout;// = rendering::Layout({ 2,0 });
rendering::VertexBuffer rendering::circleVertexBuffer;// = rendering::VertexBuffer(GL_DYNAMIC_DRAW, { 0.0f,0.0f, 0.0f,0.0f,   0.0f,0.0f, 0.0f,0.0f,   0.0f,0.0f, 0.0f,0.0f });


rendering::Shader rendering::textured2DQuadShader;
rendering::Shader rendering::texturedCutout2DQuadShader;
rendering::Layout rendering::textured2DQuadLayout;
rendering::VertexBuffer rendering::textured2DQuadVertexBuffer;
