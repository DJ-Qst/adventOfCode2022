#include "day2.h"
#include <iostream>
using namespace std;

void day2::day2Main()
{
	cout << "Your total score given move is " << part1() << " points\n";
	cout << "Your total score given outcome is " << part2() << " points\n";
}

int day2::part1()
{
	int tournamentScore = 0;
	
	string myMove;
	string oppMove;
	int myMoveInt;
	int oppMoveInt;
	int moveDiff;

	for (string line : lines) {
		oppMove = line.front();
		oppMoveInt = moveConversion[oppMove];

		myMove = line.back();
		myMoveInt = moveConversion[myMove];

		moveDiff = abs(myMoveInt - oppMoveInt);

		tournamentScore += myMoveInt;

		// If it is a draw
		if (myMoveInt == oppMoveInt) {
			tournamentScore += 3;
		}

		// If the two numbers are consecutive the bigger number wins
		else if ((moveDiff == 1) && (myMoveInt > oppMoveInt)) {
			tournamentScore += 6;
		}

		// If the two numbers are not consecutive the smallter number wins
		else if ((moveDiff != 1) && (myMoveInt < oppMoveInt)) {
			tournamentScore += 6;
		}
	}
	
	return tournamentScore;
}

int day2::part2()
{
	int tournamentScore = 0;
	vector<int> moves = { 1, 2, 3 };

	string outCome;
	string oppMove;
	int oppMoveInt;
	int oppMoveIndex; 
	int myMoveIndex;

	for (string line : lines) {
		// Getting the opponents move and its numerical value
		oppMove = line.front();
		oppMoveInt = moveConversion[oppMove];

		// Getting the needed outcome
		outCome = line.back();

		// Getting the index of the move list
		oppMoveIndex = oppMoveInt - 1;


		// If I lose
		if (outCome == "X") {
			tournamentScore += 0; // +0 to tournament score for a loss
			myMoveIndex = oppMoveIndex - 1;  // Losing move has a 1 lower index than the opponents move
			if (myMoveIndex == -1) { myMoveIndex += size(moves); }  // -1 index isn't accepted, add length of list to make index of last item
			tournamentScore += moves[myMoveIndex];
		}

		// If its a draw
		else if (outCome == "Y") {
			tournamentScore += 3;  // +3 to tournament score for a draw
			tournamentScore += oppMoveInt;  // My move = opponents move
		}

		
		// If I win
		else if (outCome == "Z") {
			tournamentScore += 6;  // +6 to tournament score for a win
			myMoveIndex = oppMoveIndex + 1; // Winning move has a 1 higher index than the opponents move
			if (myMoveIndex >= size(moves)) { myMoveIndex -= size(moves); } // If the index is out of range, put it back in range
			tournamentScore += moves[myMoveIndex];
		}
	}

	return tournamentScore;
}
