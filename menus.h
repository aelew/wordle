#ifndef MENUS_H
#define MENUS_H

#include <iostream>
#include <fstream>
#include <vector>
#include "utils.h"

int play() {
     // Get words from `words.txt`
    std::vector<std::string> words = get_words();
    if (words.size() == 0) {
        std::cerr << "Your words.txt file does not exist or has no words to choose from!" << std::endl;
        return 1;
    }

    // Get a random index in the words vector
    int randomWordIndex = get_random_number(0, words.size() - 1);

    // Select a random word
    // string solution = strtoupper(words[randomWordIndex]);
    std::string solution = "SLATE";

    bool solved = false;
    int remainingTries = 6;

    while (remainingTries != 0) {
        std::string attempt;
        std::cin >> attempt;
        attempt = strtoupper(attempt);

        if (check_attempt(solution, attempt)) {
            solved = true;
            break;
        }

        remainingTries--;
    }

    if (solved) {
        std::cout << "Splendid! You win!" << std::endl;
    } else {
        std::cout << "The word was: " << solution << "\n\nBetter luck next time!" << std::endl;
    }

    std::ofstream file;
    file.open("stats.txt", std::ios::app);
    file << solution << "," << solved << std::endl;
    file.close();

    return 0;
}

int displayMainMenu() {
    std::cout << "=========================" << std::endl;
    std::cout << "    WELCOME TO WORDLE" << std::endl;
    std::cout << "=========================" << std::endl;
    std::cout << "" << std::endl;
    std::cout << "1. Play Wordle" << std::endl;
    std::cout << "2. How to Play" << std::endl;
    std::cout << "3. Statistics Summary" << std::endl;
    std::cout << "4. Reset Statistics" << std::endl;
    std::cout << "5. Exit" << std::endl;
    std::cout << "" << std::endl;
    std::cout << "Select an option: ";

    int option;
    std::cin >> option;

    int exitCode = 0;

    switch (option) {
        case 1:
            exitCode = play();
            break;
        case 5:
            exitCode = 0;
            break;
        default:
            std::cerr << "Uh oh! You didn't enter a valid option." << std::endl;
            exitCode = -1;
            break;
    }

    return exitCode;
}

#endif