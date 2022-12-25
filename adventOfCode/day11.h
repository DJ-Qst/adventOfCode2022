#pragma once
#include <string>
#include <vector>

class day11
{
public:
	day11(std::string fileName);
private:
	std::vector<std::string> txtLines;
	int part1();
	unsigned long long part2();
	void testing();
};

