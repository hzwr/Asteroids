#include "IndexBuffer.h"
#include "Renderer.h"

IndexBuffer::IndexBuffer(const unsigned int *data, unsigned int numIndices)
	: m_numIndices(numIndices)
{
	// Create index buffer
	GLCall(glGenBuffers(1, &m_indexBufferID));
	
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBufferID));
	// Copy index data into the index buffer
	GLCall(glBufferData(
		GL_ELEMENT_ARRAY_BUFFER,			// Specify a currently bound buffer type to write to
		numIndices * sizeof(unsigned int),	// Number of bytes
		data,								// Source to copy from
		GL_STATIC_DRAW						// Usage: load the data once and use it frequently for drawing
	));
}

IndexBuffer::~IndexBuffer()
{
	//GLCall(glDeleteBuffers(1, &m_indexBufferID));
}

void IndexBuffer::Bind() const
{
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBufferID));
}

void IndexBuffer::Unbind() const
{
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}
