#pragma once
#include "../Component.h"
#include "../../../Renderer.h"

class SpriteComponent : public Component
{
public:
	SpriteComponent(class Actor *owner, int drawOrder = 100);
	~SpriteComponent();

	virtual void Draw(class Shader *shader);
	virtual void SetTexture(class Texture *texture);

	Texture *mTexture;
	int mDrawOrder;
	int mTexWidth;
	int mTexHeight;
};