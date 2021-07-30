#pragma once
#include <vector>

#include <assimp/Importer.hpp>
#include <assimp/Scene.h>
#include <assimp/postprocess.h>

class Model
{
public:
	Model();

	bool Load(const std::string &fileName, class Renderer *renderer);
	void Unload();
	void ProcessNodes(const aiNode *const node, const aiScene *const scene, class Renderer *renderer);

	const std::vector<class Mesh *> &GetMeshes() const { return m_meshes; }

private:

	std::vector<class Mesh *> m_meshes;

	std::string m_dir; // Used to generate texture's filepath

	// Remove this?
	// class Renderer *m_renderer;


};

