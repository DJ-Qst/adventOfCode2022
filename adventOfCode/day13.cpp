#include "day13.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>

enum day13::rightOrder {
	False = false,
	True = true,
	Undef = 2
};

day13::day13(std::string fileName) {
	std::fstream file;
	std::vector<std::string> pair;
	std::string line;

	// Getting the pairs
	file.open(fileName, std::ios::in);
	if (file.is_open()) {
		while (getline(file, line)) {
			// If the size is 2 its a pair
			if (pair.size() == 2) {
				pairsList.push_back(pair);
				pair.clear();
				continue;
			}
			pair.push_back(line);
		}
		pairsList.push_back(pair); // To get the last pair
		file.close();
	}
	else std::cout << "FILE NOT FOUND!!" << std::endl;

	std::cout << "The sum of indexes of pairs in the right order is " << part1() << std::endl;
	std::cout << "The product of indexes of dividers is " << part2() << std::endl;
}

int day13::part1() {
	std::string lSide, rSide;
	int indexSum = 0;

	for (int i = 0; i < pairsList.size(); i++) {
		lSide = pairsList[i][0];
		rSide = pairsList[i][1];

		if (checkElements(lSide, rSide)) indexSum += (i + 1);
	}
	return indexSum;
}

int day13::part2() {
	std::vector<std::string> sortedInputs{ "[[2]]","[[6]]" };
	std::string lSide, rSide, temp;
	int indexSum = 1;

	for (int i = 0; i < pairsList.size(); i++) {
		lSide = pairsList[i][0];
		rSide = pairsList[i][1];

		sortedInputs.push_back(lSide);
		sortedInputs.push_back(rSide);
	}
	for (int k = 0; k < sortedInputs.size(); k++) {
		for (int j = k + 1; j < sortedInputs.size(); j++) {
			if (!checkElements(sortedInputs[k], sortedInputs[j])) {
				temp = sortedInputs[j];
				sortedInputs[j] = sortedInputs[k];
				sortedInputs[k] = temp;
			}
		}
	}
	indexSum *= std::distance(sortedInputs.begin(), std::find(sortedInputs.begin(), sortedInputs.end(), "[[2]]")) + 1;
	indexSum *= std::distance(sortedInputs.begin(), std::find(sortedInputs.begin(), sortedInputs.end(), "[[6]]")) + 1;

	return indexSum;
}

std::vector<std::string> day13::splitItem(std::string item) {
	int openBrac = 0;
	int startPos = 0;
	std::vector<std::string> splitItem;

	for (int i = 0; i < item.size(); i++) {
		if (item[i] == '[') openBrac++;
		else if (item[i] == ']') openBrac--;
		
		if ((item[i] == ',') && (openBrac == 0)) {
			splitItem.push_back(item.substr(startPos, (i - startPos)));
			startPos = i + 1; // i is a comma, so you have to add 1
		}
	}
	// Adding anything remaining
	splitItem.push_back(item.substr(startPos));

	return splitItem;
}

day13::rightOrder day13::checkElements(std::string first, std::string second) {
	day13::rightOrder rightOrder = Undef; // This is a tristate enum instead of a bool so I can see if the value has been adjusted
	std::vector<std::string> firstList, secondList;
	// Remove the brackets for this level
	first = first.substr(1, (first.length() - 2));
	second = second.substr(1, (second.length() - 2));
	
	// Turn each thing into a list, if its zero, keep it empty
	if (first.size() != 0) firstList = splitItem(first);
	if (second.size() != 0)	secondList = splitItem(second);

	// Get the smaller of the two lists, used for easy looping
	std::vector<std::string>& smallerList = (firstList.size() < secondList.size()) ? firstList : secondList;
	
	for (int i = 0; i < smallerList.size(); i++) {
		// If both are integers
		if ((firstList[i][0] != '[') && (secondList[i][0] != '[')) {
			int firstInt = stoi(firstList[i]);
			int secondInt = stoi(secondList[i]);
			if (firstInt < secondInt) rightOrder = True;
			else if (secondInt < firstInt) rightOrder = False;
		}
		
		// If one or both of them are lists
		else {
			// Wrap the element in brackets if its an integer
			std::string firstSub = (firstList[i][0] == '[') ? firstList[i] : ('[' + firstList[i] + ']');
			std::string secondSub = (secondList[i][0] == '[') ? secondList[i] : ('[' + secondList[i] + ']');
			rightOrder = checkElements(firstSub, secondSub); // Recursive check
		}
		
		// If the solution has been found, its time to break
		if (rightOrder != Undef) break;
	}

	// Final check, if it has not been decided yet after all the elements are checked, see if lengths are proper
	if (rightOrder == Undef) {
		if (firstList.size() < secondList.size()) rightOrder = True;
		else if (secondList.size() < firstList.size()) rightOrder = False;
	}
	return rightOrder;
} 
