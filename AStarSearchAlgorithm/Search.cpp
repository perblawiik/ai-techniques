#include "stdafx.h"
#include <iostream>
#include <stdlib.h>
#include <time.h>

#include "AStarSearch.h"

// Takes a puzzle and rearrange the tiles in random directions N number of times
void scramblePuzzle(EightPuzzle& puzzle, const int num_iterations);

// Takes a puzzle and move a tile in specified direction
void movePuzzle(EightPuzzle& puzzle, const char move);

// Takes a puzzle and a solution path and prints the puzzle states for all steps
void printPuzzleSolution(EightPuzzle puzzle, const std::vector<char>& path);

int main()
{
	// Solved puzzle
	//size_t initial_state[9]{ 1, 2, 3, 4, 5, 6, 7, 8, 0 };
	
	// Easy
	//size_t initial_state[9]{ 4, 1, 3, 7, 2, 6, 0, 5, 8 };

	// Medium
	//size_t initial_state[9]{ 7, 2, 4, 5, 0, 6, 8, 3, 1 };

	// Hard
	size_t initial_state[9]{ 8, 6, 7, 2, 5, 4, 3, 0, 1 };

	// Initialize the eight puzzle with an initial state
	EightPuzzle puzzle{ initial_state };

	// Randomize the puzzle
	//scramblePuzzle(puzzle, 100);

	// The goal state is given by the wanted solution for the eight puzzle in a string format
	std::string goal_state = "123456780";
	// Scope for finding the solution using heuristics function h1
	{
		// Initialize the A*-search with the eight puzzle and goal state
		AStarSearch a_star{ puzzle, goal_state };

		// Solve puzzle and return the path optimal path
		auto path = a_star.findPuzzleSolution(1);

		std::cout << "Solution: " << std::endl;
		printPuzzleSolution(puzzle, path);
	}
	
	std::cout << "\n//////////////////////////////////////\n" << std::endl;

	// Scope for finding the solution using heuristics function h2
	{
		// Initialize the A*-search with the eight puzzle and goal state
		AStarSearch a_star{ puzzle, goal_state };

		// Solve puzzle and return the path optimal path
		auto path = a_star.findPuzzleSolution(2);

		std::cout << "Solution: " << std::endl;
		printPuzzleSolution(puzzle, path);
	}
	
	system("pause");
    return 0;
}

void scramblePuzzle(EightPuzzle& puzzle, const int num_iterations)
{
	/* initialize random seed: */
	srand(time(nullptr));

	// Scramble the puzzle
	for (int i{ 0 }; i < num_iterations; ++i) {
		int random_number{ rand() % 4 + 1 };
		if (random_number == 1)
			puzzle.moveLeft();
		else if (random_number == 2)
			puzzle.moveRight();
		else if (random_number == 3)
			puzzle.moveUp();
		else
			puzzle.moveDown();
	}
}

void movePuzzle(EightPuzzle& puzzle, const char move)
{
	if (move == 'D')
		puzzle.moveDown();
	else if (move == 'U')
		puzzle.moveUp();
	else if (move == 'L')
		puzzle.moveLeft();
	else
		puzzle.moveRight();
}

void printPuzzleSolution(EightPuzzle puzzle, const std::vector<char>& path)
{
	std::cout << "\nInitial state:" << std::endl;
	puzzle.print();
	for (char move : path) {
		movePuzzle(puzzle, move);
		std::cout << "\nMove " << move << ":" << std::endl;
		puzzle.print();
	}
}