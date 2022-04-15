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

#include <GL/glew.h>

#include <iostream>
#include <array>
namespace rendering 
{
	struct Layout
	{
		GLuint id;
		Layout() {}
		Layout(std::array<uint8_t, 15> sizes, GLuint vertexBufferId)
		{
			glGenVertexArrays(1, &id);
			operator++(0);
			glBindBuffer(GL_ARRAY_BUFFER, vertexBufferId);

			uint8_t stride = 0;

			for (uint8_t i = 0; i < 15; i++)
			{
				const uint8_t val = sizes[i];
				if (val == 0)
					break;

				stride += val;
			}
			uint8_t pointer = 0;

			for (uint8_t i = 0; i < 15; i++)
			{
				const uint8_t val = sizes[i];
				if (val == 0)
					break;

				glEnableVertexAttribArray(i);
				glVertexAttribPointer(i, val, GL_FLOAT, GL_FALSE, stride * sizeof(float), (void*)(pointer * sizeof(float)));
				pointer += val;

			}
			operator--(0);
		}

		void operator++(int)
		{
			glBindVertexArray(id);
		}
		void operator--(int)
		{
			glBindVertexArray(0);
		}
	};
}
