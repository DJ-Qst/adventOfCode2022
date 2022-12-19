#include "daySetup.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <string>

daySetup::daySetup(std::string userFile)
{
    fileName = userFile;
}

std::vector<std::vector<int>> daySetup::getIntVectors(){
    /*
        This function takes a text file of groups of numbers split by newlines and returns a vector of vectors
        holding all of those numbers as integers, split into their respective groups
    */
    std::fstream file;  // fstream object to work with file
    std::vector<std::vector<int>> masterVector;  // Vector to hold all of the individual vectors holding integers
    std::vector<int> subVector;  // Vector to hold integers, gets cleared consistently
    std::string line; // Variable to hold the string of file line

    file.open(fileName, std::ios::in);  // Open file

    if (file.is_open()) {
        // While there are lines to get
        while (std::getline(file, line)) {
            // If the length of the line is greater than 1
            // Necesary to find blanklines, which have a length of 1
            if (line.length() > 1) {
                // Converts line to an integer with stoi() and adds it to the subVector
                subVector.push_back(stoi(line));
            }
            else {
                // If the line length is 1 or 0 (blank line) adds subVector to master vector and clears subvector
                masterVector.push_back(subVector);
                subVector.clear();
            }
        }
        // Closes file
        file.close();
    }

    return masterVector;
}

std::vector<std::string> daySetup::getLineStrings()
{
    std::vector<std::string> lines;
    std::string line;
    std::fstream file;

    file.open(fileName, std::ios::in);
    if (file.is_open()) {
        while (getline(file, line)) {
            lines.push_back(line);
        }
        file.close();
    }
    else {
        std::cout << "ERROR: File Not Opened";
    }
    return lines;
}
