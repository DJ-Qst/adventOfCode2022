#include "day4.h"
#include "daySetup.h"
#include <iostream>
#include <string>
#include <vector>

day4::day4(std::string fileName)
{
	daySetup setup(fileName);
	elfPairs = setup.getLineStrings();

	std::cout << "The number of very bad pairs is: " << part1() << "\n";
	std::cout << "The number of kinda bad pairs is: " << part2() << "\n";
}

int day4::part1()
{
	int numBadPairs = 0;
	std::string elf1, elf2;
	int elf1Lower, elf1Upper, elf2Lower, elf2Upper;
	int charIndex;

	for (std::string elfPair : elfPairs) {
		charIndex = elfPair.find(",");
		elf1 = elfPair.substr(0, charIndex);
		elf2 = elfPair.substr(charIndex + 1);

		charIndex = elf1.find("-");
		elf1Lower = std::stoi(elf1.substr(0, charIndex));
		elf1Upper = std::stoi(elf1.substr(charIndex + 1));

		charIndex = elf2.find("-");
		elf2Lower = std::stoi(elf2.substr(0, charIndex));
		elf2Upper = std::stoi(elf2.substr(charIndex + 1));

		if ((elf1Lower <= elf2Lower) && (elf1Upper >= elf2Upper)) {
			numBadPairs += 1;
		}

		else if ((elf2Lower <= elf1Lower) && (elf2Upper >= elf1Upper)) {
			numBadPairs += 1;
		}
	}
	return numBadPairs;
}

int day4::part2()
{
	int numBadPairs = 0;
	std::string elf1, elf2;
	std::vector<int> elf1Range, elf2Range;
	int elf1Lower, elf1Upper, elf2Lower, elf2Upper;
	int charIndex;

	for (std::string elfPair : elfPairs) {
		charIndex = elfPair.find(",");
		elf1 = elfPair.substr(0, charIndex);
		elf2 = elfPair.substr(charIndex + 1);

		charIndex = elf1.find("-");
		elf1Lower = std::stoi(elf1.substr(0, charIndex));
		elf1Upper = std::stoi(elf1.substr(charIndex + 1));

		charIndex = elf2.find("-");
		elf2Lower = std::stoi(elf2.substr(0, charIndex));
		elf2Upper = std::stoi(elf2.substr(charIndex + 1));
		
		for (int i = elf1Lower; i <= elf1Upper; i++) {
			elf1Range.push_back(i);
		}

		for (int i = elf2Lower; i <= elf2Upper; i++) {
			elf2Range.push_back(i);
		}

		if ((elf1Upper-elf1Lower) > (elf2Upper - elf2Lower)){
			for (int section : elf2Range) {
				if (std::find(elf1Range.begin(), elf1Range.end(), section) != elf1Range.end()){
					numBadPairs += 1;
					break;
				}
			}
		}
	
		else {
			for (int section : elf1Range) {
				if (std::find(elf2Range.begin(), elf2Range.end(), section) != elf2Range.end()) {
					numBadPairs += 1;
					break;
				}
			}
		}

		elf1Range.clear();
		elf2Range.clear();
	}
	return numBadPairs;
}
