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

#include <string>
#include <iostream>

#define GLEW_STATIC
#include <GL/glew.h>

#include "../files/get_text.h"

#define LOG_ERROR(x) std::cout << "[ERROR] " << x << "\n";

namespace rendering
{
	struct Shader
	{
		GLuint id;
		std::string vertex;
		std::string fragment;
		Shader() {}
		~Shader()
		{
			//glDeleteProgram(id);
		}
		Shader(std::string _vertex, std::string _fragment)
		{
			vertex = _vertex;
			fragment = _fragment;
			recreate();
		}
		GLuint compileShader(GLuint type, std::string code, std::string errorName)
		{

			const char* string = code.c_str();

			GLuint shaderId = glCreateShader(type);
			glShaderSource(shaderId, 1, &string, nullptr);

			glCompileShader(shaderId);

			int result;
			glGetShaderiv(shaderId, GL_COMPILE_STATUS, &result);
			if (result == GL_FALSE)
			{
				int errorLenght = 0;
				glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &errorLenght);
				char* error = (char*)malloc(errorLenght * sizeof(char));
				glGetShaderInfoLog(shaderId, errorLenght, &errorLenght, error);

				LOG_ERROR(error);
			}
			return shaderId;
		}
		void recreate()
		{
			const std::string vertexCode = files::getText(vertex);
			const std::string fragmentCode = files::getText(fragment);

			const GLuint vertexShader = compileShader(GL_VERTEX_SHADER, vertexCode, "vertex");
			const GLuint fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentCode, "fragment");

			id = glCreateProgram();

			glAttachShader(id, vertexShader);
			glAttachShader(id, fragmentShader);
			glLinkProgram(id);
			glValidateProgram(id);

			int result;
			glGetProgramiv(id, GL_LINK_STATUS, &result);
			if (result == GL_FALSE)
			{
				int errorLenght = 0;
				glGetProgramiv(id, GL_INFO_LOG_LENGTH, &errorLenght);
				char* error = (char*)malloc(errorLenght * sizeof(char));
				glGetProgramInfoLog(id, errorLenght, &errorLenght, error);
				LOG_ERROR(error);
			}
		}
		void operator++(int)
		{
			//std::cout << glGetError() << " ERR\n";
			glUseProgram(id);
			//std::cout << glGetError() << " ERR\n";
		}
		void operator--(int)
		{
			//std::cout << glGetError() << " ERR\n";
			glUseProgram(0);
			//std::cout << glGetError() << " ERR\n";
		}
		GLint getUniformLocation(std::string name)
		{
			operator++(0);
			//LOG_ERROR("uniform missingNT '" + name + "' from shader VERT:'" + vertex + "' FRAG:'" + fragment + "'");
			const GLint location = glGetUniformLocation(id, name.c_str());
			operator--(0);
			if (location == -1)
			{
				LOG_ERROR("uniform missing '" + name + "' from shader VERT:'" + vertex + "' FRAG:'" + fragment + "'");
			}
			return location;
		}
	};
}
