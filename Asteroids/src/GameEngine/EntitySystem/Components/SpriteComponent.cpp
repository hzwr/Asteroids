#include "SpriteComponent.h"
#include "../Actor.h"
#include "src/Game.h"
#include "src/Texture.h"

SpriteComponent::SpriteComponent(Actor *owner, int drawOrder)
	:Component(owner)
	,mTexture(nullptr)
	,mDrawOrder(drawOrder)
	,mTexWidth(0)
	,mTexHeight(0)
{
	mOwner->GetGame()->GetRenderer()->AddSprite(this);
}

SpriteComponent::~SpriteComponent()
{
	mOwner->GetGame()->GetRenderer()->RemoveSprite(this);
}

void SpriteComponent::Draw(Shader *shader)
{
	// Draw quad
	GLCall(glDrawElements(
		GL_TRIANGLES,
		6,
		GL_UNSIGNED_INT,
		nullptr
	));


	//if (mTexture)
	//{
	//	SDL_Rect r;
	//	// Scale
	//	r.w = static_cast<int>(mTexWidth * mOwner->mScale);
	//	r.h = static_cast<int>(mTexHeight * mOwner->mScale);
	//	// Calculate the top left coordinate
	//	r.x = static_cast<int>(mOwner->mPosition.x - r.w / 2);
	//	r.y = static_cast<int>(mOwner->mPosition.y - r.h / 2);
	//	SDL_RenderCopyEx(renderer,
	//		mTexture,
	//		nullptr,
	//		&r,
	//		-Math::ToDegrees(mOwner->mRotation), // In a clockwise direction
	//		nullptr,
	//		SDL_FLIP_NONE
	//	);
	//}
}

void SpriteComponent::SetTexture(Texture *texture)
{
	mTexture = texture;
	mTexHeight = texture->GetHeight();
	mTexWidth = texture->GetWidth();
}
