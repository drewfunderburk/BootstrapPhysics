#include "Mesh.h"

Mesh::Mesh() :
    m_triCount(0),
    m_vertexArrayObject(0), 
    m_vertexBufferObject(0), 
    m_indexBufferObject(0),
    m_transform
    (
        { 1.0f, 0.0f, 0.0f, 0.0f,
          0.0f, 1.0f, 0.0f, 0.0f,
          0.0f, 0.0f, 1.0f, 0.0f,
          0.0f, 0.0f, 0.0f, 1.0f
        }
    )
{
}

Mesh::~Mesh()
{
    glDeleteVertexArrays(1, &m_vertexArrayObject);
    glDeleteBuffers(1, &m_vertexBufferObject);
    glDeleteBuffers(1, &m_indexBufferObject);
}

void Mesh::initializeQuad()
{
}

void Mesh::start()
{
    // Generate buffers
    glGenBuffers(1, &m_vertexBufferObject);
    glGenVertexArrays(1, &m_vertexArrayObject);

    // Bind vertex array and vertex buffer
    glBindVertexArray(m_vertexArrayObject);
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferObject);

    unsigned int vertexCount;
    m_triCount = 2;
    Vertex* vertices = generateVertices(vertexCount, m_triCount);

    // Fill vertex buffer
    glBufferData
    (
        GL_ARRAY_BUFFER,                // Type of buffer
        vertexCount * sizeof(Vertex),   // Size in bytes of all vertices
        vertices,                       // Vertex array
        GL_STATIC_DRAW                  // How the data will update
    );

    // Enable vertex position as first attribute
    glEnableVertexAttribArray(0);
    glVertexAttribPointer
    (
        0,                  // Attribute index
        4,                  // Number of values within attribute
        GL_FLOAT,           // Type of each value
        GL_FALSE,           // Whether or not to normalize
        sizeof(Vertex),     // Size of one Vertex
        0                   // Position in memory of this attribute
    );

    // Enable vertex color as second attribute
    glEnableVertexAttribArray(1);
    glVertexAttribPointer
    (
        1,                              // Attribute index
        4,                              // Number of values within attribute
        GL_FLOAT,                       // Type of each value
        GL_FALSE,                       // Whether or not to normalize
        sizeof(Vertex),                 // Size of one Vertex
        (void*)(sizeof(glm::vec4) * 1)  // Position in memory of this attribute
    );

    // Enable texture coordinate as third attribute
    glEnableVertexAttribArray(2);
    glVertexAttribPointer
    (
        2,                              // Attribute index
        2,                              // Number of values within attribute
        GL_FLOAT,                       // Type of each value
        GL_FALSE,                       // Whether or not to normalize
        sizeof(Vertex),                 // Size of one Vertex
        (void*)(sizeof(glm::vec4) * 2)  // Position in memory of this attribute
    );

    // Unbind buffer and array
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

}

void Mesh::draw()
{
    glBindVertexArray(m_vertexArrayObject);
    glDrawArrays(GL_TRIANGLES, 0, m_triCount * 3);
}
