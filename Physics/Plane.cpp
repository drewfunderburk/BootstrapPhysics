#include "Plane.h"
#include "Gizmos.h"

Plane::Plane(glm::vec2 normal, float distance, glm::vec4 color) 
	: PhysicsObject(ShapeType::PLANE)
{
	m_normal = normal;
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
	glm::vec4 colorfade = m_color;
	colorfade.a = 0.0f;

	glm::vec2 start = centerPoint + (parallel * lineSegmentLength);
	glm::vec2 end = centerPoint - (parallel * lineSegmentLength);

	aie::Gizmos::add2DLine(start, end, m_color);
}
