#include "day9.h"
#include "daySetup.h"
#include <string>
#include <utility>

day9::day9(std::string fileName) {
	daySetup setup(fileName);
	steps = setup.getLineStrings();

	std::cout << "The number of unique positions visited is " << part1() << " positions.\n";
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
