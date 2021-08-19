#include "RigidBody.h"

RigidBody::RigidBody(ShapeType shapeID, glm::vec2 position, glm::vec2 velocity, float orientation, float mass) 
	: PhysicsObject(shapeID)
{
	m_position = position;
	m_velocity = velocity;
	m_orientation = orientation;
	m_mass = mass;
}

RigidBody::~RigidBody()
{
}

void RigidBody::fixedUpdate(glm::vec2 gravity, float timeStep)
{
	// Update position
	m_position += m_velocity * timeStep;

	// Gravity
	applyForce(gravity * m_mass * timeStep);
}

void RigidBody::applyForce(glm::vec2 force)
{
	// a = F/m
	glm::vec2 acceleration = force / m_mass;
	m_velocity += acceleration;
}

void RigidBody::applyForceToOther(RigidBody* other, glm::vec2 force)
{
	// Apply force to other
	other->applyForce(force);
	// Apply inverse force to self based on Newton's Third Law
	applyForce(-force);
}
