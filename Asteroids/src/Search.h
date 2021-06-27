#pragma once
#include <vector>
#include <unordered_map>
#include <iostream>
#include <queue>
#include "Tile.h"

struct GraphNode
{
	int id;
	std::vector<GraphNode *> mAdjacent;
	bool isOnPath;
};

struct Graph
{
	std::vector<GraphNode *> mNodes;
};

struct WeightedEdge
{
	struct WeightedGraphNode *mFrom; //?
	struct WeightedGraphNode *mTo;
	float mWeight;
};

struct WeightedGraphNode
{
	std::vector<WeightedEdge *> mEdges;
};


struct WeightedGraph
{
	std::vector<WeightedGraphNode *> mNodes;
};

using NodeToParentMap =
std::unordered_map<const GraphNode *, const GraphNode *>;

bool BFS(const Graph &graph, const GraphNode *start, const GraphNode *goal, NodeToParentMap &parent, std::queue<int> &nodeVisited);
void testBFS();