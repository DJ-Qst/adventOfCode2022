#pragma once
#include <iostream>
#include <vector>

class day7
{
public:
	day7(std::string fileName);
private:
	std::vector<std::string> lines;
	int part1();
};

