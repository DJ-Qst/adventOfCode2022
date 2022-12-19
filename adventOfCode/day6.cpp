#include "day6.h"
#include <iostream>
#include <fstream>
#include <string>

day6::day6(std::string fileName){
	std::fstream file;

	file.open(fileName);
	if (file.is_open()) {
		getline(file, dataBuffer);
		file.close();
	}
	else {
		std::cout << "Error: File did not open";
	}

	std::cout << "The first start of packet is at: " << part1() << "\n";
	std::cout << "The first start of message is at: " << part2() << "\n";
}

int day6::part1() {
	std::string fourSet;
	bool duplicates = false;

	// Setting up the initial set of 4 characters
	for (int i = 0; i <= 3; i++) {
		fourSet += dataBuffer[i];
	}

	for (int i = 4; i < dataBuffer.size(); i++) {
		// Add the new character to the buffer and remove the oldes
		fourSet += dataBuffer[i];
		fourSet.erase(fourSet.begin());

		for (char letter : fourSet) {
			// Take each character and count its number of occurances
			// If the number of occurances is greater than 1, there are duplicates and the search needs to continue
			if ((std::count(fourSet.begin(), fourSet.end(), letter)) > 1) {
				duplicates = true;
				break;
			}
			else {
				duplicates = false;
			}
		}
		
		// If there are no duplicates the start has been found, indexes start at 0 so add 1
		if (!duplicates) {
			return i+1;
		}
	}
}

int day6::part2() {
	std::string fourSet;
	bool duplicates = false;

	// Setting up the initial set of 14 characters
	for (int i = 0; i <= 13; i++) {
		fourSet += dataBuffer[i];
	}

	for (int i = 14; i < dataBuffer.size(); i++) {
		// Add the new character to the buffer and remove the oldes
		fourSet += dataBuffer[i];
		fourSet.erase(fourSet.begin());

		for (char letter : fourSet) {
			// Take each character and count its number of occurances
			// If the number of occurances is greater than 1, there are duplicates and the search needs to continue
			if ((std::count(fourSet.begin(), fourSet.end(), letter)) > 1) {
				duplicates = true;
				break;
			}
			else {
				duplicates = false;
			}
		}

		// If there are no duplicates the start has been found, indexes start at 0 so add 1
		if (!duplicates) {
			return i + 1;
		}
	}
}
