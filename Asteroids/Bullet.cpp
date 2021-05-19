#include "Bullet.h"
#include "MoveComponent.h"
#include "Game.h"
#include "WireframeComponent.h"
#include "Math.h"
#include "ColliderComponent.h"
#include "Asteroid.h"

Bullet::Bullet(Game *game, float rotation)
	:Actor(game)
	,mTimer(1.5f)
{

	// Move component
	MoveComponent *move = new MoveComponent(this);
	move->mForwardSpeed = 5.0f;
	mRotation = rotation;
	move->mVelocityVector = GetForward() * 100;

	// Wireframe component
	WireframeComponent *wireframe = new WireframeComponent(this);
	int radius = 2;
	int numOfVerts = 12;
	for (int i = 0; i < numOfVerts; ++i)
	{
		float a = ((float)i / (float)numOfVerts) * Math::Pi * 2;
		wireframe->mVertices.emplace_back(Vector2(radius * Math::Cos(a), -radius * Math::Sin(a)));
	}

	/*game->AddBullet*/
	// TODO: ownership of the bullet?
	// collision detection for each bullet against all asteroids

	mCollider = new ColliderComponent(this);
	mCollider->mRadius = 2.0f;
}

void Bullet::UpdateActor(float deltaTime)
{
	mTimer -= deltaTime;
	if (mTimer <= 0.0f)
	{
		mState = ActorState::EDead;
	}

	for (auto asteroid : GetGame()->GetAsteroids())
	{
		if (Intersect(*mCollider, *(asteroid->GetCollider())))
		{
			mState = ActorState::EDead;
			asteroid->mState = ActorState::EDead;
			break;
		}
	}
}
