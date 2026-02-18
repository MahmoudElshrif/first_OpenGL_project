#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Mouse.hpp"
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/rotate_vector.hpp>
#include <algorithm>
class Camera
{
public:
	float fov = 45.f;
	float near = 0.1f;
	float far = 100.f;
	float camsens = 0.006;

	glm::vec3 pos = glm::vec3(0.f);
	glm::vec3 cameraDir = glm::vec3(0.f, 0.f, -1.f);
	glm::vec3 cameraUp = glm::vec3(0.f, 1.f, 0.f);

	glm::vec3 camRot = glm::vec3(0.f, 0.f, 0.f);

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

	void handleInputs(GLFWwindow *window)
	{
		camRot.x += (float)Mouse::deltax * camsens;
		camRot.y += (float)Mouse::deltay * camsens;

		camRot.y = std::min(std::max(-3.14f / 2.f + 0.3f, camRot.y), 3.14f / 2.f - 0.3f);

		cameraDir = glm::vec3(0., 0., -1.);
		cameraDir = glm::rotate(cameraDir, -(camRot.x), cameraUp);

		glm::vec3 cameraRight = glm::normalize(glm::cross(cameraDir, cameraUp));
		float cameraSpeed = 0.05f;
		if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
			cameraSpeed *= 2.;
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
			pos += cameraSpeed * cameraDir;
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
			pos -= cameraSpeed * cameraDir;
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
			pos -= glm::normalize(glm::cross(cameraDir, cameraUp)) * cameraSpeed;
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
			pos += glm::normalize(glm::cross(cameraDir, cameraUp)) * cameraSpeed;
		if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
			pos += cameraUp * cameraSpeed;
		if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
			pos += -cameraUp * cameraSpeed;

		cameraDir = glm::rotate(cameraDir, -(camRot.y), cameraRight);
	}
};