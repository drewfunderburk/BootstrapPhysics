#include "World.h"
#include "glm\ext.hpp"

void World::start()
{
	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	// Initialize mesh
	m_quad.start();

	// Create camera transforms
	//m_camera.setTransform(glm::lookAt
	//(
	//	glm::vec3(1, 1, 1),
	//	glm::vec3(0),
	//	glm::vec3(0, 1, 0)
	//));

	m_camera.setPosition(glm::vec3(1.0f, 1.0f, 1.0f));
	m_camera.setYaw(-135);
	m_camera.setPitch(-45);
	m_projectionMatrix = glm::perspective
	(
		m_camera.getFieldOfView() * glm::pi<float>() / 180.0f,
		(float)m_width / (float)m_height,
		m_camera.getNearClip(),
		m_camera.getFarClip()
	);
}

void World::update()
{
}

void World::draw()
{
	m_quad.draw();
}

void World::end()
{
}

glm::mat4 World::getProjectionViewModel()
{
	return m_projectionMatrix * m_camera.getViewMatrix() * m_quad.getTransform();
}
