#include "VertexArray.h"
#include <GL/glew.h>
#include <string>
#include <iostream>

#include "Renderer.h"


VertexArray::VertexArray(const float *verts, unsigned int numVerts,
	const unsigned int *indices, unsigned int numIndices)
{
	// Allocate and assign a VAO to our handle
	GLCall(glGenVertexArrays(1, &m_VAO));
	// Bind our VAO as the current used object
	GLCall(glBindVertexArray(m_VAO));

	// Create vertex buffer
	GLCall(glGenBuffers(1, &m_VertexBuffer));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer));
	// Copy verts data into the vertex buffer
	GLCall(glBufferData(
		GL_ARRAY_BUFFER,				// Specify a currently bound buffer type to write to
		numVerts * 3 * sizeof(float),	// Number of bytes (x, y, z)
		verts,							// Source to copy from
		GL_STATIC_DRAW					// Usage: load the data once and use it frequently for drawing
	));

	// Create index buffer
	GLCall(glGenBuffers(1, &m_IndexBuffer));
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBuffer));
	GLCall(glBufferData(
		GL_ELEMENT_ARRAY_BUFFER,
		numIndices * sizeof(unsigned int),
		indices,
		GL_STATIC_DRAW
	));

	// Specify vertex attributes
	GLCall(glEnableVertexAttribArray(0));
	GLCall(glVertexAttribPointer(
		0,					// Attribute index 	
		3,					// Number of components
		GL_FLOAT,			// Type of the components
		GL_FALSE,			// Normalized
		sizeof(float) * 3,	// Stride between each vertex
		0));				// Offset from start of vertex attribute



	
	
	//int programDeleteStatus;
	//glGetProgramiv(shaderProgram, GL_DELETE_STATUS, &programDeleteStatus);
	//if (programDeleteStatus == GL_TRUE)
	//{
	//	std::cout << "The Shader program is currently flagged for deletion";
	//}
}

VertexArray::~VertexArray()
{
	GLCall(glDeleteBuffers(1, &m_VertexBuffer));
	GLCall(glDeleteBuffers(1, &m_IndexBuffer));
	GLCall(glDeleteVertexArrays(1, &m_VAO));

	//glDeleteProgram(shader);
}

void VertexArray::SetActive()
{
	// Specify which vertex array we are currently using
	GLCall(glBindVertexArray(m_VAO));
}
