#include <cmath>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "classes/shader.hpp"
#include "classes/Image.hpp"
#include "classes/Vertex.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "classes/camera.hpp"
#include "classes/Mouse.hpp"
#include "classes/models/modelRenderer.hpp"

int width = 800;
int height = 800;

void framebuffer_size_change(GLFWwindow *window, int w, int h)
{
	glViewport(0, 0, w, h);
	width = w;
	height = h;
}

void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE))
	{
		glfwSetWindowShouldClose(window, true);
	}

	if (glfwGetKey(window, GLFW_KEY_1))
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}

	if (glfwGetKey(window, GLFW_KEY_2))
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
}

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	GLFWwindow *window = glfwCreateWindow(width, height, "openglshit", NULL, NULL);

	Camera cam;
	cam.pos = glm::vec3(0., 0., 5.f);

	float fov = 10.;

	if (window == NULL)
	{
		std::cout << "FAILURE AFTER FAILURE AFTER FAILURE" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwShowWindow(window);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	glViewport(0, 0, 800, 800);

	Shader shader("shaders/vertex.vert", "shaders/frag.frag");
	Shader lightShader("shaders/light/lightvertex.vert", "shaders/light/lightfrag.frag");

	ModelRenderer lightSource;
	lightSource.shader = &lightShader;

	glEnable(GL_DEPTH_TEST);

	Texture img("assets/star.jpeg");
	Texture img2("assets/image.jpg");

	glfwSetFramebufferSizeCallback(window, framebuffer_size_change);
	glfwSetCursorPosCallback(window, Mouse::mouse_move_callback);
	int t = 0;

	glm::vec3 poses[] = {
		glm::vec3(0., 0., 0.),
		// glm::vec3(10., 3., 0.),
		// glm::vec3(-2.2, 1.5, -1.),
		// glm::vec3(0., -3., 0.),
		// glm::vec3(0., 3., 3.),

	};

	std::vector<ModelRenderer> cubes;
	for (auto i : poses)
	{
		ModelRenderer cube;
		cube.pos = i;
		cube.shader = &shader;
		cubes.push_back(cube);
	}

	lightSource.pos = glm::vec3(2., 0., -0.5);

	while (!glfwWindowShouldClose(window))
	{
		processInput(window);
		cam.handleInputs(window);

		glClearColor(0., 0., 0., 1.);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shader.use();
		shader.set4f("objectColor", 1.f, 1.f, 0.3, 1.f);
		shader.set4f("lightColor", 1., 1.f, 1.f, 1.f);
		shader.seti("TIME", t);
		shader.set3f("lightPos", lightSource.pos.x, lightSource.pos.y, lightSource.pos.z);
		t++;

		lightSource.pos.x = cos(t * 0.1) * 5;
		lightSource.pos.z = sin(t * 0.1) * 5;

		// cam.lookAt(glm::vec3(0.f, 0.f, 0.f));
		glm::mat4 view = cam.getViewMatrix();

		glm::mat4 proj = cam.getProjectionMatrix(width, height);

		shader.setm4f("view", view);
		shader.setm4f("projection", proj);
		for (auto i : cubes)
		{
			i.draw();
		}

		lightShader.use();
		lightShader.setm4f("view", view);
		lightShader.setm4f("projection", proj);
		lightSource.draw();

		Mouse::deltax = 0.;
		Mouse::deltay = 0.;
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}
