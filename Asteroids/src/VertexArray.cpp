#include "VertexArray.h"
#include <GL/glew.h>
#include <string>
#include <iostream>
#include "Renderer.h"

VertexArray::VertexArray()
{
	GLCall(glGenVertexArrays(1, &m_VAO));

	//int programDeleteStatus;
	//glGetProgramiv(shaderProgram, GL_DELETE_STATUS, &programDeleteStatus);
	//if (programDeleteStatus == GL_TRUE)
	//{
	//	std::cout << "The Shader program is currently flagged for deletion";
	//}
}

VertexArray::~VertexArray()
{
	GLCall(glDeleteVertexArrays(1, &m_VAO));
	//glDeleteProgram(shader);
}

void VertexArray::Bind() const
{
	// Bind our VAO as the current used object
	GLCall(glBindVertexArray(m_VAO));
}

void VertexArray::Unbind() const
{
	GLCall(glBindVertexArray(0));
}

void VertexArray::AddBuffer(const VertexBuffer &vb, const VertexBufferLayout &layout)
{
	//m_vb = vb.GetVertexBufferID();
	Bind();
	vb.Bind();

	const auto &elements = layout.GetElements();
	unsigned int offset = 0;
	for (unsigned int i = 0; i < elements.size(); ++i)
	{
		const auto &element = elements[i];
		GLCall(glEnableVertexAttribArray(i));
		GLCall(glVertexAttribPointer(
			i,							// Attribute index 	
			element.count,				// Number of components
			element.type,				// Type of the components
			element.normalized,			// Normalized
			layout.GetStride(),			// Stride between each vertex
			(const void *)offset))		// Offset from start of vertex attribute
		offset += element.count * VertexBufferElement::GetSizeOfType(element.type);
	}
}
