#pragma once
#include <vector>
#include <string>
#include "Vendor/glm/glm.hpp"
#include "Vendor/glm/gtc/matrix_transform.hpp"
#include "math/Math.h"

struct Vertex {
	glm::vec3 m_position;
	glm::vec3 m_normal;
	glm::vec2 m_texCoords;
};

class Mesh
{
public:
	Mesh(std::vector<Vertex> &vertices, std::vector<unsigned int> indices, std::vector<class Texture *>textures);
	~Mesh();

	void Draw(class Shader *shader, const Matrix4 &worldTransform);
	//bool Load(const std::string &fileName, class Renderer *renderer);
	void Unload();

	class VertexArray *GetVertexArray() const { return m_vertexArray; }
	class VertexBuffer *GetVertexBuffer() const { return m_vertexBuffer; }
	class IndexBuffer *GetIndexBuffer() const { return m_indexBuffer; }
	class Texture *GetTexture(size_t index);
	const std::string &GetShaderName() const { return m_shaderName; }
	void SetNumOfVerts(unsigned int n) { m_numOfVerts = n; }
	float GetRadius() const { return m_radius; }
	float GetSpecPower() const { return m_specPower; }


private:
	class VertexArray *m_vertexArray;
	class VertexBuffer *m_vertexBuffer;
	class IndexBuffer *m_indexBuffer;

	unsigned int m_numOfVerts = 0;


	// Textures associated with this mesh
	std::vector<class Texture *> m_textures;
	// Name of shader specified by mesh
	std::string m_shaderName;
	// Object space bounding sphere radius for collision detection
	float m_radius;
	// Specular power of surface 
	float m_specPower; 
};

