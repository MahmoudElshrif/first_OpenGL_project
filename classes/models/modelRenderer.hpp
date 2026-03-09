#pragma once
#include "model.hpp"
#include <string>

class ModelRenderer
{
public:
	Model *model;
	Shader *shader;
	std::string texture = "assets/star.jpeg";
	glm::vec3 pos;
	glm::vec3 rot;
	glm::vec3 scale;
	glm::mat4 modelMat;

	ModelRenderer(Model *model = Model::CUBE(), Shader *shader = nullptr) : model(model), shader(shader)
	{
		modelMat = glm::mat4(1.);
		pos = glm::vec3(0.);
		rot = glm::vec3(0.);
		scale = glm::vec3(1.);
	}

	void draw()
	{
		modelMat = glm::mat4(1.);
		modelMat = glm::translate(modelMat, pos);
		modelMat = glm::scale(modelMat, scale);
		model->use();
		shader->use();
		shader->setm4f("model", modelMat);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	}
};