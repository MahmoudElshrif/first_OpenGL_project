#pragma once
#include <vector>
#include "../Vertex.hpp"
#include "../shader.hpp"
class Model
{
public:
	VertexDataArray vda;
	std::vector<unsigned int> indices;
	unsigned int VBO;
	unsigned int VAO;
	unsigned int EBO;

	static Model *cube;

	Model(VertexDataArray vda, std::vector<unsigned int> indices) : vda(vda), indices(indices)
	{
		setupBuffers();
	}
	Model() {}

	void setupBuffers()
	{
		auto verts = vda.getArray();
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);
		glGenVertexArrays(1, &VAO);

		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, vda.get_total_size(), verts, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);
	}

	void use()
	{
		glBindVertexArray(VAO);
	}

	static Model *CUBE()
	{
		if (!cube)
		{
			Model::cube = new Model();
			VertexDataArray cubevda(24);

			// Back face (Z = -0.5)
			cubevda[0] = {-0.5f, -0.5f, -0.5f, 0.0f, 0.0f}; // Bottom-Left
			cubevda[1] = {0.5f, -0.5f, -0.5f, 1.0f, 0.0f};	// Bottom-Right
			cubevda[2] = {0.5f, 0.5f, -0.5f, 1.0f, 1.0f};	// Top-Right
			cubevda[3] = {-0.5f, 0.5f, -0.5f, 0.0f, 1.0f};	// Top-Left

			// Front face (Z = 0.5)
			cubevda[4] = {-0.5f, -0.5f, 0.5f, 0.0f, 0.0f};
			cubevda[5] = {0.5f, -0.5f, 0.5f, 1.0f, 0.0f};
			cubevda[6] = {0.5f, 0.5f, 0.5f, 1.0f, 1.0f};
			cubevda[7] = {-0.5f, 0.5f, 0.5f, 0.0f, 1.0f};

			// Left face (X = -0.5)
			cubevda[8] = {-0.5f, 0.5f, 0.5f, 1.0f, 0.0f};
			cubevda[9] = {-0.5f, 0.5f, -0.5f, 1.0f, 1.0f};
			cubevda[10] = {-0.5f, -0.5f, -0.5f, 0.0f, 1.0f};
			cubevda[11] = {-0.5f, -0.5f, 0.5f, 0.0f, 0.0f};

			// Right face (X = 0.5)
			cubevda[12] = {0.5f, 0.5f, 0.5f, 1.0f, 0.0f};
			cubevda[13] = {0.5f, 0.5f, -0.5f, 1.0f, 1.0f};
			cubevda[14] = {0.5f, -0.5f, -0.5f, 0.0f, 1.0f};
			cubevda[15] = {0.5f, -0.5f, 0.5f, 0.0f, 0.0f};

			// Bottom face (Y = -0.5)
			cubevda[16] = {-0.5f, -0.5f, -0.5f, 0.0f, 1.0f};
			cubevda[17] = {0.5f, -0.5f, -0.5f, 1.0f, 1.0f};
			cubevda[18] = {0.5f, -0.5f, 0.5f, 1.0f, 0.0f};
			cubevda[19] = {-0.5f, -0.5f, 0.5f, 0.0f, 0.0f};

			// Top face (Y = 0.5)
			cubevda[20] = {-0.5f, 0.5f, -0.5f, 0.0f, 1.0f};
			cubevda[21] = {0.5f, 0.5f, -0.5f, 1.0f, 1.0f};
			cubevda[22] = {0.5f, 0.5f, 0.5f, 1.0f, 0.0f};
			cubevda[23] = {-0.5f, 0.5f, 0.5f, 0.0f, 0.0f};

			std::vector<unsigned int> cubeindices = {
				// Back face
				0, 1, 2, 2, 3, 0,
				// Front face
				4, 5, 6, 6, 7, 4,
				// Left face
				8, 9, 10, 10, 11, 8,
				// Right face
				12, 13, 14, 14, 15, 12,
				// Bottom face
				16, 17, 18, 18, 19, 16,
				// Top face
				20, 21, 22, 22, 23, 20};

			cube->vda = cubevda;
			cube->indices = cubeindices;
			cube->setupBuffers();
		}

		return cube;
	}
};

Model *Model::cube = nullptr;