#include "PhysicsGame.h"
#include "Input.h"
#include "Font.h"
#include "Gizmos.h"
#include <glm/ext.hpp>

#include "Sphere.h"
#include "Plane.h"

bool PhysicsGame::startup()
{
	aie::Gizmos::create(255U, 255U, 65535U, 65535U);

	m_renderer = new aie::Renderer2D();
	m_font = new aie::Font("../bin/font/consolas.ttf", 32);

	setBackgroundColour(0.1f, 0.1f, 0.1f);

	m_scene = new PhysicsScene();

	Sphere* sphere = new Sphere(glm::vec2(20, 0), glm::vec2(), 1, 0.5f, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
	m_scene->addActor(sphere);

	Sphere* sphere1 = new Sphere(glm::vec2(-20, 0), glm::vec2(), 1, 10, glm::vec4(0.0f, 1.0f, 1.0f, 1.0f));
	m_scene->addActor(sphere1);

	Plane* surface = new Plane(glm::vec2(0.1f, 1.0f), -30.0f, glm::vec4(0.2f, 0.8f, 0.2f, 1.0f));
	m_scene->addActor(surface);

	return true;
}

void PhysicsGame::shutdown()
{
	delete m_renderer;
	delete m_font;
	delete m_scene;
}

void PhysicsGame::update(float deltaTime)
{
	// Get input instance
	aie::Input* input = aie::Input::getInstance();

	aie::Gizmos::clear();

	m_scene->update(deltaTime);

	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();
}

void PhysicsGame::draw()
{
	clearScreen();
	
	m_renderer->begin();
	
	// Draw scene
	m_scene->draw();

	// Draw Gizmos
	static float aspectRatio = 16.0f / 9.0f;
	aie::Gizmos::draw2D(
		glm::ortho<float>(
			-100,				// Left
			100,				// Right
			-100 / aspectRatio,	// Top
			100 / aspectRatio,	// Bottom
			-1.0f,				// zNear
			1.0f				// zFar
		)
	);

	// Draw FPS
	char fps[32];
	sprintf_s(fps, 32, "FPS: %i", getFPS());
	m_renderer->setRenderColour(0, 1, 0);
	m_renderer->drawText(m_font, fps, 0, 720 - 32);

	m_renderer->end();
}
