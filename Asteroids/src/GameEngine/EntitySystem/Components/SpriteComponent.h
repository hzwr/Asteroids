#pragma once
#include "../Component.h"
#include <SDL/SDL_render.h>

class SpriteComponent : public Component
{
public:
	SpriteComponent(class Actor *owner, int drawOrder = 100);
	~SpriteComponent();

	virtual void Draw(SDL_Renderer *renderer);
	virtual void SetTexture(SDL_Texture *texture);

	SDL_Texture *mTexture;
	int mDrawOrder;
	int mTexWidth;
	int mTexHeight;
};