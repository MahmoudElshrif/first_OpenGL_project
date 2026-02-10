#pragma once

#include <string>
#include "utils.cpp"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader
{
public:
	unsigned int id;

	Shader(std::string vertexPath, std::string fragPath)
	{
		// shaders init
		auto vertexFile = loadFileAsString(vertexPath);
		const char *vertex = vertexFile.c_str();
		// vertex shader
		unsigned int vertexShader;
		vertexShader = glCreateShader(GL_VERTEX_SHADER);

		glShaderSource(vertexShader, 1, &vertex, NULL);
		glCompileShader(vertexShader);

		int success;
		char infoLog[512];
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

		if (!success)
		{
			glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"
					  << infoLog << std::endl;
		}

		auto fragFile = loadFileAsString(fragPath);
		const char *frag = fragFile.c_str();
		unsigned int fragShader;
		fragShader = glCreateShader(GL_FRAGMENT_SHADER);

		glShaderSource(fragShader, 1, &frag, NULL);
		glCompileShader(fragShader);

		glGetShaderiv(fragShader, GL_COMPILE_STATUS, &success);

		if (!success)
		{
			glGetShaderInfoLog(fragShader, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::FRAG::COMPILATION_FAILED\n"
					  << infoLog << std::endl;
		}

		// init shader
		id = glCreateProgram();

		glAttachShader(id, vertexShader);
		glAttachShader(id, fragShader);
		glLinkProgram(id);

		glGetProgramiv(id, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(id, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::PROGRAM::COMPILATION_FAILED\n"
					  << infoLog << std::endl;
		}
	}

	void use()
	{
		glUseProgram(id);
	};

	void setb(std::string name, bool val) const
	{
		auto uniformColor = glGetUniformLocation(id, name.c_str());
	};
	void seti(std::string name, int val) const
	{
		auto uniformColor = glGetUniformLocation(id, name.c_str());

		glUniform1i(uniformColor, val);
	};
	void set3f(std::string name, float x, float y, float z) const
	{
		auto uniformColor = glGetUniformLocation(id, name.c_str());

		glUniform3f(uniformColor, x, y, z);
	};
	void set4f(std::string name, float x, float y, float z, float w) const
	{
		auto uniformColor = glGetUniformLocation(id, name.c_str());

		glUniform4f(uniformColor, x, y, z, w);
	};
	void setf(std::string name, float val) const
	{
		auto uniformColor = glGetUniformLocation(id, name.c_str());

		glUniform1f(uniformColor, val);
	};

	void setm4f(std::string name, glm::mat4 mat)
	{
		unsigned int matID = glGetUniformLocation(id, name.c_str());
		glUniformMatrix4fv(matID, 1, GL_FALSE, glm::value_ptr(mat));
	}
};
