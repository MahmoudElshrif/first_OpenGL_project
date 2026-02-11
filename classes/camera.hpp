#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Camera
{
public:
	float fov = 45.f;
	float near = 0.1f;
	float far = 100.f;

	glm::vec3 pos = glm::vec3(0.f);
	glm::vec3 cameraDir = glm::vec3(0.f, 0.f, -1.f);
	glm::vec3 cameraUp = glm::vec3(0.f, 1.f, 0.f);

	void lookAt(glm::vec3 target)
	{
		cameraDir = glm::normalize(target - pos);
	}

	glm::mat4 getViewMatrix()
	{
		return glm::lookAt(pos,
						   pos + cameraDir,
						   glm::vec3(0.f, 1.f, 0.f));
	}

	glm::mat4 getProjectionMatrix(int width, int height)
	{
		return glm::perspective(fov, (float)width / (float)height, near, far);
	}
};