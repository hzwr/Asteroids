#include "MeshComponent.h"
#include "src/GameEngine//EntitySystem/Actor.h"
#include "src/Game.h"
#include "src/Renderer.h"
#include "src/Shader.h"
#include "src/Mesh.h"
#include "src/Texture.h"
#include "src/VertexArray.h"
#include "src/VertexBuffer.h"
#include "src/IndexBuffer.h"

MeshComponent::MeshComponent(Actor *owner)
	:Component(owner)
{
	m_owner->GetGame()->GetRenderer()->AddMeshComp(this);

}

MeshComponent::~MeshComponent()
{
	m_owner->GetGame()->GetRenderer()->RemoveMeshComp(this);
}

void MeshComponent::Draw(Shader *shader)
{
	if (m_mesh)
	{
		shader->SetUniformMat4f("u_worldTransform", m_owner->GetWorldTransform());
		shader->SetUniform1f("u_specPower", m_mesh->GetSpecPower());
		Texture *t = m_mesh->GetTexture(m_textureIndex);
		if (t)
		{
			t->Bind();
		}

		VertexArray *vao = m_mesh->GetVertexArray();
		vao->Bind();
		glDrawElements(GL_TRIANGLES,
			m_mesh->GetIndexBuffer()->GetNumIndices(),
			GL_UNSIGNED_INT,
			nullptr);
	}
}