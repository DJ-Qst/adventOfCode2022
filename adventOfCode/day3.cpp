#include "day3.h"
#include "daySetup.h"
#include <string>

day3::day3(std::string fileName)
{
	// Initialize setup class and get lines from text file
	daySetup setup(fileName);
	dayLines = setup.getLineStrings();

	// Add priorities to the map
	std::string alphabet = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
	for (int i = 0; i < 52; i++) {
		letterConversion[alphabet[i]] = i + 1;
	}

	// Run parts 1 and 2
	std::cout << "The sum of the priorities is: " << part1() << "\n";
	std::cout << "The sum of the priorities of the groups is: " << part2() << "\n";
}

int day3::part1()
{
	std::string frontHalf, backHalf;  // Variables to store the first and second halves of each line
	int lineLength;  // Holds the length of each line
	int prioritySum = 0;  // Total sum of the letter priorities, what gets returned

	for (std::string line : dayLines) {
		// Get the line length and the two half substrings
		lineLength = line.length();
		frontHalf = line.substr(0, lineLength / 2);  //.substr is inclusive for the start and noninclusve for the end
		backHalf = line.substr(lineLength / 2);
		
		for (char character : frontHalf) {
			//.find returns -1 if the character is not in the string
			if (backHalf.find(character) != -1) {
				prioritySum += letterConversion[character];
				break;
			}
		}
	}

	return prioritySum;
}

int day3::part2()
{
	int groupCounter = 0;  // Counter to see if 3 elves are in the group
	std::string elf1, elf2, elf3;  // String variables to hold each of the elves when it's time to check
	std::string potentialChars;  // Chars that are the same betweens elves 1 and 2 that are then tested against elf 3
	std::vector<std::string> elfGroup;  // Vector to hold each of the elves in the group
	int prioritySum = 0;  // Sum of the priorities that gets returned

	for (std::string line : dayLines) {
		// Add 1 to the group counter and add the elf to the group
		groupCounter += 1;
		elfGroup.push_back(line);
		
		if (groupCounter == 3) {
			elf1 = elfGroup[0];
			elf2 = elfGroup[1];
			elf3 = elfGroup[2];

			// Check elves 1 and 2 to find same characters
			for (char letter : elf1) {
				if (elf2.find(letter) != -1) {
					// Makes sure duplicates don't get added to potential
					if (potentialChars.find(letter) == -1) {
						potentialChars += letter;
					}
				}
			}
			
			// Check potential characters against elf 3 to get the only one
			for (char letter : potentialChars) {
				if (elf3.find(letter) != -1) {
					prioritySum += letterConversion[letter];
				}
			}

			// Reset all counter and temp variables
			groupCounter = 0;
			elfGroup.clear();
			potentialChars.clear();
		}
	}

	return prioritySum;
}
