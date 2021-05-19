#pragma once
#include "SpriteComponent.h"
#include <vector>

class AnimSpriteComponent: public SpriteComponent
{
public:
	AnimSpriteComponent(class Actor *owner, int drawOrder = 100);
	// Update animation every frame
	void Update(float deltaTime) override;
	void SetAnimTextures(const std::vector<SDL_Texture *> &textures);

	float mAnimFPS; // Use to control the speed of animation

private:
	std::vector<SDL_Texture *> mAnimTextures;
	
	// Tracks the current frame displayed as a float
	// allow to keep track of how long that frame has displayed
	float mCurrFrame; 
};


