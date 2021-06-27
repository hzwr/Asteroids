#include "Search.h"
#include "SDL/SDL.h"
#include "Tile.h"

class World
{
public:
	World(int maxWidth, int maxHeight, SDL_Renderer *renderer);
	~World();
	void ConstructGraph();
	void SetStartNode(int index);
	void SetGoalNode(int index);
	void FindPath();
	int GetNodeIndex(int x, int y);

	SDL_Renderer *mRenderer;


private:
	void Render();

	int maxHeight_;
	int maxWidth_;
	Graph g;

	GraphNode *start_;
	GraphNode *goal_;

	// Render
	Tile::Tile *tiles_;
	const int length = 30;
	const int thickness = 5;

};