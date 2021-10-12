#pragma once
#include "glm\mat4x4.hpp"
#include "Quad.h"
#include "Camera.h"
#include "Texture.h"

class World
{
public:
	World(int width = 1280, int height = 720) :
		m_width(width),
		m_height(height),
		m_projectionMatrix(glm::mat4(1.0f)) {}
	~World() {}

	void start();
	void update();
	void draw();
	void end();

	glm::mat4 getProjectionViewModel();

private:
	int m_width, m_height;
	Quad m_quad;

	aie::Texture m_earthDiffuse;

	Camera m_camera = Camera();
	glm::mat4 m_projectionMatrix;
};

