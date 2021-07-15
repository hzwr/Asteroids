#include "SpriteComponent.h"
#include "../Actor.h"
#include "src/Game.h"
#include "src/Texture.h"
#include "src/Shader.h"

SpriteComponent::SpriteComponent(Actor *owner, int drawOrder)
	:Component(owner)
	,mTexture(nullptr)
	,mDrawOrder(drawOrder)
	,mTexWidth(0)
	,mTexHeight(0)
{
	m_owner->GetGame()->GetRenderer()->AddSprite(this);
}

SpriteComponent::~SpriteComponent()
{
	m_owner->GetGame()->GetRenderer()->RemoveSprite(this);
}

void SpriteComponent::Draw(Shader *shader)
{
	// Sclae the quad by the width/height of the texture
	Matrix4 scale = Matrix4::CreateScale(
		static_cast<float>(mTexWidth),
		static_cast<float>(mTexHeight),
		1.0f
	);
	Matrix4 worldTransform = scale * m_owner->GetWorldTransform();

	// Set world transform
	shader->SetUniformMat4f("u_worldTransform", worldTransform);
	
	// Set current texture
	mTexture->Bind();

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
