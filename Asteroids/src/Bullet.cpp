#include "Bullet.h"
#include "Game.h"
#include "Math.h"
#include "Asteroid.h"
#include "GameEngine\EntitySystem\Components\MoveComponent.h"
#include "GameEngine\EntitySystem\Components\WireframeComponent.h"
#include "GameEngine\EntitySystem\Components\ColliderComponent.h"
#include "GameEngine\EntitySystem\Components\SpriteComponent.h"

Bullet::Bullet(Game *game, Quaternion rotation)
	:Actor(game)
	,mTimer(1.5f)
{

	// Move component
	MoveComponent *move = new MoveComponent(this);
	move->SetForwardSpeed(5.0f);
	SetRotation(rotation);
	move->mVelocityVector = GetForward() * 100;

	// Sprite component
	SpriteComponent *spriteComponent = new SpriteComponent(this);
	spriteComponent->SetTexture(game->GetRenderer()->GetTexture("Assets/Laser.png"));

	// Wireframe component
	//WireframeComponent *wireframe = new WireframeComponent(this);
	//int radius = 2;
	//int numOfVerts = 12;
	//for (int i = 0; i < numOfVerts; ++i)
	//{
	//	float a = ((float)i / (float)numOfVerts) * Math::Pi * 2;
	//	wireframe->mVertices.emplace_back(Vector2(radius * Math::Cos(a), -radius * Math::Sin(a)));
	//}

	/*game->AddBullet*/
	// TODO: ownership of the bullet?
	// collision detection for each bullet against all asteroids

	mCollider = new ColliderComponent(this);
	mCollider->m_radius = 2.0f;
}

void Bullet::UpdateActor(float deltaTime)
{
	mTimer -= deltaTime;
	if (mTimer <= 0.0f)
	{
		SetState(ActorState::EDead);
	}

	for (auto asteroid : GetGame()->GetAsteroids())
	{
		if (Intersect(*mCollider, *(asteroid->GetCollider())))
		{
			SetState(ActorState::EDead);
			asteroid->SetState(ActorState::EDead);
			break;
		}
	}
}
