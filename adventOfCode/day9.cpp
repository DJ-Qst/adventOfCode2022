#include "day9.h"
#include "daySetup.h"
#include <string>
#include <utility>

day9::day9(std::string fileName) {
	daySetup setup(fileName);
	steps = setup.getLineStrings();

	std::cout << "The number of unique positions visited by the small rope's tail is " << part1() << " positions.\n";
	std::cout << "The number of unique positions visited by the big rope's tail is " << part2() << " positions.\n";
}

int day9::part1() {
	std::pair <int, int> headPos(0, 0);
	std::pair <int, int> tailPos(0, 0);
	std::vector<std::pair<int, int>> allTailPos;
	int xDiff, yDiff;
	
	for (std::string step : steps) {
		// Stay on this step for as many times as required
		for (int i = 1; i <= (stoi(step.substr(1))); i++) {
			// Update head position
			if (step[0] == 'U') {
				headPos.second += 1;
			}
			else if (step[0] == 'D') {
				headPos.second -= 1;
			}
			else if (step[0] == 'L') {
				headPos.first -= 1;
			}
			else if (step[0] == 'R') {
				headPos.first += 1;
			}

			// Check how far apart the head and tail is
			xDiff = headPos.first - tailPos.first;
			yDiff = headPos.second - tailPos.second;

			// Update tail x-coordinate
			if (xDiff > 1) {
				tailPos.first += 1;
			}
			else if (xDiff < -1) {
				tailPos.first -= 1;
			}

			// Updating tail y-coordinate
			if (yDiff > 1) {
				tailPos.second += 1;
			}
			else if (yDiff < -1) {
				tailPos.second -= 1;
			}

			// Extra changes in case of diagonals
			if ((abs(xDiff) > 1) && (yDiff == 1)) {
				tailPos.second += 1;
			}
			else if ((abs(xDiff) > 1) && (yDiff == -1)) {
				tailPos.second -= 1;
			}

			if ((abs(yDiff) > 1) && (xDiff == 1)) {
				tailPos.first += 1;
			}
			else if ((abs(yDiff) > 1) && (xDiff == -1)) {
				tailPos.first -= 1;
			}

			// Check if current tail position is unique
			if (std::find(allTailPos.begin(), allTailPos.end(), tailPos) == allTailPos.end()) {
				allTailPos.push_back(tailPos);
			}
		}
	}

	return allTailPos.size();
}

int day9::part2() {
	std::vector<std::pair<int, int>> rope; // Index 0 is head, 9 is tail
	std::vector<std::pair<int, int>> allTailPos;
	int followIndex;
	int xDiff, yDiff;
	
	// Setting up rope
	for (int i = 0; i < 10; i++) {
		rope.push_back(std::make_pair(0, 0));
	}
	
	for (std::string step : steps) {
		// Stay on this step for as many times as required
		for (int i = 1; i <= (stoi(step.substr(1))); i++) {
			// Update head position
			if (step[0] == 'U') {
				rope[0].second += 1;
			}
			else if (step[0] == 'D') {
				rope[0].second -= 1;
			}
			else if (step[0] == 'L') {
				rope[0].first -= 1;
			}
			else if (step[0] == 'R') {
				rope[0].first += 1;
			}
			
			// Update the position of each of the knots
			for (int leadIndex = 0; leadIndex < 9; leadIndex++) {
				followIndex = leadIndex + 1;
				// Check how far apart the lead and follow is
				xDiff = rope[leadIndex].first - rope[followIndex].first;
				yDiff = rope[leadIndex].second - rope[followIndex].second;

				// Update follow x-coordinate
				if (xDiff > 1) {
					rope[followIndex].first += 1;
				}
				else if (xDiff < -1) {
					rope[followIndex].first -= 1;
				}

				// Updating follow y-coordinate
				if (yDiff > 1) {
					rope[followIndex].second += 1;
				}
				else if (yDiff < -1) {
					rope[followIndex].second -= 1;
				}

				// Extra changes in follow for diagonals
				if ((abs(xDiff) > 1) && (yDiff == 1)) {
					rope[followIndex].second += 1;
				}
				else if ((abs(xDiff) > 1) && (yDiff == -1)) {
					rope[followIndex].second -= 1;
				}

				if ((abs(yDiff) > 1) && (xDiff == 1)) {
					rope[followIndex].first += 1;
				}
				else if ((abs(yDiff) > 1) && (xDiff == -1)) {
					rope[followIndex].first -= 1;
				}
			}

			// Check if current tail position is unique
			if (std::find(allTailPos.begin(), allTailPos.end(), rope[9]) == allTailPos.end()) {
				allTailPos.push_back(rope[9]);
			}
		}
	}
	return allTailPos.size();
}