#include "World.h"
#include "glm\ext.hpp"
#include "Engine.h"
#include "glfw/glfw3.h"

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

	Transform cameraTransform = m_camera.getTransform();
	cameraTransform.translate(glm::vec3(1.0f));
	cameraTransform.rotate(glm::vec3(-45.0f, 45.0f, 0.0f));
	m_camera.setTransform(cameraTransform); 
	// Create camera transforms
	//m_camera.setTransform(glm::lookAt
	//(
	//	glm::vec3(1, 1, 1),
	//	glm::vec3(0),
	//	glm::vec3(0, 1, 0)
	//));
	m_projectionMatrix = glm::perspective
	(
		m_camera.getFieldOfView() * glm::pi<float>() / 180.0f,
		(float)m_width / (float)m_height,
		m_camera.getNearClip(),
		m_camera.getFarClip()
	);
}

void World::update(double deltaTime)
{
	int keyForward = GLFW_KEY_W;
	int keyBack = GLFW_KEY_S;
	int keyLeft = GLFW_KEY_A;
	int keyRight = GLFW_KEY_D;
	int keyUp = GLFW_KEY_SPACE;
	int keyDown = GLFW_KEY_LEFT_CONTROL;

	float cameraSpeed = 1.0f;
	double cameraSensitivity = 1.0f;

	// Store previous mouse coordinates
	m_previousMouseX = m_currentMouseX;
	m_previousMouseY = m_currentMouseY;

	// Get camera vectors
	glm::vec3 cameraForward = glm::vec3(0.0f, 0.0f, 1.0f);
	glm::vec3 cameraRight = glm::vec3(1.0f, 0.0f, 0.0f);
	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

	// Get mouse position
	glfwGetCursorPos(m_window, &m_currentMouseX, &m_currentMouseY);

	// Rotate camera using change in mouse position
	double deltaMouseX = m_currentMouseX - m_previousMouseX;
	double deltaMouseY = m_currentMouseY - m_previousMouseY;

	if (deltaMouseX != 0 && deltaMouseY != 0)
	{
		Transform cameraTransform = m_camera.getTransform();
		cameraTransform.rotate(glm::vec3(deltaMouseY, deltaMouseX, 0.0f) * (float)(cameraSensitivity * deltaTime));
		m_camera.setTransform(cameraTransform);
	}

	if (glfwGetKey(m_window, keyForward))
	{
		// Move forward
		Transform cameraTransform = m_camera.getTransform();
		cameraTransform.translate(cameraForward * cameraSpeed * (float)deltaTime);
		m_camera.setTransform(cameraTransform);
	}
	if (glfwGetKey(m_window, keyBack))
	{
		// Move forward
		Transform cameraTransform = m_camera.getTransform();
		cameraTransform.translate(-cameraForward * cameraSpeed * (float)deltaTime);
		m_camera.setTransform(cameraTransform);
	}
	if (glfwGetKey(m_window, keyRight))
	{
		// Move forward
		Transform cameraTransform = m_camera.getTransform();
		cameraTransform.translate(-cameraRight * cameraSpeed * (float)deltaTime);
		m_camera.setTransform(cameraTransform);
	}
	if (glfwGetKey(m_window, keyLeft))
	{
		// Move forward
		Transform cameraTransform = m_camera.getTransform();
		cameraTransform.translate(cameraRight * cameraSpeed * (float)deltaTime);
		m_camera.setTransform(cameraTransform);
	}
	if (glfwGetKey(m_window, keyUp))
	{
		// Move forward
		Transform cameraTransform = m_camera.getTransform();
		cameraTransform.translate(-cameraUp * cameraSpeed * (float)deltaTime);
		m_camera.setTransform(cameraTransform);
	}
	if (glfwGetKey(m_window, keyDown))
	{
		// Move forward
		Transform cameraTransform = m_camera.getTransform();
		cameraTransform.translate(cameraUp * cameraSpeed * (float)deltaTime);
		m_camera.setTransform(cameraTransform);
	}
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
	return m_projectionMatrix * m_camera.getTransform().getMatrix();
}
