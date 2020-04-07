#pragma once

#include <iostream>
#include <string>
#include <vector>

struct EightPuzzle {
	struct MatrixPosition {
		size_t row;
		size_t column;
		MatrixPosition(const size_t r = 0, const size_t c = 0) : row{ r }, column{ c } {};
	};

	size_t matrix[9];
	MatrixPosition empty_space;
	std::vector<std::string> history;

	// Constructor
	EightPuzzle(const size_t initial_state[]);

	// Copy constructor
	EightPuzzle(const EightPuzzle& other);

	// Functions for moving swapping the empty space with a number
	void moveUp();
	void moveDown();
	void moveLeft();
	void moveRight();

	// Returns the current state as a string
	std::string state() const;

	// Prints out the puzzle in matrix format
	void print() const;
};