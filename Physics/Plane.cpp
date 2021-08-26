#include "Plane.h"
#include "RigidBody.h"
#include "Gizmos.h"
#include <glm/ext.hpp>

Plane::Plane(glm::vec2 normal, float distance, glm::vec4 color) 
	: PhysicsObject(ShapeType::PLANE)
{
	m_normal = glm::normalize(normal);
	m_distance = distance;
	m_color = color;
}

Plane::~Plane()
{
}

void Plane::fixedUpdate(glm::vec2 gravity, float timeStep)
{
}

void Plane::draw()
{
	float lineSegmentLength = 300.0f;
	glm::vec2 centerPoint = m_normal * m_distance;
	glm::vec2 parallel(m_normal.y, -m_normal.x);

	glm::vec2 start = centerPoint + (parallel * lineSegmentLength);
	glm::vec2 end = centerPoint - (parallel * lineSegmentLength);

	aie::Gizmos::add2DLine(start, end, m_color);
}

void Plane::resolveCollision(RigidBody* other)
{
	// j = ((-1 + e) * Vrel) dot n) / (n dot (n * (1 / MA + 1 / MB))
	// j is the impulse magnitude
	// e is the coefficient of elasticity
	// Vrel is the relative velocity before collision
	// n is the collision normal
	// MA is the mass of object a
	// MB is the mass of object b

	// e
	float elasticity = 1.0f;

	// Vrel
	glm::vec2 relativeVelocity = other->getVelocity();

	// n
	glm::vec2 collisionNormal = getNormal();

	// MA would be infinite

	// MB
	float massB = other->getMass();

	// j
	float impulse =
		glm::dot((-(1 + elasticity) * relativeVelocity), collisionNormal)
		/ glm::dot(collisionNormal, (collisionNormal * (1 / massB)));

	other->applyForce(collisionNormal * impulse);
}
