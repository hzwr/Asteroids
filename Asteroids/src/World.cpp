#include "World.h"
#include <iostream>

World::World(int maxWidth, int maxHeight, SDL_Renderer *renderer):
	maxHeight_(maxHeight)
	,maxWidth_(maxWidth)
	,mRenderer(renderer)
{
	ConstructGraph();

	// Render
	tiles_ = new Tile::Tile[1296];
	for (int i = 0; i < 1296; ++i)
	{
		tiles_[i].id = i;
	}
}

World::~World()
{
	delete[] tiles_;
	tiles_ = nullptr;
}

void World::ConstructGraph()
{
	for (int i = 0; i < maxHeight_ * maxWidth_; ++i)
	{
		GraphNode *node = new GraphNode;
		node->id = i;
		g.mNodes.emplace_back(node);
	}

	for (int row = 0; row < maxHeight_; row++)
	{
		for (int col = 0; col < maxWidth_; col++)
		{
			GraphNode *node = g.mNodes[row * maxWidth_ + col];
			if (col > 0) // Not the left-most column
			{
				node->mAdjacent.emplace_back(g.mNodes[row * maxWidth_ + col - 1]); // Add the node to the left

			}
			if (col < maxWidth_ -1)
			{
				node->mAdjacent.emplace_back(g.mNodes[row * maxWidth_ + col + 1]);
			}
			if (row > 0) // Not first row
			{
				node->mAdjacent.emplace_back(g.mNodes[(row - 1) * maxWidth_ + col]); // Add the node above
				if (col > 0) // Not first row or left-most col
				{
					node->mAdjacent.emplace_back(g.mNodes[(row - 1) * maxWidth_ + col - 1]); // Add the node to the top left
				}
				if (col < maxWidth_ - 1)
				{
					node->mAdjacent.emplace_back(g.mNodes[(row - 1) * maxWidth_ + col + 1]); // Add the node to the top right

				}
			}
			if (row < maxHeight_ - 1) 
			{
				node->mAdjacent.emplace_back(g.mNodes[(row + 1) * maxWidth_ + col]);
				if (col > 0) // Not last row or left-most col
				{
					node->mAdjacent.emplace_back(g.mNodes[(row + 1) * maxWidth_ + col - 1]); // Add the node to the bottom left
				}
				if (col < maxWidth_ - 1)
				{
					node->mAdjacent.emplace_back(g.mNodes[(row + 1) * maxWidth_ + col + 1]); // Add the node to the bottom right
				}

			}
		}
	}
	std::cout << "Graph constructed" << std::endl;


}

void World::SetStartNode(int index)
{
	start_ = g.mNodes[index];
}

void World::SetGoalNode(int index)
{
	goal_ = g.mNodes[index];

}

void World::FindPath()
{
	GraphNode *start = start_;
	GraphNode *goal = goal_;
	NodeToParentMap map;
	std::queue<int> mNodeVisited;
	bool found = BFS(g, start, goal, map, mNodeVisited);

	// Current node is the goal, trace back using the parent table to find the path
	const GraphNode *current = goal;
	std::cout << current->id << std::endl;
	tiles_[current->id].color.r = 0;

	while (!map.empty())
	{
		
		//std::unordered_map<GraphNode *, GraphNode *>::const_iterator got = map.find(current);
		std::cout << map.find(current)->second->id << std::endl;
		current = map.find(current)->second;
		//while (!mNodeVisited.empty())
		//{
		//	tiles_[mNodeVisited.front()].color.g = 0;
		//	mNodeVisited.pop();
		//	Render();
		//}

		tiles_[current->id].color.r = 0;
		Render();
		if (current == start)
		{
			break;
		}
	}
}

int World::GetNodeIndex(int x, int y)
{
	return maxWidth_ * y + x;
}

void World::Render()
{
	// Set draw color to black
	SDL_SetRenderDrawColor(
		mRenderer,
		0,		// R
		0,		// G 
		0,		// B
		0		// A
	);

	// Clear back buffer
	SDL_RenderClear(mRenderer);

	// Draw square frame
	for (int i = 0; i < 48 * 27; ++i)
	{
		// Draw square frame
		SDL_SetRenderDrawColor(mRenderer, 0, 0, 255, 255);

		// Draw squares
		SDL_Rect square{
			(i % 48) * length,	// Top left x
			(i / 48) * length,	// Top left y
			length,
			length
		};

		SDL_RenderFillRect(mRenderer, &square);
	}

	for (int i = 0; i < 48 * 27; ++i)
	{
		// Draw square fill
		int r = tiles_[i].color.r;
		int g = tiles_[i].color.g;
		int b = tiles_[i].color.b;

		SDL_SetRenderDrawColor(mRenderer, r, g, b, 255);

		// Draw squares
		SDL_Rect square{
			(i % 48) * length + thickness/2,	// Top left x
			(i / 48) * length + thickness/2,	// Top left y
			length - thickness,
			length - thickness
		};
		SDL_RenderFillRect(mRenderer, &square);
	}

	// Swap front buffer and back buffer
	SDL_RenderPresent(mRenderer);
}
