#include "day14.h"
#include "daySetup.h"
#include <vector>
#include <queue>

day14::day14(std::string fileName) {
	// Pull the lines from the file
	daySetup setup(fileName);
	std::vector<std::string> graphCommands = setup.getLineStrings();
	
	// Set up the blocked locations
	for (std::string line : graphCommands) {
		std::vector<std::string> points = split(line, " -> "); // Split it on the arrow to only have points
		std::queue<std::pair<int, int>> blockedLine; // The start and stop for where we're blocking with rocks
		char changeOn;
		int direction;

		for (std::string coord : points) {
			// Get the coordinate nums, turn them to integers, make them a pair, and push it to the blocked line
			std::vector<std::string> coordNums = split(coord, ",");
			blockedLine.push(std::make_pair(stoi(coordNums[0]), stoi(coordNums[1])));
			
			// Check for deepest y
			if (stoi(coordNums[1]) > deepestY) deepestY = stoi(coordNums[1]);

			if (blockedLine.size() == 2) {
				changeOn = (blockedLine.front().first == blockedLine.back().first) ? 'y' : 'x';
				if (changeOn == 'y') {
					// If the goal is greater than the start, we need to add one each time, otherwise its a subtract
					direction = (blockedLine.front().second < blockedLine.back().second) ? 1 : -1;
					for (int y = blockedLine.front().second; y != (blockedLine.back().second + direction); y += direction) {
						blockedLocs[blockedLine.front().first].insert(y); // Insert the y value at the constant x in the map
					}
				}

				else if (changeOn == 'x') {
					direction = (blockedLine.front().first < blockedLine.back().first) ? 1 : -1;
					//std::cout << blockedLine.front().first << " " << blockedLine.back().first << std::endl;
					for (int x = blockedLine.front().first; x != (blockedLine.back().first + direction); x += direction) {
						//std::cout << x << " ";
						blockedLocs[x].insert(blockedLine.front().second);
					}
				}
				//std::cout << "\n";
				blockedLine.pop();
			}
		}
	}	
	std::cout << "The number of grains of sand that drop before entering the void is " << part1() << " grains.\n";
	std::cout << "The number of grains of sand that drop before blocking the source is " << part2() << " grains.\n";
}

int day14::part1() {
	std::map<int, std::set<int>> blockedMap(blockedLocs);
	std::pair<int, int> grainLoc;
	int numGrains = 0;
	bool inVoid = false;
	while (!inVoid) {
		numGrains += 1;
		bool stuck = false;
		grainLoc = std::make_pair(500, 0);
		while (!stuck) {
			// Go a level deeper and see if that's too deep
			grainLoc.second += 1;
			if (grainLoc.second > deepestY + 5) {
				inVoid = true;
				break;
			}

			// Check if the down, left, and right location is blocked, if any are valid it jumps to the next loop
			// If statement trys to find the y in the x list, but if it doesent it returns the .end()
			if (blockedMap[grainLoc.first].find(grainLoc.second) == blockedMap[grainLoc.first].end()) continue;
			grainLoc.first -= 1; // Go 1 left
			if (blockedMap[grainLoc.first].find(grainLoc.second) == blockedMap[grainLoc.first].end()) continue;
			grainLoc.first += 2; // Get back to straight and then go 1 right
			if (blockedMap[grainLoc.first].find(grainLoc.second) == blockedMap[grainLoc.first].end()) continue;
			grainLoc.first -= 1; // Go back to center

			// If we reach here, the sand cannot go down again, so subtract 1 from the y and thats resting place
			grainLoc.second -= 1;
			blockedMap[grainLoc.first].insert(grainLoc.second);
			stuck = true;
		}
	}

	return (numGrains - 1);
}

int day14::part2() {
	std::map<int, std::set<int>> blockedMap(blockedLocs);
	std::pair<int, int> grainLoc;
	int numGrains = 0;
	
	// Adding the floor of the cave
	for (int i = 455; i <= 538; i++) {
		blockedMap[i].insert(deepestY + 2);
	}

	// While the source is not blocked
	while (blockedMap[500].find(0) == blockedMap[500].end()) {
		// Add 1 to the number of grains, set the "stuck" flag to false
		numGrains += 1;
		bool stuck = false;
		grainLoc = std::make_pair(500, 0);
		while (!stuck) {
			// Go a level deeper and see if that's too deep
			grainLoc.second += 1;
			// Check if the down, left, and right location is blocked, if any are valid it jumps to the next loop
			// If statement trys to find the y in the x list, but if it doesent it returns the .end()
			if (blockedMap[grainLoc.first].find(grainLoc.second) == blockedMap[grainLoc.first].end()) continue;
			grainLoc.first -= 1; // Go 1 left
			if (blockedMap[grainLoc.first].find(grainLoc.second) == blockedMap[grainLoc.first].end()) continue;
			grainLoc.first += 2; // Get back to straight and then go 1 right
			if (blockedMap[grainLoc.first].find(grainLoc.second) == blockedMap[grainLoc.first].end()) continue;
			grainLoc.first -= 1; // Go back to center

			// If we reach here, the sand cannot go down again, so subtract 1 from the y and thats resting place
			grainLoc.second -= 1;
			blockedMap[grainLoc.first].insert(grainLoc.second);
			stuck = true;
		}
	}

	return numGrains;
}

std::vector<std::string> day14::split(std::string fullString, std::string splitter) {
	std::vector<std::string> splitString;
	int startPos = 0;
	int occurrance = fullString.find(splitter, startPos);
	while (occurrance >= 0) {
		splitString.push_back(fullString.substr(startPos, (occurrance - startPos)));
		startPos = occurrance + splitter.size();
		occurrance = fullString.find(splitter, startPos);
	}
	splitString.push_back(fullString.substr(startPos)); // Adding anything remaining

	return splitString;
}