#include "Engine.h"
#include <gl_core_4_4.h>
#include <GLFW/glfw3.h>
#include <glm\ext.hpp>
#include <iostream>

aie::ShaderProgram* Engine::m_shader = nullptr;

Engine::Engine(int screenSizeX, int screenSizeY, const char* windowTitle) :
	m_screenSizeX(screenSizeX),
	m_screenSizeY(screenSizeY),
	m_windowTitle(windowTitle),
	m_world(new World(screenSizeX, screenSizeY))
{
	m_shader = new aie::ShaderProgram();
}

Engine::~Engine()
{
	delete m_world;
}

int Engine::run()
{
	int exitCode = 0;

	double currentTime = 0.0f;
	double previousTime = 0.0f;
	double deltaTime = 0.0f;

	exitCode = start();
	if (exitCode) return exitCode;

	while (!glfwWindowShouldClose(m_window) && glfwGetKey(m_window, GLFW_KEY_ESCAPE) != GLFW_PRESS)
	{
		// Get current time
		currentTime = glfwGetTime();
		// Find deltaTime
		deltaTime = currentTime - previousTime;
		// Update previous time
		previousTime = currentTime;

		exitCode = update(deltaTime);
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
	m_world->setWindow(m_window);
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
	m_shader->loadShader(aie::eShaderStage::VERTEX, "Shaders/Vertex.shader");
	m_shader->loadShader(aie::eShaderStage::FRAGMENT, "Shaders/Fragment.shader");
	if (!m_shader->link())
	{
		printf("Shader error: %s\n", m_shader->getLastError());
		return -7;
	}

	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);

	m_world->start();

	return 0;
}

int Engine::update(double deltaTime)
{
	if (!m_window) return -5;
	glfwPollEvents();
	m_world->update(deltaTime);
	return 0;
}

int Engine::draw()
{
	if (!m_window) return -5;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	m_shader->bind();

	m_shader->bindUniform("projectionViewMatrix", m_world->getProjectionViewMatrix());

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
