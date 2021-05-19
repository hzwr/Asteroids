#include "Player.h"
#include "AnimSpriteComponent.h"
#include "Game.h"
#include "InputComponent.h"
#include "WireframeComponent.h"

Player::Player(Game *game)
	:Actor(game)
	,mRightSpeed(0.0f)
	,mDownSpeed(0.0f)
{
	//AnimSpriteComponent *anim = new AnimSpriteComponent(this);
	//std::vector<SDL_Texture *> textures = {
	//	game->GetTexture("Assets/Ship01.png"),
	//	game->GetTexture("Assets/Ship02.png"),
	//	game->GetTexture("Assets/Ship03.png"),
	//	game->GetTexture("Assets/Ship04.png")
	//};
	//anim->SetAnimTextures(textures);

	// Wireframe component
	WireframeComponent *wireframe = new WireframeComponent(this);
	wireframe->mVertices = { Vector2(0,-24), Vector2(18,24), Vector2(0,18), Vector2(-18,24), Vector2(0,-24) };

	// Create input component
	//InputComponent *input = new InputComponent(this);
	//input->mForwardKey = SDL_SCANCODE_W;
	//input->mBackKey = SDL_SCANCODE_S;
	//input->mClockwiseKey = SDL_SCANCODE_D;
	//input->mCounterClockwiseKey = SDL_SCANCODE_A;
	//input->mMaxForwardSpeed = 30.0f;
	//input->mMaxAngularSpeed = Math::TwoPi;
}

void Player::UpdateActor(float deltaTime)
{
	mPosition.x += mRightSpeed * deltaTime;
	mPosition.y += mDownSpeed * deltaTime;
	if (mPosition.x < 25.0f)
	{
		mPosition.x = 25.0f;
	}
	else if (mPosition.x > 500.0f)
	{
		mPosition.x = 500.0f;
	}
	if (mPosition.y < 25.0f)
	{
		mPosition.y = 25.0f;
	}
	else if (mPosition.y > 743.0f)
	{
		mPosition.y = 743.0f;
	}
	std::cout << "Postition: " << mPosition.x << " " << mPosition.y << std::endl;
}

void Player::ProcessKeyboard(const uint8_t *state)
{
	mRightSpeed = 0.0f;
	mDownSpeed = 0.0f;
	if (state[SDL_SCANCODE_D])
	{
		mRightSpeed += 250.0f;
	}
	if (state[SDL_SCANCODE_A])
	{
		mRightSpeed -= 250.0f;
	}
	// up/down
	if (state[SDL_SCANCODE_S])
	{
		mDownSpeed += 300.0f;
	}
	if (state[SDL_SCANCODE_W])
	{
		mDownSpeed -= 300.0f;
	}
}
