#include "ModelComponent.h"
#include "Model.h"
#include "GameEngine/EntitySystem/Actor.h"
#include "Model.h"
#include "Mesh.h"
#include "Game.h"
#include "Renderer.h"


ModelComponent::ModelComponent(Actor *owner)
	:Component(owner)
{
	m_owner->GetGame()->GetRenderer()->AddModelComp(this);
}
ModelComponent::~ModelComponent()
{
	m_owner->GetGame()->GetRenderer()->RemoveModelComp(this);

}
void ModelComponent::Draw(Shader *shader)
{
	for (auto mesh : m_model->GetMeshes())
	{
		mesh->Draw(shader, m_owner->GetWorldTransform());
	}
}

