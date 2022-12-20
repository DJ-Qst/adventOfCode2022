#include "day8.h"
#include "daySetup.h"
#include <iostream>
#include <vector>

day8::day8(std::string fileName) {
	// Setup the days
	daySetup setup(fileName);
	rows = setup.getLineStrings();

	// Runing the code parts
	std::cout << "The number of visible trees is " << part1() << " trees\n";
	std::cout << "The highest possible scenic score is " << part2() << " points\n";
}

int day8::part1() {
	int numVisible = 0;
	int tempRow, tempCol, posVal;
	bool visible;

	for (int rowNum = 0; rowNum < rows.size(); rowNum++) {
		for (int colNum = 0; colNum < rows[rowNum].size(); colNum++) {
			posVal = int(rows[rowNum][colNum]) - 48;  // Have to subtract 48 to get from ascii to int value
			// Check edge
			if ((rowNum == 0) || (rowNum == rows.size() - 1)) {
				numVisible += 1;
				continue;
			}
			else if ((colNum == 0) || (colNum == rows[rowNum].size() - 1)) {
				numVisible += 1;
				continue;
			}
			
			// Check left
			visible = true;
			tempRow = rowNum - 1;
			for (tempRow; tempRow >= 0; tempRow--) {
				if ((int(rows[tempRow][colNum])-48) >= posVal) {
					visible = false;
					break;
				}
			}
			if (visible) {
				numVisible += 1;
				continue;
			}

			// Check right
			visible = true;
			tempRow = rowNum + 1;
			for (tempRow; tempRow < rows[rowNum].size(); tempRow++) {
				if ((int(rows[tempRow][colNum]) - 48) >= posVal) {
					visible = false;
					break;
				}
			}
			if (visible) {
				numVisible += 1;
				continue;
			}

			// Check up
			visible = true;
			tempCol = colNum - 1;
			for (tempCol; tempCol >= 0; tempCol--) {
				if ((int(rows[rowNum][tempCol])-48) >= posVal) {
					visible = false;
					break;
				}
			}
			if (visible) {
				numVisible += 1;
				continue;
			}
			
			// Check down
			visible = true;
			tempCol = colNum + 1;
			for (tempCol; tempCol < rows.size(); tempCol++) {
				if ((int(rows[rowNum][tempCol])-48) >= posVal) {
					visible = false;
					break;
				}
			}
			if (visible) {
				numVisible += 1;
				continue;
			}
		}

	}
	return numVisible;
}

int day8::part2() {
	int highestScore = 0;
	int posScore, sideScore;
	int tempRow, tempCol, tempPosVal, posVal;

	for (int rowNum = 0; rowNum < 99; rowNum++) {
		for (int colNum = 0; colNum < 99; colNum++) {
			posVal = int(rows[rowNum][colNum]) - 48;  // Have to subtract 48 to get from ascii to int value
			posScore = 1;

			// Check left
			sideScore = 0;
			for (tempCol = colNum; tempCol >= 0; tempCol--) {
				// If it's at the edge, stop 
				if (tempCol == 0) {
					break;
				}
				sideScore++;
				tempPosVal = int(rows[rowNum][tempCol - 1]) - 48;
				// If the current position is too tall, stop
				if (tempPosVal >= posVal) {
					break;
				}
			}
			if (sideScore > 0) { posScore *= sideScore; }

			// Check right
			sideScore = 0;
			for (tempCol = colNum; tempCol <= 98; tempCol++) {
				if (tempCol == 98) {
					break;
				}
				sideScore++;
				tempPosVal = int(rows[rowNum][tempCol+1]) - 48;
				if (tempPosVal >= posVal) {
					break;
				}
			}
			if (sideScore > 0) { posScore *= sideScore; }

			// Check up
			sideScore = 0;
			for (tempRow = rowNum; tempRow >= 0; tempRow--) {
				if (tempRow == 0) {
					break;
				}
				sideScore++;
				tempPosVal = int(rows[tempRow - 1][colNum]) - 48;
				if (tempPosVal >= posVal) {
					break;
				}
			}
			if (sideScore > 0) { posScore *= sideScore; }


			// Check down
			sideScore = 0;
			for (tempRow = rowNum; tempRow <= 98; tempRow++) {
				if (tempRow == 98) {
					break;
				}
				sideScore++;
				tempPosVal = int(rows[tempRow + 1][colNum]) - 48;
				if (tempPosVal >= posVal) {
					break;
				}
			}
			if (sideScore > 0) { posScore *= sideScore; }

			if (posScore > highestScore) {
				highestScore = posScore;
			}
		}
	}

	return highestScore;
}