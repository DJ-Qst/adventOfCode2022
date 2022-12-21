#pragma once
#include <string>
#include <vector>

class day10
{
public:
	day10(std::string fileName);
private:
	std::vector<std::string> commands;
	int part1();
	void part2();
};

