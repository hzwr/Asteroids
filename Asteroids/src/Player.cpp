#include "Player.h"
#include "GameEngine\EntitySystem\Components\AnimSpriteComponent.h"
#include "Game.h"
#include "GameEngine\EntitySystem\Components\InputComponent.h"
#include "GameEngine\EntitySystem\Components\WireframeComponent.h"
#include "Bullet.h"
#include "GameEngine\EntitySystem\Components\ColliderComponent.h"
#include "Asteroid.h"

Player::Player(Game *game)
	:Actor(game)
	,mWeaponCooldown(0.0f)
	,mCollider(nullptr)
{
	//AnimSpriteComponent *anim = new AnimSpriteComponent(this);
	//std::vector<SDL_Texture *> textures = {
	//	game->GetTexture("Assets/Ship01.png"),
	//	game->GetTexture("Assets/Ship02.png"),
	//	game->GetTexture("Assets/Ship03.png"),
	//	game->GetTexture("Assets/Ship04.png")
	//};
	//anim->SetAnimTextures(textures);

	// Sprite component
	SpriteComponent *spriteComponent = new SpriteComponent(this);
	spriteComponent->SetTexture(game->GetRenderer()->GetTexture("Assets/Ship.png"));

	// Wireframe component
	/*WireframeComponent *wireframe = new WireframeComponent(this);
	wireframe->mVertices = { Vector2(0,-24), Vector2(18,24), Vector2(0,18), Vector2(-18,24), Vector2(0,-24) };*/

	// Create input component
	InputComponent *input = new InputComponent(this);
	input->mForwardKey = SDL_SCANCODE_W;
	input->mBackKey = SDL_SCANCODE_S;
	input->mClockwiseKey = SDL_SCANCODE_D;
	input->mCounterClockwiseKey = SDL_SCANCODE_A;
	input->mMaxForwardSpeed = 30.0f;
	input->mMaxAngularSpeed = Math::TwoPi;

	// Collider component
	mCollider = new ColliderComponent(this);
	mCollider->m_radius = 24.0f;
}

void Player::UpdateActor(float deltaTime)
{
	mWeaponCooldown -= deltaTime;
}

void Player::ActorInput(const uint8_t *keyState)
{
	if (keyState[SDL_SCANCODE_SPACE] && mWeaponCooldown <= 0.0f)
	{
		Bullet *bullet = new Bullet(GetGame(), GetRotation());
		bullet->SetPosition(GetPosition());	// Instantiate a bullet at the ship's postition
	
		mWeaponCooldown = 0.5f;
	}
}
