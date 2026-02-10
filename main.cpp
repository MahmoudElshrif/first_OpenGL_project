#include <cmath>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "classes/shader.cpp"
#include "classes/Image.cpp"
#include "classes/Vertex.cpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

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

	float fov = 45.;

	if (window == NULL)
	{
		std::cout << "FAILURE AFTER FAILURE AFTER FAILURE" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwShowWindow(window);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	glViewport(0, 0, 800, 800);

	VertexDataArray vda(4);

	vda[0] = {0.5, 0.5, 0, 0.f, 1.f, 0.f, 1.f, 1.f};
	vda[1] = {0.5, -0.5, 0, 0.f, 0.f, 1.f, 1., 0.f};
	vda[2] = {-0.5, -0.5, 0, 1.f, 0.f, 0.f, 0.f, 0.f};
	vda[3] = {-0.5, 0.5, 0, 1.f, 0.f, 0.f, 0.f, 1.f};

	float *vertices = vda.getArray();

	unsigned int indices[]{
		0, 1, 2,
		2, 3, 0

	};

	Shader shader("shaders/vertex.glsl", "shaders/frag.glsl");
	unsigned int VBO;
	glGenBuffers(1, &VBO);

	unsigned int EBO;
	glGenBuffers(1, &EBO);

	unsigned int VAO;
	glGenVertexArrays(1, &VAO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vda.get_size() * 8 * 4, vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// Position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)0);
	glEnableVertexAttribArray(0);

	// Color
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	Texture img("assets/star.jpeg");
	Texture img2("assets/image.jpg");

	glfwSetFramebufferSizeCallback(window, framebuffer_size_change);

	int t = 0;

	while (!glfwWindowShouldClose(window))
	{
		// std::cout << "shitting fuck\n";
		processInput(window);

		glClearColor(0., 0., 0., 1.);
		glClear(GL_COLOR_BUFFER_BIT);

		shader.use();
		shader.seti("TEXTURE", 0);
		shader.seti("OTHERTEXTURE", 1);
		shader.seti("TIME", t);

		t++;
		glm::mat4 trans = glm::mat4(1.);
		trans = glm::rotate(trans, glm::radians(t / 2.f), glm::vec3(0.f, 1.f, 0.f));
		trans = glm::translate(trans, glm::vec3(0.f, 0.f, 2.));

		glm::mat4 view = glm::mat4(1.);
		view = glm::translate(view, glm::vec3(0., 0., -5.));

		glm::mat4 proj = glm::perspective(glm::radians(fov), (float)width / (float)height, 0.1f, 100.f);

		shader.setm4f("model", trans);
		shader.setm4f("view", view);
		shader.setm4f("projection", proj);

		img2.use(0);
		img.use(1);
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}
