#pragma once
#include "stb_image.h"
#include <string>
#include <GLFW/glfw3.h>
#include <GLES3/gl3.h>
#include <iostream>

class Image
{
private:
	int width, height, nrChannels;
	unsigned char *data;
	unsigned int texture;

public:
	Image(std::string path)
	{
		data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);

		glGenTextures(1, &texture);

		glBindTexture(GL_TEXTURE_2D, texture);

		if (data)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else
		{
			std::cout << "Failed to load image\n";
		}

		stbi_image_free(data);
	}
};