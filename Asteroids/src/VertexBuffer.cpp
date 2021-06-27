#include "VertexBuffer.h"
#include "Renderer.h"

VertexBuffer::VertexBuffer(const void *data, unsigned int size)
{
	// Create vertex buffer
	GLCall(glGenBuffers(1, &m_vertexBufferID));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferID));
	// Copy verts data into the vertex buffer
	GLCall(glBufferData(
		GL_ARRAY_BUFFER,				// Specify a currently bound buffer type to write to
		size,							// Number of bytes
		data,							// Source to copy from
		GL_STATIC_DRAW					// Usage: load the data once and use it frequently for drawing
	));
}

VertexBuffer::~VertexBuffer()
{
	//GLCall(glDeleteBuffers(1, &m_vertexBufferID));
}

void VertexBuffer::Bind() const
{
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferID));
}

void VertexBuffer::Unbind() const
{
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}
