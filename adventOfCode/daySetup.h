#pragma once
#include <iostream>
#include <vector>

class daySetup{
private:
    std::string fileName;

public:
    daySetup(std::string userFile);
    std::vector<std::vector<int>> getIntVectors();
    std::vector<std::string> getLineStrings();
};

