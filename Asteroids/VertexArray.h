#pragma once
class VertexArray
{
public:
	VertexArray(const float *verts, unsigned int numVerts,
		const unsigned int *indices, unsigned int numIndices);
	~VertexArray();

	void SetActive();
private:
	unsigned int m_NumVerts;
	unsigned int m_NumIndices;	

	unsigned int m_VertexBuffer; // ID of vertex buffer
	unsigned int m_IndexBuffer;	// ID of index buffer
	unsigned int m_VAO; // OpenGL ID of VAO
};

