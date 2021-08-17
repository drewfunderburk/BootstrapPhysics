#pragma once
#include "glm/vec2.hpp"

class PhysicsObject
{
protected:
	PhysicsObject() {}
	~PhysicsObject() {}

public:
	virtual void fixedUpdate(glm::vec2 gracity, float timeStep) = 0;
	virtual void draw() = 0;
	virtual void resetPosition() {}
};

