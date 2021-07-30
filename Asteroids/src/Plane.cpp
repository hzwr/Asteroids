#include "Plane.h"
#include "Game.h"
#include "Renderer.h"
#include "GameEngine/EntitySystem/Components/MeshComponent.h"

Plane::Plane(Game *game)
	:Actor(game)
{
	SetScale(10.0f);
	MeshComponent *mc = new MeshComponent(this);
	mc->SetMesh(GetGame()->GetRenderer()->GetMesh("Assets/Plane.gpmesh"));

}
