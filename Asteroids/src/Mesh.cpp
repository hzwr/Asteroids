#include "Mesh.h"
#include <fstream>
#include <sstream>
#include <SDL/SDL_log.h>
#include <rapidjson/document.h>
#include "Renderer.h"
#include "VertexArray.h"
#include "math/Math.h"
#include "VertexBufferLayout.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "texture.h"

Mesh::Mesh(std::vector<Vertex> &vertices, std::vector<unsigned int> indices, std::vector<class Texture *>textures)
	:m_textures(textures)
{
	VertexBufferLayout layout;
	layout.Push<float>(3); // position
	layout.Push<float>(3); // normal
	layout.Push<float>(2); // texture
	size_t vertSize = 8;

	// Create and bind vertex buffer
	m_vertexBuffer = new VertexBuffer(
		vertices.data(),
		static_cast<unsigned>(vertices.size()) * layout.GetStride()
	);

	m_vertexArray = new VertexArray();

	// Bind vao and add buffer
	m_vertexArray->AddBuffer(
		*m_vertexBuffer,
		layout); 

	m_indexBuffer = new IndexBuffer(
		indices.data(),
		indices.size()
	);
}

Mesh::~Mesh()
{
}

void Mesh::Draw(Shader *shader, const Matrix4 &worldTransform)
{
	// Set the world transform
	shader->SetUniformMat4f("u_worldTransform", worldTransform);

	unsigned int diffuseNr = 1;
	unsigned int specularNr = 1;
	for (unsigned int i = 0; i < m_textures.size(); i++)
	{
		// retrieve texture number (the N in diffuse_textureN)
		std::string number;
		std::string name;
		if (m_textures[i]->GetTextureType() == TextureType::EDiffuse)
		{
			name = "texture_diffuse";
			number = std::to_string(diffuseNr++);
		}
		else if (m_textures[i]->GetTextureType() == TextureType::ESpecular)
		{
			name = "texture_specular";
			number = std::to_string(specularNr++);
		}

		shader->SetUniform1i((name + number).c_str(), i);

		m_textures[i]->Bind(i);

	}

	VertexArray *vao = GetVertexArray();
	vao->Bind();
	glDrawElements(
		GL_TRIANGLES,
		GetIndexBuffer()->GetNumIndices(),
		GL_UNSIGNED_INT,
		nullptr
	);
}

void Mesh::Unload()
{
	delete m_vertexArray;
	m_vertexArray = nullptr;

	delete m_vertexBuffer;
	m_vertexBuffer = nullptr;

	delete m_indexBuffer;
	m_indexBuffer = nullptr;
}

Texture *Mesh::GetTexture(size_t index)
{
	if (index < m_textures.size())
	{
		return m_textures[index];
	}
	else
	{
		return nullptr;
	}
}
