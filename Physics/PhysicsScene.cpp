#include "PhysicsScene.h"
#include "PhysicsObject.h"
#include "Sphere.h"

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

		// Collision
		for (auto outer = m_actors.begin(); outer != --m_actors.end(); outer++)
		{
			for (auto inner = ++outer; inner != m_actors.end(); inner++)
			{
				PhysicsObject* object1 = *outer;
				PhysicsObject* object2 = *inner;

				// Collision check
				sphereToSphere(dynamic_cast<Sphere*>(object1), dynamic_cast<Sphere*>(object2));
			}
		}
	}
}

void PhysicsScene::draw()
{
	for (PhysicsObject* actor : m_actors)
		actor->draw();
}

bool PhysicsScene::sphereToSphere(Sphere* sphere1, Sphere* sphere2)
{
	
	return false;
}
