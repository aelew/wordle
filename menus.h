#ifndef MENUS_H
#define MENUS_H

#include <iostream>
#include <fstream>
#include <vector>
#include "utils.h"

void play() {
     // Get words from `words.txt`
    std::vector<std::string> words = get_words();
    if (words.size() == 0) {
        std::cerr << "Your words.txt file does not exist or has no words to choose from!" << std::endl;
        return;
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
}

void display_tutorial() {
    std::cout << "=============================================" << std::endl;
    std::cout << "                 HOW TO PLAY" << std::endl;
    std::cout << "=============================================" << std::endl;
    std::cout << "Guess the Wordle in 6 tries." << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << "HOW TO PLAY:" << std::endl;
    std::cout << "- Each guess must be a valid 5 letter word." << std::endl;
    std::cout << "- The color of the tiles will change to show" << std::endl;
    std::cout << "  you how close your guess was to the word." << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << "  ---  ---  ---  ---  --- " << std::endl;
    std::cout << " | W || E || A || R || Y | " << std::endl;
    std::cout << "  ---  ---  ---  ---  --- " << std::endl;
    std::cout << "W is in the word and in the correct spot." << std::endl;
    std::cout << std::endl;
    std::cout << "  ---  ---  ---  ---  --- " << std::endl;
    std::cout << " | P || I || L || L || S | " << std::endl;
    std::cout << "  ---  ---  ---  ---  --- " << std::endl;
    std::cout << "I is in the word and in the correct spot." << std::endl;
    std::cout << std::endl;
    std::cout << "  ---  ---  ---  ---  --- " << std::endl;
    std::cout << " | V || A || G || U || E | " << std::endl;
    std::cout << "  ---  ---  ---  ---  --- " << std::endl;
    std::cout << "U is in the word and in the correct spot." << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
}

void start() {
    bool exited = false;
    // Use a while loop so the main menu is displayed after the selected option is complete
    while (!exited) {
        std::cout << "=========================" << std::endl;
        std::cout << "    WELCOME TO WORDLE" << std::endl;
        std::cout << "=========================" << std::endl;
        std::cout << std::endl;
        std::cout << "1. Play Wordle" << std::endl;
        std::cout << "2. How to Play" << std::endl;
        std::cout << "3. Statistics Summary" << std::endl;
        std::cout << "4. Reset Statistics" << std::endl;
        std::cout << "5. Exit" << std::endl;
        std::cout << std::endl;
        std::cout << "Select an option: ";

        int option;
        std::cin >> option;

        switch (option) {
            case 1:
                play();
                break;
            case 2:
                display_tutorial();
                break;
            case 5:
                std::cout << "Goodbye!" << std::endl;
                exited = true;
                break;
            default:
                std::cerr << "Uh oh! You didn't enter a valid option." << std::endl;
                // Reset the fail state of cin
                std::cin.clear();
                std::cin.ignore();
                break;
        }

        if (option >= 1 && option <= 5) {
            std::cout << "Press [enter] to continue" << std::endl;
            std::cin.ignore();
            std::cin.get();
        }
    }
}

#endif
