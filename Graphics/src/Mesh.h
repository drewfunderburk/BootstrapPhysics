#pragma once
#include <gl_core_4_4.h>
#include <glm\vec4.hpp>;
#include <glm\mat4x4.hpp>

class Mesh
{
public:
	struct Vertex
	{
		glm::vec4 position;
		glm::vec4 color;
		glm::vec4 normal;
	};

public:
	Mesh();
	virtual ~Mesh();

	void initializeQuad();
	void start();
	virtual void draw();

	virtual Vertex* generateVertices(unsigned int& vertexCount, unsigned int& triCount) = 0;

	glm::mat4 getTransform() { return m_transform; }
	void setTransform(glm::mat4 transform) { m_transform = transform; }

	glm::vec4 getColor() { return m_color; }
	void setColor(glm::vec4 color) { m_color = color; }

private:
	glm::mat4 m_transform;
	glm::vec4 m_color;
	unsigned int m_triCount, m_vertexArrayObject, m_vertexBufferObject, m_indexBufferObject;

};

