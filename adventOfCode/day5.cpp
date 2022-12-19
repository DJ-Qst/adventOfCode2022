#include "day5.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

day5::day5(std::string fileName)
{
	std::fstream file;
	std::string line;
	int columnNum;
	std::string colElement;

	// Adding all 9 columns to the map
	for (int i=1; i <= 9; i++) {
		columns[i] = {};
	}	

	// Reading data from file
	file.open(fileName, std::ios::in);
	if (file.is_open()) {
		// This loop just takes and adds all of the starting positions to their columns
		while (getline(file, line)) {
			// If the second character is '1', we have reached the end of the initial crates
			if (line[1] == '1') {
				getline(file, line); // get the blank line between board and instructions
				break;  // Break out of setup loop
			}
			else {
				columnNum = 1;
				// Add 4 to take care of blank space between elements
				for (int i = 1; i < line.size(); i += 4) {
					colElement = line[i];  // 3 is the length of the substring, not end index
					// If the column is not empty append it to the list
					if (colElement != " ") {
						// By this method, the first index, "0", is the very top element,
						// aka the one that should be removed first
						columns[columnNum].push_back(colElement);
					}
					columnNum += 1;
				}
			}
		}

		// This reverses the order of each of the columns, so that the last element is the top
		// Allows .pop and .push to access the top element
		for (int i = 1; i <= 9; i++) {
			std::reverse(columns[i].begin(), columns[i].end());
		}

		// This loop adds all of the instructions to a list
		while (getline(file, line)) {
			// By this method, 0 index is the first command
			commands.push_back(line);
		}

		// After everything is done, close the file
		file.close();
	}

	// If given a bad file name
	else {
		std::cout << "ERROR: File did not open";
	}

	std::cout << "The message spelled by CrateMover 9000 is: " << part1() << "\n";
	std::cout << "The message spelled by CrateMover 9001 is: " << part2() << "\n";
}

std::string day5::part1() {
	// Copy of the initial columns for part 1
	std::map<int, std::vector<std::string>> pt1Columns = columns;

	// These values are for each command
	int moveAmount;  // How many crates to move
	int startCol;  // Where to pull crates from
	int endCol;  // Where to send crates to
	std::string moveItem;  // A temp variable to hold the crate in transit
	// This is the string that the final positions get added to
	std::string finalMessage;

	// For each of the commands 
	for (std::string command : commands) {
		// Pull information from the command
		// Find the first space and then get a substring to the next space, move amounts are sometimes double digits
		moveAmount = stoi(command.substr(command.find(" "), (command.find(" from") - command.find(" "))));
		startCol = stoi(command.substr((command.find(" from ") + strlen(" from ")), 1));
		endCol = stoi(command.substr((command.find(" to ") + strlen(" to ")), 1));

		for (int i = 1; i <= moveAmount; i++) {
			// Take the item from the start column
			moveItem = pt1Columns[startCol].back();
			pt1Columns[startCol].pop_back();

			// Add it to the ending column
			pt1Columns[endCol].push_back(moveItem);
		}
		
	}
	
	// Add each column top to the final message
	for (int i = 1; i <= 9; i++) {
		finalMessage += pt1Columns[i].back();
	}
	return finalMessage;
}

std::string day5::part2() {
	// Copy of the initial columns for part 2
	std::map<int, std::vector<std::string>> pt2Columns = columns;

	// These values are for each command
	int moveAmount;  // How many crates to move
	int startCol;  // Where to pull crates from
	int endCol;  // Where to send crates to
	int tempIndex; // Index of the moveItem in the vector
	std::string moveItem;  // A temp variable to hold the crate in transit

	// This is the string that the final positions get added to
	std::string finalMessage;

	for (std::string command : commands) {
		// Pull information from the command
		// Find the first space and then get a substring to the next space, move amounts are sometimes double digits
		moveAmount = stoi(command.substr(command.find(" "), (command.find(" from") - command.find(" "))));
		startCol = stoi(command.substr((command.find(" from ") + strlen(" from ")), 1));
		endCol = stoi(command.substr((command.find(" to ") + strlen(" to ")), 1));

		for (int i = moveAmount; i > 0; i--) {
			tempIndex = pt2Columns[startCol].size() - i;
			moveItem = pt2Columns[startCol][tempIndex];
			
			// Erase is weird because it has to be passed an iterator, not just an integer
			pt2Columns[startCol].erase(std::next(pt2Columns[startCol].begin(), tempIndex));

			pt2Columns[endCol].push_back(moveItem);
		}
	}

	// Add each column top to the final message
	for (int i = 1; i <= 9; i++) {
		finalMessage += pt2Columns[i].back();
	}

	return finalMessage;
}