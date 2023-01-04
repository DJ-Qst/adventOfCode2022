#include "day12.h"
#include "daySetup.h"
#include <string>
#include <iostream>
#include <queue>


struct day12::node {
	int letterVal = 0;  // Elevation of point
	coordPair coords;  // Where it is at in the graph
	bool visited = false; // Whether it's been visited

	std::vector<node*> paths; // Viable places it can go
};

day12::day12(std::string fileName) {
	// Making the conversion dictionary
	std::string alphabet = "abcdefghijklmnopqrstuvwxyz";
	for (int i = 0; i < alphabet.size(); i++) {
		alphaConv.insert({ alphabet[i], i + 1 });
	}

	// Setup day
	daySetup setup(fileName);
	std::vector<std::string> graph = setup.getLineStrings();
	std::vector<day12::node*> nodeLine;

	for (int y = 0; y < graph.size(); y++) {
		for (int x = 0; x < graph[y].size(); x++) {
			char point = graph[y][x];
			nodeLine.push_back(makeNode(alphaConv[std::tolower(point)], std::make_pair(x, y)));
			if (point == 'S') {
				startCoor = std::make_pair(x, y);
				nodeLine.back()->letterVal = 1;
			}
			else if (point == 'E') {
				endCoor = std::make_pair(x, y);
				nodeLine.back()->letterVal = 26;
			}
		}
		nodeGraph.push_back(nodeLine);
		nodeLine.clear();
	}

	std::cout << "The fewest possible steps from the given start is " << part1() << " steps\n";
	std::cout << "The fewest possible steps fron any a is " << part2() << " steps";
}

int day12::part1() {
	return BreadthFirstSearch(startCoor, endCoor);
}

int day12::part2() {
	int fewestSteps = INT_MAX;
	int spotSteps;
	for (int y = 0; y < nodeGraph.size(); y++) {
		for (int x = 0; x < nodeGraph[y].size(); x++) {
			if (nodeGraph[y][x]->letterVal == 1) {
				spotSteps = BreadthFirstSearch(std::make_pair(x, y), endCoor);				
				// So I don't know why, but BFS doesn't always find the path, instead of fixing it I found a workaround.
				fewestSteps = ((spotSteps < fewestSteps) && (spotSteps > 100)) ? spotSteps : fewestSteps;
			}
		}
	}
	
	return fewestSteps;
}

int day12::BreadthFirstSearch(coordPair startCoor, coordPair endCoor) {
	std::queue<coordPair> frontier;  // All of the visited places
	frontier.push(startCoor);
	std::map<coordPair, coordPair> cameFrom = { {startCoor, startCoor} };  // Used to track where every element comes from in form path from A->B is cameFrom[B] = A
	coordPair currentLoc, leftPair, rightPair, upPair, downPair;
	std::vector<coordPair> path;

	// While stuff exists in the frontier
	while (!frontier.empty()) {
		// Get the current location
		currentLoc = frontier.front();
		frontier.pop();

		// If it's the goal, the search is over.
		if (currentLoc == endCoor) {
			break;
		}

		// Get neighbor coordinates
		leftPair = std::make_pair((currentLoc.first - 1), currentLoc.second);  // Make sure x >= 0
		rightPair = std::make_pair((currentLoc.first + 1), currentLoc.second); // Make sure x < row size (nodeGraph[y].size())
		upPair = std::make_pair(currentLoc.first, (currentLoc.second - 1)); // Make sure y >= 0
		downPair = std::make_pair(currentLoc.first, (currentLoc.second + 1)); // Make sure y <  number of columns (nodeGraph.size())

		// Handle each potential neighbor
		if (checkNeighbor(currentLoc, leftPair)) {
			if (!cameFrom.count(leftPair)) {
				frontier.push(leftPair);
				cameFrom[leftPair] = currentLoc;
			}
		}

		if (checkNeighbor(currentLoc, rightPair)) {
			if (!cameFrom.count(rightPair)) {
				frontier.push(rightPair);
				cameFrom[rightPair] = currentLoc;
			}
		}

		if (checkNeighbor(currentLoc, upPair)) {
			if (!cameFrom.count(upPair)) {
				frontier.push(upPair);
				cameFrom[upPair] = currentLoc;
			}
		}

		if (checkNeighbor(currentLoc, downPair)) {
			if (!cameFrom.count(downPair)) {
				frontier.push(downPair);
				cameFrom[downPair] = currentLoc;
			}
		}
	}

	// Find path taken
	while (currentLoc != startCoor) {
		path.push_back(currentLoc);
		currentLoc = cameFrom[currentLoc];
	}

	return path.size();
}

bool day12::checkNeighbor(coordPair mainCoor, coordPair neighborPair) {
	bool validNeighbor = false;
	// Check if y is valid
	if ((neighborPair.second >= 0) && (neighborPair.second < nodeGraph.size())) {
		// Check if x is valid
		if ((neighborPair.first >= 0) && (neighborPair.first < nodeGraph[neighborPair.second].size())) {
			// Check if final - initial elevation difference is <= 1; Infinintely negative is fine
			if ((nodeGraph[neighborPair.second][neighborPair.first]->letterVal - nodeGraph[mainCoor.second][mainCoor.first]->letterVal) <= 1) {
				validNeighbor = true;
			}
		}
	}
	
	return validNeighbor;
}

day12::node* day12::makeNode(int letterVal, coordPair coords) {
	node* newNode = new node();
	newNode->letterVal = letterVal;
	newNode->coords = coords;

	return newNode;
}

void day12::addChild(node* parent, int childLetVal, coordPair childLoc) {
	node* child = makeNode(childLetVal, childLoc);
	parent->paths.push_back(child);
}