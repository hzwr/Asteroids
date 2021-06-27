#include "WireframeComponent.h"
#include "../Actor.h"
#include "../../../Game.h"

WireframeComponent::WireframeComponent(Actor *owner, int drawOrder)
	:Component(owner)
	,mDrawOrder(drawOrder)
{
	mOwner->GetGame()->AddWireframe(this);
}

WireframeComponent::~WireframeComponent()
{
	mOwner->GetGame()->RemoveWireframe(this);
}

void WireframeComponent::Draw(SDL_Renderer *renderer)
{
	if (!mVertices.empty())
	{
		int numOfVertices = mVertices.size();
		SDL_Point *points = new SDL_Point[numOfVertices];

		Matrix3 rotationMatrix = Matrix3::CreateRotation(mOwner->mRotation - Math::PiOver2); // Original rotation is 90 degrees

		for (int i = 0; i < numOfVertices; ++i)
		{
			Vector2 rotatedVertex = Vector2::Transform(mVertices[i], rotationMatrix);
			points[i].x = mOwner->mPosition.x + static_cast<int>(rotatedVertex.x);
			points[i].y = mOwner->mPosition.y + static_cast<int>(rotatedVertex.y);
		}
		
		SDL_RenderDrawLines(renderer, points, numOfVertices);

		delete[] points;
	}
}

