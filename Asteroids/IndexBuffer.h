#pragma once
class IndexBuffer
{
public:
	IndexBuffer(const unsigned int *data, unsigned int numIndices);
	~IndexBuffer();

	void Bind() const;
	void Unbind() const;
private:
	unsigned int m_indexBufferID;
	
	// How many indices
	unsigned int m_numIndices;
};
