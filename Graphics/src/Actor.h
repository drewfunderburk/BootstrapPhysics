#pragma once
#include "glm\mat4x4.hpp"

class Actor
{
public:
	Actor() {}
	~Actor() {}

	void start();
	void update();
	void draw();
	void end();

	Actor* getParent() { return m_parent; }
	void setParent(Actor* actor) { m_parent = actor; }
	glm::mat4 getWorldTransform() { return m_worldTransform; }
	void updateWorldTransform();
	glm::mat4 getLocalTransform() { return m_localTransform; }
	void setLocalTransform(glm::mat4 transform) { m_localTransform = transform; }

private:
	Actor* m_parent = nullptr;
	glm::mat4 m_localTransform = glm::mat4(1.0f);
	glm::mat4 m_worldTransform = glm::mat4(1.0f);
};

