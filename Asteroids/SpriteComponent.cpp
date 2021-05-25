#include "SpriteComponent.h"
#include "Actor.h"
#include "Game.h"

SpriteComponent::SpriteComponent(Actor *owner, int drawOrder)
	:Component(owner)
	,mTexture(nullptr)
	,mDrawOrder(drawOrder)
	,mTexWidth(0)
	,mTexHeight(0)
{
	//mOwner->GetGame()->AddSprite(this);
}

SpriteComponent::~SpriteComponent()
{
	//mOwner->GetGame()->RemoveSprite(this);
}

void SpriteComponent::Draw(SDL_Renderer *renderer)
{
	if (mTexture)
	{
		SDL_Rect r;
		// Scale
		r.w = static_cast<int>(mTexWidth * mOwner->mScale);
		r.h = static_cast<int>(mTexHeight * mOwner->mScale);
		// Calculate the top left coordinate
		r.x = static_cast<int>(mOwner->mPosition.x - r.w / 2);
		r.y = static_cast<int>(mOwner->mPosition.y - r.h / 2);
		SDL_RenderCopyEx(renderer,
			mTexture,
			nullptr,
			&r,
			-Math::ToDegrees(mOwner->mRotation), // In a clockwise direction
			nullptr,
			SDL_FLIP_NONE
		);
	}
}

void SpriteComponent::SetTexture(SDL_Texture *texture)
{
	mTexture = texture;

	// Get width and height of the texture
	SDL_QueryTexture(texture, nullptr, nullptr, &mTexWidth, &mTexHeight);
}
