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

	float fov = 45.;

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

	VertexDataArray vda(24);

	// Back face (Z = -0.5)
	vda[0] = {-0.5f, -0.5f, -0.5f, 0.0f, 0.0f}; // Bottom-Left
	vda[1] = {0.5f, -0.5f, -0.5f, 1.0f, 0.0f};	// Bottom-Right
	vda[2] = {0.5f, 0.5f, -0.5f, 1.0f, 1.0f};	// Top-Right
	vda[3] = {-0.5f, 0.5f, -0.5f, 0.0f, 1.0f};	// Top-Left

	// Front face (Z = 0.5)
	vda[4] = {-0.5f, -0.5f, 0.5f, 0.0f, 0.0f};
	vda[5] = {0.5f, -0.5f, 0.5f, 1.0f, 0.0f};
	vda[6] = {0.5f, 0.5f, 0.5f, 1.0f, 1.0f};
	vda[7] = {-0.5f, 0.5f, 0.5f, 0.0f, 1.0f};

	// Left face (X = -0.5)
	vda[8] = {-0.5f, 0.5f, 0.5f, 1.0f, 0.0f};
	vda[9] = {-0.5f, 0.5f, -0.5f, 1.0f, 1.0f};
	vda[10] = {-0.5f, -0.5f, -0.5f, 0.0f, 1.0f};
	vda[11] = {-0.5f, -0.5f, 0.5f, 0.0f, 0.0f};

	// Right face (X = 0.5)
	vda[12] = {0.5f, 0.5f, 0.5f, 1.0f, 0.0f};
	vda[13] = {0.5f, 0.5f, -0.5f, 1.0f, 1.0f};
	vda[14] = {0.5f, -0.5f, -0.5f, 0.0f, 1.0f};
	vda[15] = {0.5f, -0.5f, 0.5f, 0.0f, 0.0f};

	// Bottom face (Y = -0.5)
	vda[16] = {-0.5f, -0.5f, -0.5f, 0.0f, 1.0f};
	vda[17] = {0.5f, -0.5f, -0.5f, 1.0f, 1.0f};
	vda[18] = {0.5f, -0.5f, 0.5f, 1.0f, 0.0f};
	vda[19] = {-0.5f, -0.5f, 0.5f, 0.0f, 0.0f};

	// Top face (Y = 0.5)
	vda[20] = {-0.5f, 0.5f, -0.5f, 0.0f, 1.0f};
	vda[21] = {0.5f, 0.5f, -0.5f, 1.0f, 1.0f};
	vda[22] = {0.5f, 0.5f, 0.5f, 1.0f, 0.0f};
	vda[23] = {-0.5f, 0.5f, 0.5f, 0.0f, 0.0f};

	float *vertices = vda.getArray();

	unsigned int indices[] = {
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

	Shader shader("shaders/vertex.vert", "shaders/frag.frag");
	unsigned int VBO;
	glGenBuffers(1, &VBO);

	unsigned int EBO;
	glGenBuffers(1, &EBO);

	unsigned int VAO;
	unsigned int lightVAO;

	glGenVertexArrays(1, &VAO);
	glGenVertexArrays(1, &lightVAO);

	// normal VAO
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vda.get_size() * 5 * 4, vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// Position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// light VAO
	glBindVertexArray(lightVAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
	glEnableVertexAttribArray(0);

	glEnable(GL_DEPTH_TEST);

	Texture img("assets/star.jpeg");
	Texture img2("assets/image.jpg");

	glfwSetFramebufferSizeCallback(window, framebuffer_size_change);
	glfwSetCursorPosCallback(window, Mouse::mouse_move_callback);
	int t = 0;

	glm::vec3 poses[] = {
		glm::vec3(0., 0., 0.),
		glm::vec3(10., 3., 0.),
		glm::vec3(-2.2, 1.5, -1.),
		glm::vec3(0., -3., 0.),
		glm::vec3(0., 3., 3.),

	};

	while (!glfwWindowShouldClose(window))
	{
		processInput(window);
		cam.handleInputs(window);

		glClearColor(0., 0., 0., 1.);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shader.use();
		shader.set4f("objectColor", 0.f, 1.f, 0.3, 1.f);
		shader.set4f("lightColor", 1., 1.f, 1.f, 1.f);
		shader.seti("TIME", t);

		t++;

		// cam.lookAt(glm::vec3(0.f, 0.f, 0.f));
		glm::mat4 view = cam.getViewMatrix();

		glm::mat4 proj = cam.getProjectionMatrix(width, height);

		for (auto i : poses)
		{
			glm::mat4 trans = glm::mat4(1.);
			trans = glm::translate(trans, i);
			shader.setm4f("model", trans);
			shader.setm4f("view", view);
			shader.setm4f("projection", proj);
			glBindVertexArray(VAO);
			glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
		}
		// trans = glm::translate(trans, glm::vec3(0.f, 0.f, 1.5));
		// trans = glm::rotate(trans, glm::radians(t / 2.f), glm::vec3(0.f, 1.f, 0.f));
		// trans = glm::rotate(trans, glm::radians(t / 1.f), glm::vec3(1.f, 1.f, 0.f));

		Mouse::deltax = 0.;
		Mouse::deltay = 0.;
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}
