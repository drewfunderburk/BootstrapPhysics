#pragma once
#include "Shader.h"
#include "World.h"

class GLFWwindow;
class Engine
{
public:
	Engine(int screenSizeX = 0, int screenSizeY = 0, const char* windowTitle = "Window");
	~Engine();

	int run();

	static aie::ShaderProgram* getShader() { return m_shader; }

private:
	int start();
	int update(double deltaTime);
	int draw();
	int end();

private:
	GLFWwindow* m_window = nullptr;
	int m_screenSizeX;
	int m_screenSizeY;
	const char* m_windowTitle;

	static aie::ShaderProgram* m_shader;
	World* m_world;
};

