#pragma once
#include <vector>
#include <string>

class Mesh
{
public:
	Mesh();
	~Mesh();

	bool Load(const std::string &fileName, class Renderer *renderer);
	void Unload();

	class VertexArray *GetVertexArray() const { return m_vertexArray; }
	class VertexBuffer *GetVertexBuffer() const { return m_vertexBuffer; }
	class IndexBuffer *GetIndexBuffer() const { return m_indexBuffer; }
	class Texture *GetTexture(size_t index);
	const std::string &GetShaderName() const { return m_shaderName; }
	float GetRadius() const { return m_radius; }
	float GetSpecPower() const { return m_specPower; }


private:
	class VertexArray *m_vertexArray;
	class VertexBuffer *m_vertexBuffer;
	class IndexBuffer *m_indexBuffer;

	// Textures associated with this mesh
	std::vector<class Texture *> m_textures;
	// Name of shader specified by mesh
	std::string m_shaderName;
	// Object space bounding sphere radius for collision detection
	float m_radius;
	// Specular power of surface 
	float m_specPower; 
};

