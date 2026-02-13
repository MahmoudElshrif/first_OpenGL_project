#pragma once
#include <GLFW/glfw3.h>

class Mouse
{
public:
	static double x, y;
	static double deltax, deltay;

	static void mouse_move_callback(GLFWwindow *window, double posx, double posy)
	{
		deltax = posx - x;
		deltay = posy - y;
		x = posx;
		y = posy;
		int width, height;
		glfwGetWindowSize(window, &width, &height);
		// while (x > width)
		// {
		// 	x -= width;
		// }
		// while (x < 0)
		// {
		// 	x += width;
		// }

		// while (y > height)
		// {
		// 	y -= height;
		// }
		// while (y < 0)
		// {
		// 	y += height;
		// }

		// glfwSetCursorPos(window, x, y);
	}
};

double Mouse::x = 0;
double Mouse::y = 0;
double Mouse::deltax = 0;
double Mouse::deltay = 0;