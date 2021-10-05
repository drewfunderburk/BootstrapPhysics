#include "World.h"
#include "glm\ext.hpp"
#include "Engine.h"

void World::start()
{
	// Initialize mesh
	m_quad.start();
	

	// Initialize the light
	m_light.setDirection(glm::vec3(-1.0f));
	m_light.setAmbient(glm::vec4(0.6f, 0.6f, 0.0f, 1.0f));
	m_light.setDiffuse(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
	m_light.setSpecular(glm::vec4(1.0f));
	m_light.setSpecularPower(1000.0f);

	// Create camera transforms
	m_camera.setTransform(glm::lookAt
	(
		glm::vec3(1, 1, 1),
		glm::vec3(0),
		glm::vec3(0, 1, 0)
	));
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
	Engine::getShader()->bindUniform("cameraPosition", glm::vec4(1.0f));
	Engine::getShader()->bindUniform("lightDirection", m_light.getDirection());
	Engine::getShader()->bindUniform("lightAmbient", m_light.getAmbient());
	Engine::getShader()->bindUniform("lightDiffuse", m_light.getDiffuse());
	Engine::getShader()->bindUniform("lightSpecular", m_light.getSpecular());
	Engine::getShader()->bindUniform("specularPower", m_light.getSpecularPower());
	m_quad.draw();
}

void World::end()
{
}

glm::mat4 World::getProjectionViewMatrix()
{
	return m_projectionMatrix * m_camera.getTransform();
}
