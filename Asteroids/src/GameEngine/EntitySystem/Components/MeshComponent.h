#pragma once
#include "../Component.h"

class MeshComponent:
	public Component
{
public:
	MeshComponent(class Actor *owner);
	~MeshComponent();

	virtual void Draw(class Shader *shader);
	virtual void SetMesh(class Mesh *mesh) { m_mesh = mesh; }
	void SetTextureIndex(size_t index) { m_textureIndex = index; }

private:
	class Mesh *m_mesh;
	size_t m_textureIndex; // which texture to use
};

