#pragma once

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

class VertexArray
{
public:
	VertexArray();
	~VertexArray();

	void Bind() const;
	void Unbind() const;
	void AddBuffer(const VertexBuffer &vb, const VertexBufferLayout &layout);

	//unsigned int GetVertexBufferID() const { return m_vb; }
private:
	unsigned int m_VAO; // OpenGL ID of VAO
};

