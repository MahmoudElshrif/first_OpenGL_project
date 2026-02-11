#pragma once
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <string>
#include <GLFW/glfw3.h>
#include <iostream>

class Texture
{
private:
public:
	int width, height, nrChannels;
	unsigned char *data;
	unsigned int texture;
	Texture(std::string path)
	{
		stbi_set_flip_vertically_on_load(true);
		data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);

		glGenTextures(1, &texture);

		glBindTexture(GL_TEXTURE_2D, texture);

		if (data)
		{
			glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else
		{
			std::cout << "Failed to load image\n";
		}

		stbi_image_free(data);
	}

	void use(int num = 0)
	{
		glActiveTexture(GL_TEXTURE0 + num);
		glBindTexture(GL_TEXTURE_2D, texture);
	}
};