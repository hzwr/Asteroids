#include "Asteroid.h"
#include "Game.h"
#include "src/Vendor/Random.h"
#include "GameEngine/EntitySystem/Components/MoveComponent.h"
#include "GameEngine/EntitySystem/Components/SpriteComponent.h"
#include "GameEngine/EntitySystem/Components/WireframeComponent.h"
#include "GameEngine/EntitySystem/Components/ColliderComponent.h"

const int Pi = 3.1415926535f;

Asteroid::Asteroid(Game *game)
	:Actor(game)
	,mCollider(nullptr)
{
	// Random position
	Vector3 randPos = Random::GetVector(Vector3(-960.0f, -540.0f,0.0f),
		Vector3(960.0f, 540.0f, 0.0f));
	//Vector2 randPos(-960, -540);
	//Vector2 randPos(0, 0);
	SetPosition(randPos);

	float angle = Random::GetFloatRange(0.0f, Math::TwoPi);
	SetRotation(Quaternion(Vector3::UnitZ, angle));

	// Wireframe component
	//WireframeComponent *wireframe = new WireframeComponent(this);
	int radius = 30;
	//int numOfVerts = 12;
	//for (int i = 0; i < numOfVerts; ++i)
	//{
	//	float a = ((float)i / (float)numOfVerts) * Pi * 2;
	//	wireframe->mVertices.emplace_back(Vector2(radius * Math::Cos(a), radius * Math::Sin(a)));
	//}
	//wireframe->mVertices.emplace_back(wireframe->mVertices.front()); // Close the polygon


	// Sprite component
	SpriteComponent *spriteComponent = new SpriteComponent(this);
	spriteComponent->SetTexture(game->GetRenderer()->GetTexture("Assets/Asteroid.png"));

	MoveComponent *moveComponent = new MoveComponent(this);
	moveComponent->mVelocityVector = GetForward() * 150;

	mCollider = new ColliderComponent(this);
	mCollider->m_radius = radius;

	game->AddAsteroid(this);
}

Asteroid::~Asteroid()
{
	GetGame()->RemoveAsteroid(this);
}
