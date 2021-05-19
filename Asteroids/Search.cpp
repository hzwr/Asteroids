#include "Search.h"


bool BFS(const Graph &graph, const GraphNode *start, const GraphNode *goal, NodeToParentMap &parent, std::queue<int> &nodeVisited)
{
	// Level = { startingNode: 0 }
	std::unordered_map<const GraphNode *, int> level = { {start, 0} };
	parent = { {start, nullptr} };
	int i = 1;  
	// Frontier contains all the nodes reachable in i-1 move(s)
	std::vector<const GraphNode *> frontier = { start };
	while (frontier.size() != 0)
	{
		std::vector<const GraphNode *> next; // Nodes reachable in i move(s)

		for (const GraphNode *node : frontier)
		{
			if (node == goal)
			{
				return true;
			}
			// Find all the neighbors
			for (const GraphNode *neighbor : node->mAdjacent)
			{


				if (level.find(neighbor) == level.end()) // If not in the table
				{
					nodeVisited.push(neighbor->id);
					level.insert({ neighbor, i });
					parent.insert({ neighbor, node }); // node, parent
					next.push_back(neighbor);
				}
			}
		}
		frontier = next;
		i += 1;
	}
	return false;
}

//bool BFS(const Graph &graph, const GraphNode *start, const GraphNode *goal, NodeToParentMap &outMap)
//{
//	// Whether we found a path
//	bool pathFound = false;
//	// Nodes to consider
//	std::queue<const GraphNode *> q;
//	// Enqueue the first node
//	q.emplace(start);
//
//	while (!q.empty())
//	{
//		// Dequeue a node
//		const GraphNode *current = q.front();
//		q.pop();
//		if (current == goal)
//		{
//			pathFound = true;
//			break;
//		}
//
//		// Enqueue adjacent nodes that aren't already in the queue
//		for (const GraphNode *node : current->mAdjacent)
//		{
//			// If the parent is null, it hasn't been enqueued
//			// (except for the start node)
//			const GraphNode *parent = outMap[node];
//			if (parent == nullptr && node != start)
//			{
//				// Enqueue this node, setting its parent
//				outMap[node] = current;
//				q.emplace(node);
//			}
//		}
//	}
//
//	return pathFound;
//}

void testBFS()
{
	Graph g;
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			GraphNode *node = new GraphNode;
			node->id = i * 5 + j;
			g.mNodes.emplace_back(node);
		}
	}

	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			GraphNode *node = g.mNodes[i * 5 + j];
			if (i > 0)
			{
				node->mAdjacent.emplace_back(g.mNodes[(i - 1) * 5 + j]);
			}
			if (i < 4)
			{
				node->mAdjacent.emplace_back(g.mNodes[(i + 1) * 5 + j]);
			}
			if (j > 0)
			{
				node->mAdjacent.emplace_back(g.mNodes[i * 5 + j - 1]);
			}
			if (j < 4)
			{
				node->mAdjacent.emplace_back(g.mNodes[i * 5 + j + 1]);
			}
		}
	}

	NodeToParentMap map;
	//bool found = BFS(g, g.mNodes[0], g.mNodes[9], map);
	
	// Current node is the goal, trace back using the parent table to find the path
	const GraphNode *current = g.mNodes[9];
	while (!map.empty())
	{
		//std::unordered_map<GraphNode *, GraphNode *>::const_iterator got = map.find(current);
		std::cout << map.find(current)->second->id << std::endl;
		current = map.find(current)->second;

		if (current == g.mNodes[0])
		{
			break;
		}
	}
	//std::cout << found << '\n';
}

void FindPath()
{
	// Construct the graph
	
	// Run BFS
}