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

#include <iostream>
#include <string>
#include <vector>

#include <GL/glew.h>

#include "color3.h"
#include "Shader.h"

namespace rendering
{
	struct UniformInt
	{
		std::vector<GLuint> shaders;
		std::vector<GLint> locations;
		std::string name;
		UniformInt() {}
		UniformInt(std::string _name, std::vector<Shader*> _shaders)
		{
			name = _name;

			const auto end = _shaders.end();
			for (auto it = _shaders.begin(); it != end; it++)
			{

				const GLint location = (*it)->getUniformLocation(name);
				if (location != -1)
				{
					shaders.push_back((*it)->id);
					locations.push_back(location);
				}
			}
		}
		void setValue(int32_t value)
		{
			const size_t length = shaders.size();
			if (length == 0) { return; }
			for (size_t i = 0; i < length; i++)
			{
				glUseProgram(shaders[i]);
				glUniform1i(locations[i], value);
			}
			glUseProgram(0);
		}
	};

	struct UniformColor3
	{
		std::vector<GLuint> shaders;
		std::vector<GLint> locations;
		std::string name;
		UniformColor3() {}
		UniformColor3(std::string _name, std::vector<Shader*> _shaders)
		{
			name = _name;

			const auto end = _shaders.end();
			for (auto it = _shaders.begin(); it != end; it++)
			{
				
				const GLint location = (*it)->getUniformLocation(name);
				if (location != -1)
				{
					shaders.push_back((*it)->id);
					locations.push_back(location);
				}
			}
		}
		void setValue(color3 value)
		{
			const size_t length = shaders.size();
			if (length == 0) { return; }
			for (size_t i = 0; i < length; i++)
			{
				glUseProgram(shaders[i]);
				glUniform3f(locations[i], value.r, value.g, value.b);
			}
			glUseProgram(0);
		}
	};
}
