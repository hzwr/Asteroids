#pragma once
#include "math/Math.h"
#include "../Component.h"
#include "SDL/SDL.h"
#include <vector>

class WireframeComponent :
    public Component
{
public:
    WireframeComponent(class Actor *owner, int drawOrder = 100);
    ~WireframeComponent();

    void Draw(SDL_Renderer *renderer);

    std::vector<Vector2> mVertices;
    int mDrawOrder;
};

