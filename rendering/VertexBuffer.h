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

#include <vector>

#include <GL/glew.h>
namespace rendering 
{
	struct VertexBuffer
	{
		GLuint id;
		GLuint type;

		size_t size;
		VertexBuffer() {}
		VertexBuffer(GLuint _type, std::vector<float> data)
		{
			glGenBuffers(1, &id);
			type = _type;
			size = data.size();
			recreate(data);
		}
		VertexBuffer(GLuint _type, size_t _size)
		{
			glGenBuffers(1, &id);
			type = _type;
			size = _size;
			recreateEmpty();
		}

		VertexBuffer(std::vector<float> data)
		{
			glGenBuffers(1, &id);
			size = data.size();
			type = GL_STATIC_DRAW;
			recreate(data);
		}
	
		void recreate(std::vector<float> data)
		{
			operator++(0);
			glBufferData(GL_ARRAY_BUFFER, size * sizeof(float), &data.front(), type);
			operator--(0);
		}

		void recreate(std::vector<float> data, size_t _size)
		{
			operator++(0);
			glBufferData(GL_ARRAY_BUFFER, _size * sizeof(float), &data.front(), type);
			operator--(0);
		}

		void recreateEmpty()
		{
			operator++(0);
			glBufferData(GL_ARRAY_BUFFER, size * sizeof(float), NULL, type);
			operator--(0);
		}

		void updateData(std::vector<float> data)
		{
			operator++(0);
			glBufferSubData(GL_ARRAY_BUFFER, 0, size * sizeof(float), &data.front());
			operator--(0);
		}

		void operator++(int)
		{
			glBindBuffer(GL_ARRAY_BUFFER, id);
		}
		void operator--(int)
		{
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}
	};
}
