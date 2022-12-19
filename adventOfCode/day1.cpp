#include "day1.h"
#include "daySetup.h"
#include <iostream>
#include <vector>
using namespace std;

void day1::day1Main(string fileName){
    daySetup setup(fileName);
    // Calling the function to get the elves
    vector<vector<int>> elves = setup.getIntVectors();

    // Day 1 Part 1
    cout << "The elf with the most calories holds " << part1(elves) << " calories.\n";

    // Day 1 Part 2
    cout << "The sum of calories held by the top three elves is " << part2(elves) << " calories.\n";
}

int day1::part1(vector<vector<int>> elves){
    int mostCals = 0;
    int elfCals = 0;
    
    // For each elf
    for (vector<int> elf : elves) {
        elfCals = 0;
        // For each calorie its holding
        for (int calorie : elf) {
            elfCals += calorie;
        }

        // If the calories the elf is holding is greater than the current max
        if (elfCals > mostCals) {
            mostCals = elfCals;
        }
    }
    return mostCals;
}

int day1::part2(vector<vector<int>> elves){
    vector<int> top3(3, 0);
    int sumOf3 = 0;
    int elfCals = 0;

    // For each elf
    for (vector<int> elf : elves) {
        elfCals = 0;
        // For each calorie its holding
        for (int calorie : elf) {
            elfCals += calorie;
        }

        // For each of the current top 3
        for (int i = 0; i < top3.size(); i++) {
            // If the current elf is in the top 3, put it there
            if (elfCals > top3[i]) {
                top3[i] = elfCals;
                break;
            }
        }
    }
    
    for (int topElf : top3) {
        sumOf3 += topElf;
    }
    
    return sumOf3;
}