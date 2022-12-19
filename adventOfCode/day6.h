#pragma once
#include <iostream>

class day6 {
public:
	day6(std::string fileName);
private:
	std::string dataBuffer;

	int part1();
	int part2();
};