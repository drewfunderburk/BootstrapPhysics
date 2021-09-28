#include <gl_core_4_4.h>
#include <GLFW/glfw3.h>
#include <iostream>

int main()
{
	// Initialize GLFW
	if (!glfwInit())
		return -1;
	printf("Initialized glfw\n");

	// Create window
	GLFWwindow* window = glfwCreateWindow(1280, 720, "Bootstrap Graphics", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -2;
	}
	glfwMakeContextCurrent(window);
	printf("Created window\n");

	// Load OpenGL
	if (ogl_LoadFunctions() == ogl_LOAD_FAILED)
	{
		glfwDestroyWindow(window);
		glfwTerminate();
		return -3;
	}
	printf("Loaded OpenGL functions\n");
	printf("OpenGL version %i.%i\n", ogl_GetMajorVersion(), ogl_GetMinorVersion());

	while (!glfwWindowShouldClose(window) && glfwGetKey(window, GLFW_KEY_ESCAPE)!= GLFW_PRESS)
	{
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// Cleanup and exit
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}