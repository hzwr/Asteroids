#include "WireframeComponent.h"
#include "../Actor.h"
#include "../../../Game.h"

WireframeComponent::WireframeComponent(Actor *owner, int drawOrder)
	:Component(owner)
	,mDrawOrder(drawOrder)
{
	m_owner->GetGame()->AddWireframe(this);
}

WireframeComponent::~WireframeComponent()
{
	m_owner->GetGame()->RemoveWireframe(this);
}

void WireframeComponent::Draw(SDL_Renderer *renderer)
{
	//if (!mVertices.empty())
	//{
	//	int numOfVertices = mVertices.size();
	//	SDL_Point *points = new SDL_Point[numOfVertices];

	//	Matrix3 rotationMatrix = Matrix3::CreateRotation(mOwner->GetRotation() - Math::PiOver2); // Original rotation is 90 degrees

	//	for (int i = 0; i < numOfVertices; ++i)
	//	{
	//		Vector2 rotatedVertex = Vector2::Transform(mVertices[i], rotationMatrix);
	//		points[i].x = mOwner->GetPosition().x + static_cast<int>(rotatedVertex.x);
	//		points[i].y = mOwner->GetPosition().y + static_cast<int>(rotatedVertex.y);
	//	}
	//	
	//	SDL_RenderDrawLines(renderer, points, numOfVertices);

	//	delete[] points;
	//}
}

