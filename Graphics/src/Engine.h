#pragma once
class GLFWwindow;
class Engine
{
public:
	Engine();
	Engine(int screenSizeX, int screenSizeY, const char* windowTitle);
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
};

