#include "PhysicsGame.h"
#include "Input.h"
#include "Font.h"
#include "Gizmos.h"
#include <glm/ext.hpp>

bool PhysicsGame::startup()
{
	m_renderer = new aie::Renderer2D();
	m_font = new aie::Font("../bin/font/consolas.ttf", 32);

	setBackgroundColour(0.1f, 0.1f, 0.1f);

	return true;
}

void PhysicsGame::shutdown()
{
	delete m_renderer;
	delete m_font;
}

void PhysicsGame::update(float deltaTime)
{
	// Get input instance
	aie::Input* input = aie::Input::getInstance();

	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();
}

void PhysicsGame::draw()
{
	clearScreen();
	
	m_renderer->begin();

	// Draw FPS
	char fps[32];
	sprintf_s(fps, 32, "FPS: %i", getFPS());
	m_renderer->setRenderColour(0, 1, 0);
	m_renderer->drawText(m_font, fps, 0, 720 - 32);

	m_renderer->end();
}
