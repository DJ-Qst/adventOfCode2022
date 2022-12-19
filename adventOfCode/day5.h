#pragma once
#include <iostream>
#include <map>
#include <vector>

class day5
{
public:
	day5(std::string fileName);
private:
	std::map<int, std::vector<std::string>> columns;
	std::vector<std::string> commands;

	std::string part1();
	std::string part2();
};

