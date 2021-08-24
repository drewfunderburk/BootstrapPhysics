#include "PhysicsScene.h"

#include "glm/ext.hpp"
#include "PhysicsObject.h"
#include "Sphere.h"
#include "Plane.h"

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

// Collision function pointer type
typedef bool(*collisionCheck)(PhysicsObject*, PhysicsObject*);

// Array of collision check functions
static const collisionCheck collisionFunctionArray[] =
{
	PhysicsScene::planeToPlane,		PhysicsScene::planeToSphere,	PhysicsScene::planeToBox,
	PhysicsScene::sphereToPlane,	PhysicsScene::sphereToSphere,	PhysicsScene::sphereToBox,
	PhysicsScene::boxToPlane,		PhysicsScene::boxToSphere,		PhysicsScene::boxToBox
};

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

				int shape1 = (int)(object1->getShapeID());
				int shape2 = (int)(object2->getShapeID());

				// Find index using i = (y * w) + x
				int i = (shape1 * (int)ShapeType::LENGTH) + shape2;

				// Retrieve and call proper collision check function
				collisionCheck collisionFn = collisionFunctionArray[i];
				if (collisionFn)
					collisionFn(object1, object2);
			}
		}
	}
}

void PhysicsScene::draw()
{
	for (PhysicsObject* actor : m_actors)
		actor->draw();
}

bool PhysicsScene::planeToPlane(PhysicsObject* object1, PhysicsObject* object2)
{
	return false;
}

bool PhysicsScene::planeToSphere(PhysicsObject* object1, PhysicsObject* object2)
{
	return sphereToPlane(object2, object1);
}

bool PhysicsScene::planeToBox(PhysicsObject* object1, PhysicsObject* object2)
{
	return boxToPlane(object2, object1);
}

bool PhysicsScene::sphereToPlane(PhysicsObject* object1, PhysicsObject* object2)
{
	Sphere* sphere = dynamic_cast<Sphere*>(object1);
	Plane* plane = dynamic_cast<Plane*>(object2);

	if (!sphere || !plane)
		return false;

	// D1 = (C dot N) - D - R
	// D1 is the distance from the sphere surface to plane surface
	// C is the center of the sphere
	// N is the normal of the plane
	// D is the distance from the plane to the origin
	// R is the radius of the sphere

	// C
	glm::vec2 sphereCenter = sphere->getPosition();

	// N
	glm::vec2 planeNormal = plane->getNormal();

	// D
	float planeDistance = plane->getDistance();

	// R
	float sphereRadius = sphere->getRadius();

	// D1
	float sphereToPlaneDistance = glm::dot(sphereCenter, planeNormal) - planeDistance - sphereRadius;

	if (sphereToPlaneDistance <= 0)
	{
		sphere->applyForce(-sphere->getVelocity() * sphere->getMass());
		return true;
	}

	return false;
}

bool PhysicsScene::sphereToSphere(PhysicsObject* object1, PhysicsObject* object2)
{
	Sphere* sphere1 = dynamic_cast<Sphere*>(object1);
	Sphere* sphere2 = dynamic_cast<Sphere*>(object2);

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
	if (glm::abs(distance) < totalRadii)
	{
		sphere1->applyForce(-sphere1->getVelocity() * sphere1->getMass());
		sphere2->applyForce(-sphere2->getVelocity() * sphere2->getMass());

		return true;
	}

	return false;
}

bool PhysicsScene::sphereToBox(PhysicsObject* object1, PhysicsObject* object2)
{
	return boxToSphere(object2, object1);
}

bool PhysicsScene::boxToPlane(PhysicsObject* object1, PhysicsObject* object2)
{
	return false;
}

bool PhysicsScene::boxToSphere(PhysicsObject* object1, PhysicsObject* object2)
{
	return false;
}

bool PhysicsScene::boxToBox(PhysicsObject* object1, PhysicsObject* object2)
{
	return false;
}
