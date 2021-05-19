#include "Player.h"
#include "AnimSpriteComponent.h"
#include "Game.h"
#include "InputComponent.h"
#include "WireframeComponent.h"

Player::Player(Game *game)
	:Actor(game)
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
	InputComponent *input = new InputComponent(this);
	input->mForwardKey = SDL_SCANCODE_W;
	input->mBackKey = SDL_SCANCODE_S;
	input->mClockwiseKey = SDL_SCANCODE_D;
	input->mCounterClockwiseKey = SDL_SCANCODE_A;
	input->mMaxForwardSpeed = 30.0f;
	input->mMaxAngularSpeed = Math::TwoPi;
}

void Player::UpdateActor(float deltaTime)
{
}
