#include <vector>
#include "Vertex.hpp"
#include "shader.hpp"
class Model
{
public:
	VertexDataArray vda;
	std::vector<int> indices;
	Shader shader;
	unsigned int VBO;
	unsigned int VAO;
	unsigned int EBO;

	Model(VertexDataArray vda, std::vector<int> indices, Shader shader) : vda(vda), indices(indices), shader(shader)
	{

		auto verts = vda.getArray();
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);
		glGenVertexArrays(1, &VAO);

		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, vda.get_total_size(), verts, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size(), &indices[0], GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);
	}
	void draw()
	{
	}
};