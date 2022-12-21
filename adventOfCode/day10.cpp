#include "day10.h"
#include "daySetup.h"
#include <string>
#include <vector>

// Function definition
char pixelAdd(int cycleCount, int xReg);

day10::day10(std::string fileName) {
	daySetup setup(fileName);
	commands = setup.getLineStrings();

	std::cout << "The sum of the signal strengths is: " << part1() << std::endl;
	part2();  // No print statement is needed because it draws a board
}

int day10::part1() {
	int xReg = 1;
	int cycleCount = 0;
	int sumStrength = 0;
	std::vector<int> testCycles = { 20, 60, 100, 140, 180, 220 };  // Spots where we want to test the device
	for (std::string command: commands) {
		if (command == "noop") {
			cycleCount++;
			// If the current cycle is equal to one of the test cycles
			if (std::find(testCycles.begin(), testCycles.end(), cycleCount) != testCycles.end()) {
				sumStrength += (cycleCount * xReg);
			}
		}
		else if (command[0] == 'a') {
			cycleCount++;
			// If the current cycle is equal to one of the test cycles
			if (std::find(testCycles.begin(), testCycles.end(), cycleCount) != testCycles.end()) {
				sumStrength += (cycleCount * xReg);
			}
			cycleCount++;
			// If the current cycle is equal to one of the test cycles
			if (std::find(testCycles.begin(), testCycles.end(), cycleCount) != testCycles.end()) {
				sumStrength += (cycleCount * xReg);
			}
			xReg += stoi(command.substr(5));
		}
	}

	return sumStrength;
}

void day10::part2() {
	int xReg = 1;
	int cycleCount = -1;  // Starts at -1 so when I add the first count, it goes to 0
	int rowNum = 0;
	std::vector<std::vector<char>> screen = { {}, {}, {}, {}, {}, {} };

	// For each command
	for (std::string command : commands) {
		if (command == "noop") {
			// This block is seen several times and it goes as follows:
			// 1. Add 1 to the cycle count
			// 2. See if its time to move to the next row of the screen
			// 3. Add the correct pixel using the function
			cycleCount++;
			if (cycleCount == 40) {
				// Cycle count is basically an index, so go from 0 to 39
				rowNum += 1;
				cycleCount = 0;
			}
			screen[rowNum].push_back(pixelAdd(cycleCount, xReg));

		}
		// If it's addx, the first character will always be a, so this removes need to pull substring
		else if (command[0] == 'a') {
			// Cycle count block, see noop command for details
			cycleCount++;
			if (cycleCount == 40) {
				rowNum += 1;
				cycleCount = 0;
			}
			screen[rowNum].push_back(pixelAdd(cycleCount, xReg));

			cycleCount++;
			if (cycleCount == 40) {
				rowNum += 1;
				cycleCount = 0;
			}
			screen[rowNum].push_back(pixelAdd(cycleCount, xReg));

			// Pull the number from the command, convert it to an integer, add it to the x register
			xReg += stoi(command.substr(5));
		}
	}
	
	// Rendering the board
	for (int i = 0; i <= 5; i++) {
		for (int x = 0; x < screen[i].size(); x++) {
			std::cout << screen[i][x];
		}
		std::cout << "\n";
	}
}

char pixelAdd(int cycleCount, int xReg) {
	// Sprite ranges to +/- 1 of the x register
	for (int i = xReg - 1; i <= xReg + 1; i++) {
		if (cycleCount == i) {
			return '#';
		}
	} 

	// If it wasn't found in the loop, the pixel is not lit
	return '.';
}
