#pragma once
#include "glm\mat4x4.hpp"
#include "Mesh\Quad.h"
#include "Camera.h"
#include "Light.h"

class GLFWwindow;

class World
{
public:
	World(int width = 1280, int height = 720) :
		m_width(width),
		m_height(height),
		m_projectionMatrix(glm::mat4(1.0f)) {}
	~World() {}

	void start();
	void update(double deltaTime);
	void draw();
	void end();

	glm::mat4 getProjectionViewMatrix();

	GLFWwindow* getWindow() { return m_window; }
	void setWindow(GLFWwindow* window) { m_window = window; }

private:
	int m_width, m_height;
	Quad m_quad;

	Camera m_camera = Camera();
	glm::mat4 m_projectionMatrix;
	Light m_light = Light();

	GLFWwindow* m_window = nullptr;
	double m_currentMouseX = 0.0;
	double m_currentMouseY = 0.0;
	double m_previousMouseX = 0.0;
	double m_previousMouseY = 0.0;
};

