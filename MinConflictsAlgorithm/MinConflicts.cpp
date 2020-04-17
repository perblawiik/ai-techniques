// MinConflicts.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <iomanip>

#include <stdlib.h> // srand, rand 
#include <time.h> // time

#include <vector>
#include <string>
#include <tuple>

void minConflicts(std::vector<std::string>& csp, const size_t max_iterations);
size_t totalConflicts(const std::vector<std::string>& csp);
size_t findConflicts(const std::vector<std::string>& csp, const size_t row_number);
size_t findMinConflictsIndex(std::vector<std::string>& csp, const size_t random_index, const size_t total_conflicts);

size_t randomVariable(std::vector<std::string>& csp);

void print(std::vector<std::string>& csp);

// Global constants
const size_t NUM_COLUMNS{ 3 };

int main()
{
	// Schedule to solve
	std::vector<std::string> schedule{
	//	TP51	 SP34	  K3
		"     ", "     ", "MT101", // 09.00
		"MT102", "MT103", "MT104", // 10.00
		"MT105", "MT106", "MT107", // 11.00
		"MT201", "MT202", "MT203", // 12.00
		"MT204", "MT205", "MT206", // 13.00
		"MT301", "MT302", "MT303", // 14.00
		"MT304", "MT401", "MT402", // 15.00
		"MT403", "MT501", "MT502"  // 16.00
	};
	print(schedule);

	size_t MAX_STEPS{ 1000 };
	minConflicts(schedule, MAX_STEPS);
}

void minConflicts(std::vector<std::string>& csp, const size_t max_steps)
{
	// Initialize random seed
	srand(time(nullptr));

	// Iterate a given number of steps to avoid infinity loop
	for (size_t steps{ 0 }; steps < max_steps; steps++) {
		// Check total number of conflicts
		size_t num_conflicts{ totalConflicts(csp) };

		// If no conflicts were found, the problem is solved
		if (num_conflicts == 0) {
			std::cout << "\nSchedule solved after " << steps << " steps:\n" << std::endl;
			print(csp);
			return;
		}

		// Draw a random conflicted variable
		size_t random_index{ randomVariable(csp) };

		// Check for minimum conflicts
		size_t min_conflicts_index{ findMinConflictsIndex(csp, random_index, num_conflicts) };
		
		// Set the random variable to the minimum conflicts position
		std::swap(csp[random_index], csp[min_conflicts_index]);
	}

	std::cout << "\nFailed to solve schedule" << std::endl;
	print(csp);
}

size_t totalConflicts(const std::vector<std::string>& csp)
{
	size_t num_conflicts{ 0 };
	size_t num_rows{ csp.size() / NUM_COLUMNS };

	// Sum all conflicts found on each row
	for (size_t row{ 0 }; row < num_rows; row++) {
		num_conflicts += findConflicts(csp, row);
	}

	return num_conflicts;
}

size_t findConflicts(const std::vector<std::string>& csp, const size_t row_number)
{
	size_t num_conflicts{ 0 };
	auto id_1{ (csp[row_number * NUM_COLUMNS])[2] };
	auto id_2{ (csp[row_number * NUM_COLUMNS + 1])[2] };
	auto id_3{ (csp[row_number * NUM_COLUMNS + 2])[2] };

	// Special case for id 5 and blank space
	if (id_1 != '5' && id_1 != ' ') {
		if (id_1 == id_2)
			num_conflicts++;
		if (id_1 == id_3)
			num_conflicts++;
	}
	if (id_2 != '5' && id_2 != ' ' && id_2 == id_3) {
		num_conflicts++;
	}

	return num_conflicts;
}

size_t findMinConflictsIndex(std::vector<std::string>& csp, const size_t random_index, const size_t total_conflicts)
{
	// Set minimum conflicts to the total number of conflicts as default
	size_t min_conflicts{ total_conflicts };
	// Set minimum conflicts index to the original index as default
	size_t min_conflicts_index{ random_index };

	// Iterate through all possible moves for the random variable
	for (size_t i{ 0 }; i < csp.size(); i++) {
		if (i != random_index) {
			// Swap to a potential position
			std::swap(csp[random_index], csp[i]);

			// Check number of conflicts
			size_t current_conflicts{ totalConflicts(csp) };

			// If current conflicts are lower than minimum, save index as the new minimum conflicts
			if (current_conflicts < min_conflicts) {
				min_conflicts = current_conflicts;
				min_conflicts_index = i;
			}

			// Swap back
			std::swap(csp[random_index], csp[i]);
		}
	}

	// Return the index that gave the minimum number of conflicts
	return min_conflicts_index;
}

size_t randomVariable(std::vector<std::string>& csp)
{
	size_t index{ 0 }, num_conflicts{ 0 };
	do {
		// Index in the range 0 to size of vector
		index = rand() % (csp.size() - 1);
		// Check for conflicts in the row of selected index
	} while (findConflicts(csp, index / NUM_COLUMNS) == 0);

	// Return random variable index with conflicts
	return index;
}

void print(std::vector<std::string>& csp)
{
	std::cout << "     TP51    SP34    K3" << std::endl;
	std::cout << "     ----    ----    ----" << std::endl;
	size_t num_rows{ csp.size() / NUM_COLUMNS };
	size_t time{ 9 };
	for (size_t row{ 0 }; row < num_rows; row++) {
		std::cout << std::setfill('0') << std::setw(2) << time++;
		std::cout << "   " << csp[row * NUM_COLUMNS]
			<< "   " << csp[row * NUM_COLUMNS + 1]
			<< "   " << csp[row * NUM_COLUMNS + 2] << std::endl;
	}
}