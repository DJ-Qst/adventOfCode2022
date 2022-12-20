#pragma once
#include <iostream>
#include <vector>


class day8 {
public:
	day8(std::string fileName);
private:
	std::vector<std::string> rows;
	int part1();
	int part2();
};

