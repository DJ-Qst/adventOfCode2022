#pragma once
#include <string>
#include <vector>
#include <map>

typedef std::pair<int, int> coordPair;

class day12
{
public:
	day12(std::string fileName);
private:
	std::map<char, int> alphaConv; // Convert letter chars to numbers
	std::pair<int, int> startCoor, endCoor;  // Where I begin and end
	
	struct node; // The all important struct
	node* makeNode(int letterVal, coordPair coords);  // Node constructor
	void addChild(node* parent, int childLetVal, coordPair childLoc); // Function to add a child to a node
	std::vector<std::vector<node*>> nodeGraph;  // Representing graph as nodes

	int part1(); // Part 1 code
	int part2();
	int BreadthFirstSearch(coordPair startCoor, coordPair endCoor); // Run a search to the determined end coordinate and return number of steps
	bool checkNeighbor(coordPair mainCoor, coordPair neighborPair); // Used to see if a coordinate is a valid neighbor
};

