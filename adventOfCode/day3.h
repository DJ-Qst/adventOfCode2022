#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <map>

class day3
{
public:
	// Class constructor and "main" function for the day
	day3(std::string fileName);

private:
	std::vector<std::string> dayLines;  // Vector to hold all of the lines from the text file
	std::map<char, int> letterConversion;  // Map for converting a character to a priority number
	int part1();  // Part 1, finding the unsorted items
	int part2();  // Part 2, finding the badges of the elf groups
};

