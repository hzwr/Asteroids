#include "Model.h"
#include <iostream>
#include "Mesh.h"
#include "Texture.h"
#include "Renderer.h"

Mesh *ProcessMesh(const aiMesh *const mesh, const aiScene *const scene, Renderer *renderer, const std::string &dir);
std::vector<Texture *> LoadTextures(const aiMaterial &material, aiTextureType aiType, TextureType type, Renderer *renderer, const std::string &dir);


Model::Model()
{
}

bool Model::Load(const std::string &fileName, Renderer *renderer)
{
	// Read file
	Assimp::Importer importer;
	const aiScene *scene = importer.ReadFile(
		fileName,
		aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_CalcTangentSpace
	);

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) // if not Zero
	{
		std::cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << std::endl;
		return false;
	}

	m_dir = fileName.substr(0, fileName.find_last_of('/'));

	ProcessNodes(scene->mRootNode, scene, renderer);

	return true;
}

void Model::Unload()
{
	for (auto mesh : m_meshes)
	{
		delete mesh;
		mesh = nullptr;
	}
}

void Model::ProcessNodes(const aiNode *const node, const aiScene *const scene, Renderer *renderer)
{
	// Recursively process child nodes
	for (unsigned int i = 0; i < node->mNumMeshes; ++i)
	{
		aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
		m_meshes.emplace_back(ProcessMesh(mesh, scene, renderer, m_dir));
	}

	for (unsigned int i = 0; i < node->mNumChildren; ++i)
	{
		ProcessNodes(node->mChildren[i], scene, renderer);
	}

}

Mesh *ProcessMesh(const aiMesh *const mesh, const aiScene *const scene, Renderer *renderer, const std::string& dir)
{

	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<Texture *> textures;

	// TODO: range-based for loop

	for (unsigned int i = 0; i < mesh->mNumVertices; ++i)
	{
		Vertex vertex;
		vertex.m_position = glm::vec3(
			mesh->mVertices[i].x,
			mesh->mVertices[i].y,
			mesh->mVertices[i].z
		);

		if (mesh->HasNormals())
		{
			vertex.m_normal = glm::vec3(
				mesh->mNormals[i].x,
				mesh->mNormals[i].y,
				mesh->mNormals[i].z
			);
		}

		if (mesh->mTextureCoords[0])
		{
			vertex.m_texCoords = glm::vec2(
				mesh->mTextureCoords[0][i].x,
				mesh->mTextureCoords[0][i].y
			);
		}
		else
		{
			vertex.m_texCoords = glm::vec2(0.0f);
		}
		
		vertices.emplace_back(vertex);

	}

	// Index buffer data
	for (unsigned int i = 0; i < mesh->mNumFaces; ++i)
	{
		auto face = mesh->mFaces[i];
		for (unsigned int j = 0; j < face.mNumIndices; ++j)
		{
			indices.emplace_back(face.mIndices[j]);
		}
	}

	// Materials
	if (mesh->mMaterialIndex >= 0)
	{
		aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];
		
		std::vector<Texture *> diffuseMaps = LoadTextures(
			*material,
			aiTextureType_DIFFUSE,
			TextureType::EDiffuse,
			renderer
			,dir
		);
		textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

		std::vector<Texture *> specularMaps = LoadTextures(
			*material,
			aiTextureType_SPECULAR,
			TextureType::ESpecular,
			renderer
			,dir
		);
		textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());

	}

	// Optimization?
	Mesh *newMesh = new Mesh(vertices, indices, textures);

	// For debugging
	newMesh->SetNumOfVerts(mesh->mNumVertices);

	return newMesh;
}

std::vector<Texture *> LoadTextures(const aiMaterial &material, aiTextureType aiType, TextureType type, Renderer *renderer, const std::string &dir)
{
	std::vector<Texture *> textures;
	for (unsigned int i = 0; i < material.GetTextureCount(aiType); ++i)
	{
		// Get filePath
		aiString fileName;
		material.GetTexture(
			aiType,		// type
			i,			// index
			&fileName	// filePath
		);

		// Check if the texture is cached, if not, load the texture
		Texture *t = renderer->GetTexture(dir + '/' + fileName.C_Str());
		
		// Check if the texture is already in our list, renderer maintain a list of all textures?
		// Take care of other texture info
		auto iter = std::find(textures.begin(), textures.end(), t);
		if (iter == textures.end())
		{
			// if not find
			t->SetTextureType(type);

			textures.emplace_back(t);
		}
	}
	return textures;
}
