#include "Asteroid.h"
#include "GameEngine\EntitySystem\Components\MoveComponent.h"
#include "GameEngine\EntitySystem\Components\SpriteComponent.h"
#include "Game.h"
#include <random>
#include "GameEngine\EntitySystem\Components\WireframeComponent.h"
#include "GameEngine\EntitySystem\Components\ColliderComponent.h"

const int Pi = 3.1415926535f;

Asteroid::Asteroid(Game *game)
	:Actor(game)
	,mCollider(nullptr)
{
	// Random position
	mPosition.x = std::rand() % 1920; // movement will take care of wrapping, no need for %
	mPosition.y = std::rand() % 1080;

	// Random rotation
	std::random_device rd;
	std::uniform_real_distribution<float> dist(0, 2 * Pi);
	std::mt19937 sGenerator;
	sGenerator.seed(rd());
	mRotation = dist(sGenerator);

	// Wireframe component
	WireframeComponent *wireframe = new WireframeComponent(this);
	int radius = 30;
	int numOfVerts = 12;
	for (int i = 0; i < numOfVerts; ++i)
	{
		float a = ((float)i / (float)numOfVerts) * Pi * 2;
		wireframe->mVertices.emplace_back(Vector2(radius * Math::Cos(a), -radius * Math::Sin(a)));
	}
	wireframe->mVertices.emplace_back(wireframe->mVertices.front()); // Close the polygon


	// Sprite component
	//SpriteComponent *spriteComponent = new SpriteComponent(this);
	//spriteComponent->SetTexture(game->GetTexture("Assets/Asteroid.png"));

	MoveComponent *moveComponent = new MoveComponent(this);
	moveComponent->mVelocityVector = GetForward() * 150;

	mCollider = new ColliderComponent(this);
	mCollider->mRadius = radius;

	game->AddAsteroid(this);
}

Asteroid::~Asteroid()
{
	GetGame()->RemoveAsteroid(this);
}
