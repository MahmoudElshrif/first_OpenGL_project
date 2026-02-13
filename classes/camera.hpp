#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Mouse.hpp"
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/rotate_vector.hpp>
class Camera
{
public:
	float fov = 45.f;
	float near = 0.1f;
	float far = 100.f;
	float camsens = 0.1;

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

	void handleInputs(GLFWwindow *window)
	{
		const float cameraSpeed = 0.05f;
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
			pos += cameraSpeed * cameraDir;
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
			pos -= cameraSpeed * cameraDir;
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
			pos -= glm::normalize(glm::cross(cameraDir, cameraUp)) * cameraSpeed;
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
			pos += glm::normalize(glm::cross(cameraDir, cameraUp)) * cameraSpeed;
		cameraDir = glm::rotate(cameraDir, -glm::radians((float)Mouse::deltax * camsens), cameraUp);
		glm::vec3 cameraRight = glm::normalize(glm::cross(cameraDir, cameraUp));
		cameraDir = glm::rotate(cameraDir, -glm::radians((float)Mouse::deltay * camsens), cameraRight);
	}
};