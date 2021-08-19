#include "PhysicsScene.h"
#include "PhysicsObject.h"
#include "Sphere.h"
#include "glm/ext.hpp"

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
		auto outerEnd = m_actors.end();
		outerEnd--;
		for (auto outer = m_actors.begin(); outer != outerEnd; outer++)
		{
			auto innerStart = outer;
			innerStart++;
			for (auto inner = innerStart; inner != m_actors.end(); inner++)
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
	if (!sphere1 || !sphere2)
		return false;

	// Get the sum of the two radii
	float totalRadii = sphere1->getRadius() + sphere2->getRadius();

	// Get the distance between the two spheres
	float distance = 
		glm::sqrt(
			glm::pow(
				sphere2->getPosition().x - sphere1->getPosition().x, 
				2
			) + 
			glm::pow(
				sphere2->getPosition().y - sphere1->getPosition().y, 
				2
			)
		);

	// Test to ensure collisions are detected
	if (distance < totalRadii)
	{
		/*sphere1->applyForce(-(sphere1->getVelocity() * sphere1->getMass()));
		sphere2->applyForce(-(sphere2->getVelocity() * sphere2->getMass()));*/

		sphere1->applyForce(-sphere1->getVelocity() * sphere1->getMass());
		sphere2->applyForce(-sphere2->getVelocity() * sphere2->getMass());

		return true;
	}

	return false;
}
