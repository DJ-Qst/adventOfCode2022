#include "day11.h"
#include "daySetup.h"
#include <queue>
#include <string>
#include <cmath>
#include <iostream>
#include <time.h>
#include <boost/multiprecision/cpp_int.hpp>

namespace bmp = boost::multiprecision;


struct monkey getNewMonkey(std::queue<int> initItems, std::string operation, std::string test);
struct monkey defineNewMonkey(std::vector<std::string> linesList);

struct monkey {
	// Items: Theinteger items the monkey holds
	// Operation: A 3-4 character string, index 0 is the operation and index 2+ is the factor;
	// Test: A 4 character string: Index 0-1 is what to divide by, Index 2 is what monkey to throw to if true, Index 3 is what monkey to throw to if false
	
	int numInspected = 0;
	std::queue<unsigned long long> items; 
	std::string operation;
	std::string test;
};

day11::day11(std::string fileName){
	daySetup setup(fileName);
	txtLines = setup.getLineStrings();
	
	std::cout << "The Monkey Business is: " << part1() << std::endl;
	std::cout << "The big business is: " << part2() << std::endl;
};




int day11::part1() {
	std::vector<monkey> monkeyList;
	std::vector<std::string> monkeyInfo;
	int lineCounter = 0;
	int currentItem;
	std::vector<int> numInspected;
	int monkeyBusiness = 1;
	std::queue<int> q;
	
	// Split the text fileinto the differrent monkeys and make them
	for (int i = 0; i < txtLines.size(); i++) {
		monkeyInfo.push_back(txtLines[i]);
		lineCounter += 1;
		if (lineCounter == 7) {
			monkeyList.push_back(defineNewMonkey(monkeyInfo));
			monkeyInfo.clear();
			lineCounter = 0;
		}
	}

	// 20 rounds
	for (int i = 1; i <= 20; i++) {
		// For each monkey; Use index so the actual monkey is adjusted, very important
		for (int mon = 0; mon < monkeyList.size(); mon++) {
			while (!monkeyList[mon].items.empty()) {
				// Get the item
				monkeyList[mon].numInspected += 1;
				currentItem = monkeyList[mon].items.front();
				monkeyList[mon].items.pop();
				
				// Do the operation
				if (monkeyList[mon].operation[0] == '*') {
					if (monkeyList[mon].operation[2] == 'o') {
						currentItem = currentItem;
					}
					else {
						currentItem *= stoi(monkeyList[mon].operation.substr(2));
					}

				}
				else if (monkeyList[mon].operation[0] == '+') {
					currentItem += stoi(monkeyList[mon].operation.substr(2));

				}
				currentItem /= 3;

				// Run the test
				if ((currentItem % stoi(monkeyList[mon].test.substr(0,2))) == 0) {
					monkeyList[int(monkeyList[mon].test[2]) - 48].items.push(currentItem);
				}
				else {
					monkeyList[int(monkeyList[mon].test[3]) - 48].items.push(currentItem);
				}
			}
		}
	}

	// After 20 rounds, find the highest two
	for (monkey mon: monkeyList) {
		numInspected.push_back(mon.numInspected);
	}
	monkeyBusiness *= *max_element(numInspected.begin(), numInspected.end());
	numInspected.erase(std::remove(numInspected.begin(), numInspected.end(), *max_element(numInspected.begin(), numInspected.end())), numInspected.end());
	monkeyBusiness *= *max_element(numInspected.begin(), numInspected.end());


	return monkeyBusiness;
}

unsigned long long day11::part2() {
	std::vector<monkey> monkeyList;

	// Setting up monkeys
	std::vector<std::string> monkeyInfo;
	int lineCounter = 0;

	// Doing the rounds
	unsigned long long int currentItem;

	// Final calculation
	std::vector<int> numInspected;
	unsigned long long monkeyBusiness = 1;

	// Split the text fileinto the differrent monkeys and make them
	for (int i = 0; i < txtLines.size(); i++) {
		monkeyInfo.push_back(txtLines[i]);
		lineCounter += 1;
		if (lineCounter == 7) {
			monkeyList.push_back(defineNewMonkey(monkeyInfo));
			monkeyInfo.clear();
			lineCounter = 0;
		}
	}

	// 20 rounds
	for (int i = 1; i <= 10000; i++) {
		// For each monkey
		for (int mon = 0; mon < monkeyList.size(); mon++) {
			while (!monkeyList[mon].items.empty()) {
				// Get the item
				monkeyList[mon].numInspected += 1;
				currentItem = monkeyList[mon].items.front();
				monkeyList[mon].items.pop();

				// Do the operation
				if (monkeyList[mon].operation[0] == '*') {
					if (monkeyList[mon].operation[2] == 'o') {
						currentItem *= currentItem;
					}
					else {
						currentItem *= stoi(monkeyList[mon].operation.substr(2));
					}

				}
				else if (monkeyList[mon].operation[0] == '+') {
					currentItem += stoi(monkeyList[mon].operation.substr(2));

				}
				currentItem = (currentItem % 9699690);
				if (currentItem < 0) {
					currentItem += 9699690;
				}
				//if (currentItem < 0) {
				//	currentItem = (currentItem % LLONG_MAX);
				//}
				

				// Run the test
				if ((currentItem % stoi(monkeyList[mon].test.substr(0, 2))) == 0) {
					monkeyList[int(monkeyList[mon].test[2]) - 48].items.push(currentItem);
				}
				else {
					monkeyList[int(monkeyList[mon].test[3]) - 48].items.push(currentItem);
				}
			}
		}
	}
	
	// After rounds, find the highest two
	for (monkey mon : monkeyList) {
		numInspected.push_back(mon.numInspected);
	}
	monkeyBusiness *= *max_element(numInspected.begin(), numInspected.end());
	numInspected.erase(std::remove(numInspected.begin(), numInspected.end(), *max_element(numInspected.begin(), numInspected.end())), numInspected.end());
	monkeyBusiness *= *max_element(numInspected.begin(), numInspected.end());


	return monkeyBusiness;
}

monkey getNewMonkey(std::queue<unsigned long long> initItems, std::string operation, std::string test) {
	monkey newMon;
	newMon.items = initItems;
	newMon.operation = operation;
	newMon.test = test;

	return newMon;
}

monkey defineNewMonkey(std::vector<std::string> linesList) {
	// This is horrendously ugly, but it's specifically fitted to the input data
	// Please trust and ignore
	std::queue<unsigned long long> initItems;
	std::string operation;
	std::string test;

	for (int i = 18; i < linesList[1].size(); i += 4) {
		initItems.push(stoi(linesList[1].substr(i, 2)));
	}

	operation = linesList[2].substr(23);
	test = linesList[3].substr(21);
	if (test.size() == 1) {
		test += " " + linesList[4].substr(29) + linesList[5].substr(30);
	}
	else {
		test += linesList[4].substr(29) + linesList[5].substr(30);
	}
		

	return getNewMonkey(initItems, operation, test);
}

