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
#include <iostream>

#define GLEW_STATIC
#include <GL/glew.h>

#define STB_IMAGE_IMPLEMENTATION
#include "../ven/stb_image.h"

#include <GLFW/glfw3.h>

#include "../rendering/render.h"
#include "../rendering/Texture.h"
#include "TileRenderer.h"
#include "Init.h"

bool reRender = true;

void resizeCallBack(GLFWwindow* window, int x, int y)
{
    game::xMul = 1.0f / float(x) * game::uIScale;
    game::yMul = 1.0f / float(y) * game::uIScale;

    game::tileSizeMulX = game::tileSize * game::xMul;
    game::tileSizeMulY = game::tileSize * game::yMul;

    game::cameraMulX = game::cameraX * game::xMul;
    game::cameraMulZ = game::cameraZ * game::yMul;

    reRender = true;
    glViewport(0, 0, x, y);
}

rendering::Texture atlas;
rendering::Texture cutoutAtlas;

void reloadAll()
{
    atlas.reload();
    cutoutAtlas.reload();
}

int main()
{
    stbi_set_flip_vertically_on_load(1);

    if (!glfwInit())
        return -1001;

    //glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_FALSE);//breaks renderdoc! ...

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    //glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_TRUE);

    GLFWwindow* window = glfwCreateWindow(960, 720, "", nullptr, nullptr);

    // glfwSetWindowAttrib(window, GLFW_DECORATED, GLFW_FALSE);

    if (!window)
    {
        glfwTerminate();
        return -1002;
    }

    glfwMakeContextCurrent(window);

    if (glewInit())
    {
        glfwTerminate();
        return -1003;

    }




    glfwSetWindowSizeCallback(window, resizeCallBack);




    //glClearColor(0.4f, 0.3f, 1.0f, 1.0f);
    //glClear(GL_COLOR_BUFFER_BIT);

    double time = glfwGetTime();

    uint64_t frame = 0;


    rendering::renderInit();

    int32_t texId = 0;


    atlas = rendering::Texture("atlas.png", texId++);
    rendering::baseColorTextureUniform.setValue(atlas.i);

    cutoutAtlas = rendering::Texture("cutoutAtlas.png", texId++);
    rendering::baseColorCutoutTextureUniform.setValue(cutoutAtlas.i);
    
    game::initWorld(1);


    //rendering::VertexBuffer worldBuffer = rendering::VertexBuffer(GL_DYNAMIC_DRAW, game::worldSizeX*2 * game::worldSizeY * game::worldSizeZ*2 * 4);

    while (!glfwWindowShouldClose(window))
    {
        frame++;

        //while (glfwGetTime() < time + (1.0 / 60.0))
        //{
        //}
        time = glfwGetTime();

        reRender = true;
        //render
        if (reRender)
        {
            reRender = false;
            rendering::clearScreen(0.0509803922f, 0.0196078431f, 0.0f);
            game::render::renderTiles(NULL);//&worldBuffer
            /*double p = time;
            double c = 0.0;
            for (size_t i = 0; i < 6; i++)
            {
                p += 2.0 / 6.0;
                c += 2.0 / 6.0;

                const rendering::vec2 pos = rendering::vec2(float(sin(p * PI)) * 350.0f, float(cos(p * PI)) * 350.0f);

                const float lineWidth = 30.0f;

                rendering::renderCircleRGB(
                    rendering::vec2((pos.x - lineWidth) * xMul, (pos.y - lineWidth) * yMul),
                    rendering::vec2((pos.x - lineWidth) * xMul, (pos.y + lineWidth) * yMul),
                    rendering::vec2((pos.x + lineWidth) * xMul, (pos.y + lineWidth) * yMul),
                    rendering::vec2((pos.x + lineWidth) * xMul, (pos.y - lineWidth) * yMul),
                    rendering::color3(float(sin(c * PI)) * 0.5f + 0.5f, float(cos(c * PI)) * 0.5f + 0.5f, float(-sin(c * PI)) * 0.5f + 0.5f)
                );
            }

            if (frame >= 1000999900)
            {
                rendering::renderQuadRGB(
                    rendering::vec2(0.0f, 0.0f),
                    rendering::vec2(0.0f, 0.5f),
                    rendering::vec2(0.5f, 0.5f),
                    rendering::vec2(0.5f, 0.0f),
                    rendering::color3(0.5f, 0.2f, 0.8f)
                );
            }*/
        }

        //glBlendEquation(GL_ADD);
        //glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ONE_MINUS_SRC_ALPHA);

        //glFlush();
        glfwSwapBuffers(window);

        glfwPollEvents();
    }






    glfwTerminate();
    return 0;
}
