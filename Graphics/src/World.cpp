#include "World.h"
#include "glm\ext.hpp"

void World::start()
{
	// Initialize mesh
	m_mesh.start();

	// Create camera transforms
	m_viewMatrix = glm::lookAt
	(
		glm::vec3(10, 10, 10),
		glm::vec3(0),
		glm::vec3(0, 1, 0)
	);
	m_projectionMatrix = glm::perspective
	(
		glm::pi<float>() / 4.0f,
		(float)m_width / (float)m_height,
		0.001f,
		1000.0f
	);
}

void World::update()
{
}

void World::draw()
{
	m_mesh.draw();
}

void World::end()
{
}

glm::mat4 World::getProjectionViewModel()
{
	return m_projectionMatrix * m_viewMatrix * m_mesh.getTransform();
}
