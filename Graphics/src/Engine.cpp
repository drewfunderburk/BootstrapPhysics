#include "Engine.h"
#include <gl_core_4_4.h>
#include <GLFW/glfw3.h>
#include <glm\ext.hpp>
#include <iostream>

Engine::~Engine()
{
	delete m_world;
}

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

	// Initialize shader
	m_shader.loadShader(aie::eShaderStage::VERTEX, "Shaders/Vertex.shader");
	m_shader.loadShader(aie::eShaderStage::FRAGMENT, "Shaders/Fragment.shader");
	if (!m_shader.link())
	{
		printf("Shader error: %s\n", m_shader.getLastError());
		return -7;
	}

	m_world->start();

	return 0;
}

int Engine::update(float deltaTime)
{
	if (!m_window) return -5;
	glfwPollEvents();
	m_world->update();
	return 0;
}

int Engine::draw()
{
	if (!m_window) return -5;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	m_shader.bind();

	glm::mat4 projectViewModel = m_world->getProjectionViewModel();
	m_shader.bindUniform("projectionViewModel", projectViewModel);

	m_world->draw();

	glfwSwapBuffers(m_window);
	return 0;
}

int Engine::end()
{
	m_world->end();
	// Cleanup and exit
	if (!m_window) return -6;
	glfwDestroyWindow(m_window);
	glfwTerminate();
	return 0;
}
