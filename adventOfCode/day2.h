#pragma once
#include "daySetup.h"
#include <string>
#include <vector>
#include <map>
using namespace std;

class day2
{
public:
	string fileName = "day2.txt";
	void day2Main();
private:
	daySetup setup;
	vector<string> lines = setup.getLineStrings();
	map<string, int> moveConversion{
		{"A", 1},
		{"B", 2},
		{"C", 3},
		{"X", 1},
		{"Y", 2},
		{"Z", 3}
	};
	
	int part1();
	int part2();
};

