#include "World.h"
#include "glm\ext.hpp"
#include "gl_core_4_4.h"

void World::start()
{
	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	// Initialize mesh
	m_quad.start();
	if (m_earthDiffuse.load("src/Resources/earth_diffuse.jpg"))
		printf("Failed to load texture.\n");

	// Create camera transforms
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
	int program = -1;
	glGetIntegerv(GL_CURRENT_PROGRAM, &program);
	if (program == -1)
		printf("No shader bound.\n");

	int diffuseTextureUniform = glGetUniformLocation(program, "diffuseTexture");
	if (diffuseTextureUniform >= 0)
		glUniform1i(diffuseTextureUniform, 0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_earthDiffuse.getHandle());

	m_quad.draw();
}

void World::end()
{
}

glm::mat4 World::getProjectionViewModel()
{
	return m_projectionMatrix * m_camera.getViewMatrix() * m_quad.getTransform();
}
