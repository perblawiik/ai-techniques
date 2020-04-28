#include "stdafx.h"
#include "AStarSearch.h"


AStarSearch::AStarSearch(const EightPuzzle& puzzle, const std::string& goal_state)
	: goal_state{ goal_state }, heuristicsFunction{ 2 }
{
	std::cout << "Initial state: " << std::endl;
	puzzle.print();

	// Add initial state to both open list and closed list
	open_list.insert(Node{ heuristics(puzzle), (size_t)0, puzzle });
	// Add initial state to the closed list to avoid infinite loops
	closed_list.insert(puzzle.state());
}

AStarSearch::~AStarSearch()
{ }

std::vector<char> AStarSearch::findPuzzleSolution(const int heuristics = 2)
{
	heuristicsFunction = heuristics;
	std::cout << "\nSolving puzzle with heuristics function h" << heuristics << "..\n" << std::endl;

	// An iterator to the first node in the open list queue
	std::multiset<Node>::iterator current_node;

	// Set a limit in case the puzzle is unsolvable
	const size_t MAX_ITERATIONS{ 500000 };
	size_t n{ 0 };
	while (n < MAX_ITERATIONS) {
		// Get iterator to first node in the queue
		current_node = open_list.begin();

		// Compare current state to goal state
		if (isGoalState(current_node->puzzle.state())) {
			std::cout << "Goal state found!" << std::endl;
			std::cout << "\nNumber of steps: " << current_node->step_count << std::endl;
			std::cout << "Number of iterations: " << n << std::endl;
			std::cout << "Closed list size: " << closed_list.size() << std::endl;
			std::cout << "Open list size: " << open_list.size() << std::endl;
			std::cout << "Path: ";
			for (auto dir : current_node->puzzle.history) {
				std::cout << dir << " ";
			}
			std::cout << std::endl << std::endl;

			break;
		}

		// Try all possible rearrangements
		rearrangePuzzle(current_node);

		// Remove node from open list
		open_list.erase(current_node);

		n++;
	}

	if (n == MAX_ITERATIONS)
		std::cout << "Goal state was not found!"<< std::endl;
	
	// Return the path to the solution
	return current_node->puzzle.history;
}

bool AStarSearch::isGoalState(const std::string& state)
{
	return goal_state.compare(state) == 0;
}

size_t AStarSearch::heuristics(const EightPuzzle& puzzle)
{
	if (heuristicsFunction == 2)
		return h2(puzzle);
	else
		return h1(puzzle);
}

size_t AStarSearch::h1(const EightPuzzle& puzzle)
{
	size_t num_displacements{ 0 };
	for (size_t i{ 0 }; i < 9; ++i) {
		// Don't count a displacement for the empty space
		if (puzzle.matrix[i] != 0 && puzzle.matrix[i] != i+1) {
			num_displacements++;
		}
	}
	return num_displacements;
}

size_t AStarSearch::h2(const EightPuzzle& puzzle)
{
	size_t distance_sum{ 0 };
	for (int i{ 0 }; i < 9; ++i) {
		if (puzzle.matrix[i] != 0) {
			// Current position
			int c_row{ i / 3 }, c_col{ i % 3 };
			// Goal position
			int g_row{ ((int)puzzle.matrix[i] - 1) / 3 }, g_col{ ((int)puzzle.matrix[i] - 1) % 3 };

			// Calculate Manhattan distance between current position and goal position
			distance_sum += abs(c_row - g_row) + abs(c_col - g_col);
		}
	}
	return distance_sum;
}

void AStarSearch::rearrangePuzzle(std::multiset<Node>::iterator it)
{
	// Add puzzle state to the closed list to avoid infinite loops
	closed_list.insert(it->puzzle.state());

	// Get step count from current node and increment it by one
	size_t step_count = it->step_count + 1;

	// Swap empty space with upper piece
	if (it->puzzle.empty_space.row > 0) {
		EightPuzzle puzzle{ it->puzzle };
		puzzle.moveUp();

		addNodeToList(puzzle, step_count);
	}
	// Swap empty space with lower piece
	if (it->puzzle.empty_space.row < 2) {
		EightPuzzle puzzle{ it->puzzle };
		puzzle.moveDown();

		addNodeToList(puzzle, step_count);
		
	}
	// Swap empty space with piece to the left
	if (it->puzzle.empty_space.column > 0) {
		EightPuzzle puzzle{ it->puzzle };
		puzzle.moveLeft();

		addNodeToList(puzzle, step_count);
	}
	// Swap empty space with piece to the right
	if (it->puzzle.empty_space.column < 2) {
		EightPuzzle puzzle{ it->puzzle };
		puzzle.moveRight();

		addNodeToList(puzzle, step_count);
	}
}

void AStarSearch::addNodeToList(const EightPuzzle& puzzle, const size_t step_count)
{
	// Make sure that this puzzle state is not included in the closed list
	if (closed_list.find(puzzle.state()) == closed_list.end()) {
		// Add node to the open list
		open_list.insert(Node{ heuristics(puzzle), step_count, puzzle });
	}
}
