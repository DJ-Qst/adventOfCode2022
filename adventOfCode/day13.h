#pragma once
#include <string>
#include <vector>

class day13
{
public:
	day13(std::string fileName);

private:
	// Class variables and types
	std::vector<std::vector<std::string>> pairsList;
	enum rightOrder;
	
	// Parts 1 and 2
	int part1();
	int part2();

	// Class methods
	std::vector<std::string> split(std::string fullString, std::string splitter);
	std::vector<std::string> splitItem(std::string item);
	rightOrder checkElements(std::string first, std::string second);
};

