#include "day7.h"
#include <iostream>
#include <vector>
#include <map>
#include <string>
/*
struct dir* getNewDir(int dirName);
void addSubDir(dir* parentDir, std::string subDirName, int subDirSize);
void printTree(dir* root);

// Basic directory
struct dir {
	std::string dirName;
	int dirSize;
	std::map<std::string, dir*> subDirs;
};
*/
int main(){
    day7 day7("day7.txt");
	/*
	dir* root;
	root = getNewDir(50);
	root->dirSize;
	*/
	return 0;
}


/*
// Function to get make a new directory
dir* getNewDir(int newDirSize) {
	dir* newDir = new dir();
	newDir->dirSize = newDirSize;

	return newDir;
}

// Function to add a subdirectory to a specific directory
void addSubDir(dir* parentDir, std::string subDirName, int subDirSize) {
	//Create a new subdirectory
	dir* subDir = getNewDir(subDirSize);
	parentDir->subDirs[subDirName] = subDir;
}

void printTree(dir* root) {
	std::cout << root->dirSize;
}
*/