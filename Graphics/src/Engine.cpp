#include "Engine.h"
#include <gl_core_4_4.h>
#include <GLFW/glfw3.h>
#include <iostream>

int Engine::run()
{
	int exitCode = 0;

	exitCode = start();
	if (exitCode) return exitCode;

	while (!glfwWindowShouldClose(m_window) && glfwGetKey(m_window, GLFW_KEY_ESCAPE) != GLFW_PRESS)
	{
		exitCode = update(0);
		if (exitCode) return exitCode;
		exitCode = draw();
		if (exitCode) return exitCode;
	}

	exitCode = end();
	if (exitCode) return exitCode;
	return 0;
}

int Engine::start()
{
	// Initialize GLFW
	if (!glfwInit())
		return -1;
	printf("Initialized glfw\n");

	// Create window
	m_window = glfwCreateWindow(m_screenSizeX, m_screenSizeY, m_windowTitle, NULL, NULL);
	if (!m_window)
	{
		glfwTerminate();
		return -2;
	}
	glfwMakeContextCurrent(m_window);
	printf("Created window\n");

	// Load OpenGL
	if (ogl_LoadFunctions() == ogl_LOAD_FAILED)
	{
		glfwDestroyWindow(m_window);
		glfwTerminate();
		return -3;
	}
	printf("Loaded OpenGL functions\n");
	printf("OpenGL version %i.%i\n", ogl_GetMajorVersion(), ogl_GetMinorVersion());

	return 0;
}

int Engine::update(float deltaTime)
{
	if (!m_window) return -5;
	glfwPollEvents();
	return 0;
}

int Engine::draw()
{
	if (!m_window) return -5;
	glfwSwapBuffers(m_window);
	return 0;
}

int Engine::end()
{
	// Cleanup and exit
	if (!m_window) return -6;
	glfwDestroyWindow(m_window);
	glfwTerminate();
	return 0;
}
