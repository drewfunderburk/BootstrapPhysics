#include "PhysicsScene.h"
#include "PhysicsObject.h"

PhysicsScene::PhysicsScene() : m_timeStep(0.01f), m_gravity(glm::vec2(0, -9.81f))
{

}

PhysicsScene::~PhysicsScene()
{
}

void PhysicsScene::addActor(PhysicsObject* actor)
{
	m_actors.insert(actor);
}

void PhysicsScene::removeActor(PhysicsObject* actor)
{
	m_actors.erase(actor);
}

void PhysicsScene::update(float deltaTime)
{
	static float accumulatedTime = 0.0f;
	accumulatedTime += deltaTime;

	// As long as there is enough accumulated time for a fixedUpdate...
	while (accumulatedTime >= m_timeStep)
	{
		// ...call each actor's fixedUpdate()
		for (PhysicsObject* actor : m_actors)
		{
			actor->fixedUpdate(m_gravity, deltaTime);
		}
		accumulatedTime -= m_timeStep;
	}
}

void PhysicsScene::draw()
{
	for (PhysicsObject* actor : m_actors)
		actor->draw();
}
