#pragma once
#include <vector>
#include <string>
#include <map>
#include <set>


class day14
{
public:
	day14(std::string fileName);
private:
	// The map and the cave's lowest y-coords
	std::map<int, std::set<int>> blockedLocs;
	int deepestY;

	// Function to split a string given a splitting substring
	std::vector<std::string> split(std::string fullString, std::string splitter);

	// Parts 1 and 2
	int part1();
	int part2();
};

