#pragma once
class VertexBuffer
{
public:
	VertexBuffer(const void* data, unsigned int size);
	~VertexBuffer();

	void Bind() const;
	void Unbind() const;

	//unsigned int GetVertexBufferID() const { return m_vertexBufferID; }

private:
	unsigned int m_vertexBufferID;
};

