#pragma once
#include "Shader.h"
#include "World.h"

class GLFWwindow;
class Engine
{
public:
	Engine(int screenSizeX = 0, int screenSizeY = 0, const char* windowTitle = "Window") :
		m_screenSizeX(screenSizeX),
		m_screenSizeY(screenSizeY),
		m_windowTitle(windowTitle),
		m_world(new World(screenSizeX, screenSizeY)) {}
	~Engine();

	int run();

private:
	int start();
	int update(float deltaTime);
	int draw();
	int end();

private:
	GLFWwindow* m_window = nullptr;
	int m_screenSizeX;
	int m_screenSizeY;
	const char* m_windowTitle;

	aie::ShaderProgram m_shader;
	World* m_world;
};

