#pragma once
class VertexArray
{
public:
	VertexArray(const float *verts, unsigned int numVerts,
		const unsigned int *indices, unsigned int numIndices);
	~VertexArray();

	void SetActive();
private:
	unsigned int mNumVerts;
	unsigned int nNumIndices;	
	unsigned int mVertexBuffer; // ID of vertex buffer
	unsigned int mIndexBuffer;	// ID of index buffer
	unsigned int mVertexArray; // OpenGL ID of VAO
};

