#include "Quad.h"

Mesh::Vertex* Quad::generateVertices(unsigned int& vertexCount, unsigned int& triCount)
{
    // Define vertices for a quad
    Vertex* vertices = nullptr;
    vertexCount = 6;
    triCount = 2;
    vertices = new Vertex[vertexCount];

    vertices[0].position = { -0.5f,  0.0f,  0.5f, 1.0f };
    vertices[1].position = { 0.5f,  0.0f,  0.5f, 1.0f };
    vertices[2].position = { -0.5f,  0.0f, -0.5f, 1.0f };

    vertices[3].position = { 0.5f,  0.0f,  0.5f, 1.0f };
    vertices[4].position = { -0.5f,  0.0f, -0.5f, 1.0f };
    vertices[5].position = { 0.5f,  0.0f, -0.5f, 1.0f };

    for (int i = 0; i < vertexCount; i++)
    {
        vertices[i].color = { 0.0f, 0.5f, 0.5f, 1.0f };
        vertices[i].normal = { 0.0f, 1.0f, 0.0f, 0.0f };
    }

    vertices[5].normal = { 1.0f, 0.0f, 0.0f, 0.0f };

    return vertices;
}
