#include "stdafx.h"
#include "EightPuzzle.h"

#include <algorithm>

EightPuzzle::EightPuzzle(const size_t initial_state[]) 
{
	for (size_t i{ 0 }; i < 9; ++i) {
		matrix[i] = initial_state[i];
		// Save the matrix coordinates of the empty space (represented as a zero)
		if (initial_state[i] == 0) {
			empty_space.row = i / 3;
			empty_space.column = (i % 3);
		}
	}
};

EightPuzzle::EightPuzzle(const EightPuzzle& other) 
	: EightPuzzle(other.matrix)
{ 
	history = other.history;
}

void EightPuzzle::moveUp() {
	if (empty_space.row > 0) {
		std::swap(matrix[empty_space.row * 3 + empty_space.column], matrix[(empty_space.row - 1) * 3 + empty_space.column]);
		empty_space.row -= 1;
		// Save move in the history stack
		history.push_back('U');
	}
}

void EightPuzzle::moveDown() {
	if (empty_space.row < 2) {
		std::swap(matrix[empty_space.row * 3 + empty_space.column], matrix[(empty_space.row + 1) * 3 + empty_space.column]);
		empty_space.row += 1;
		// Save move in the history stack
		history.push_back('D');
	}
}

void EightPuzzle::moveLeft() {
	if (empty_space.column > 0) {
		std::swap(matrix[empty_space.row * 3 + empty_space.column], matrix[empty_space.row * 3 + (empty_space.column - 1)]);
		empty_space.column -= 1;
		// Save move in the history stack
		history.push_back('L');
	}
}

void EightPuzzle::moveRight() {
	if (empty_space.column < 2) {
		std::swap(matrix[empty_space.row * 3 + empty_space.column], matrix[empty_space.row * 3 + (empty_space.column + 1)]);
		empty_space.column += 1;
		// Save move in the history stack
		history.push_back('R');
	}
}

std::string EightPuzzle::state() const 
{
	std::string result;
	for (size_t element : matrix) {
		result += std::to_string(element);
	}
	return result;
}

void EightPuzzle::print() const 
{
	std::cout << matrix[0] << "  " << matrix[1] << "  " << matrix[2] << std::endl;
	std::cout << matrix[3] << "  " << matrix[4] << "  " << matrix[5] << std::endl;
	std::cout << matrix[6] << "  " << matrix[7] << "  " << matrix[8] << std::endl;
}