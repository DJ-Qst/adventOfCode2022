#pragma once
#include <iostream>
#include <vector>

class day4
{
public:
	day4(std::string fileName);
private:
	std::vector<std::string> elfPairs;
	int part1();
	int part2();
};

