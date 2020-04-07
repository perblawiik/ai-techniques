#pragma once
#include "EightPuzzle.h"
#include <unordered_set>
#include <set>

class AStarSearch
{
public:
	AStarSearch(const EightPuzzle& puzzle, const std::string& goal_state);
	~AStarSearch();

	// Search for the shortest path for solving the puzzle and return the path
	std::vector<std::string> findPuzzleSolution(const int heuristicsFunction);

	class Node {
	public:
		Node(const size_t heuristics, const size_t step, const EightPuzzle& puzzle)
			: evaluation{ heuristics + step }, step_count{ step }, puzzle{ puzzle } 
		{ };
		bool operator<(const Node &foo) const { return evaluation < foo.evaluation; }

		size_t evaluation;
		size_t step_count;
		EightPuzzle puzzle;
	};

private:
	int heuristicsFunction;
	std::string goal_state;
	std::unordered_set<std::string> closed_list;
	std::multiset<Node> open_list;

	// Computes heuristics to determine how close the current state is to the goal state (solution)
	size_t heuristics(const EightPuzzle& puzzle);
	// Computes and returns the heuristics based on number of displaced tiles
	size_t h1(const EightPuzzle& puzzle);
	// Computes and returns the heuristics based on the summed Manhattan distances between all tiles and their goal states
	size_t h2(const EightPuzzle& puzzle);

	// Try rearrange the puzzle in all possible ways to create children nodes
	void rearrangePuzzle(std::multiset<Node>::iterator it);

	// Add a puzzle node with its evaluation cost to the open list, given that the state does not exist in the closed list
	void addNodeToList(const EightPuzzle& puzzle, const size_t step_count);
};

