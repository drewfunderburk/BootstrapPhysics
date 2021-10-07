#include "Mesh.h"
#include "..\Engine.h"

Mesh::Mesh() :
    m_triCount(0),
    m_color(glm::vec4(1)),
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

    // Store memory position
    unsigned int memoryPosition = 0u;

    // Enable vertex position as first attribute
    glEnableVertexAttribArray(0);
    glVertexAttribPointer
    (
        0,                              // Attribute index
        4,                              // Number of values within attribute
        GL_FLOAT,                       // Type of each value
        GL_FALSE,                       // Whether or not to normalize
        sizeof(Vertex),                 // Size of one Vertex
        (void*)memoryPosition           // Position in memory of this attribute
    );

    // Shift memory position
    memoryPosition += sizeof(Vertex::position);

    // Enable vertex normal as second attribute
    glEnableVertexAttribArray(1);
    glVertexAttribPointer
    (
        1,                              // Attribute index
        4,                              // Number of values within attribute
        GL_FLOAT,                       // Type of each value
        GL_TRUE,                        // Whether or not to normalize
        sizeof(Vertex),                 // Size of one Vertex
        (void*)memoryPosition           // Position in memory of this attribute
    );

    // Shift memory position
    memoryPosition += sizeof(Vertex::normal);

    // Enable tex coord as third attribute
    glEnableVertexAttribArray(2);
    glVertexAttribPointer
    (
        2,                              // Attribute index
        2,                              // Number of values within attribute
        GL_FLOAT,                       // Type of each value
        GL_FALSE,                       // Whether or not to normalize
        sizeof(Vertex),                 // Size of one Vertex
        (void*)memoryPosition           // Position in memory of this attribute
    );

    // Shift memory position
    memoryPosition += sizeof(Vertex::texCoord);

    // Enable tangent as fourth attribute
    glEnableVertexAttribArray(3);
    glVertexAttribPointer
    (
        3,                              // Attribute index
        4,                              // Number of values within attribute
        GL_FLOAT,                       // Type of each value
        GL_FALSE,                       // Whether or not to normalize
        sizeof(Vertex),                 // Size of one Vertex
        (void*)memoryPosition           // Position in memory of this attribute
    );

    // Shift memory position
    memoryPosition += sizeof(Vertex::tangent);

    // Enable vertex color as fifth attribute
    glEnableVertexAttribArray(4);
    glVertexAttribPointer
    (
        4,                              // Attribute index
        4,                              // Number of values within attribute
        GL_FLOAT,                       // Type of each value
        GL_FALSE,                       // Whether or not to normalize
        sizeof(Vertex),                 // Size of one Vertex
        (void*)memoryPosition           // Position in memory of this attribute
    );

    // Shift memory position
    memoryPosition += sizeof(Vertex::color);

    // Unbind buffer and array
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

}

void Mesh::update(double deltaTime)
{
}

void Mesh::draw()
{
    Engine::getShader()->bindUniform("modelMatrix", m_transform);
    glBindVertexArray(m_vertexArrayObject);
    glDrawArrays(GL_TRIANGLES, 0, m_triCount * 3);
}
