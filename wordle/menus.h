#ifndef MENUS_H
#define MENUS_H

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>

#include "utils.h"
#include "statistic.h"

void play() {
     // Get words from `words.txt`
    std::vector<std::string> words = getWords();
    if (words.size() == 0) {
        std::cerr << "Your words.txt file does not exist or has no words to choose from!" << std::endl;
        return;
    }

    // Get a random index in the words vector
    int randomWordIndex = getRandomNumber(0, words.size() - 1);

    // Select a random word
    // string solution = strtoupper(words[randomWordIndex]);
    std::string solution = "SOLVE";

    bool solved = false;
    int remainingTries = 6;
    std::string statData = "";

    while (remainingTries != 0) {
        std::cout << "Your guess: ";

        std::string attempt;
        std::cin >> attempt;
        attempt = strtoupper(attempt);
        solved = checkAttempt(solution, attempt);

        statData += solution + "," + attempt + "," + (solved ? "1" : "0") + "\n";

        if (solved) {
            break;
        }

        remainingTries--;
    }

    std::cout << std::endl;

    if (solved) {
        std::cout << "Splendid! You win!" << std::endl;
    } else {
        std::cout << "The word was: " << solution << "\n\nBetter luck next time!" << std::endl;
    }

    std::cout << std::endl;

    std::ofstream file;
    file.open("stats.txt", std::ios::app);
    file << statData;
    file.close();
}

void showTutorial() {
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
    std::cout << green(" --- ") << " ---  ---  ---  --- " << std::endl;
    std::cout << green("| W |") << "| E || A || R || Y |" << std::endl;
    std::cout << green(" --- ") << " ---  ---  ---  --- " << std::endl;
    std::cout << BOLD << "W" << RESET << " is in the word and in the correct spot." << std::endl;
    std::cout << std::endl;
    std::cout << " --- " << yellow(" --- ") << " ---  ---  --- " << std::endl;
    std::cout << "| P |" << yellow("| I |") << "| L || L || S |" << std::endl;
    std::cout << " --- " << yellow(" --- ") << " ---  ---  --- " << std::endl;
    std::cout << BOLD << "I" << RESET << " is in the word and in the correct spot." << std::endl;
    std::cout << std::endl;
    std::cout << " ---  ---  --- " << gray(" --- ") << " --- " << std::endl;
    std::cout << "| V || A || G |" << gray("| U |") << "| E | " << std::endl;
    std::cout << " ---  ---  --- " << gray(" --- ") << " --- " << std::endl;
    std::cout << BOLD << "U" << RESET << " is in the word and in the correct spot." << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
}

void showStatistics() {
    std::vector<Statistic> stats = getStatistics();
    std::cout << "==========================" << std::endl;
    std::cout << "    STATISTICS SUMMARY" << std::endl;
    std::cout << "==========================" << std::endl;
    std::cout << "Times Played:" << std::setw(13) << std::right << stats.size() << std::endl;
    std::cout << "Average Attempts:" << std::setw(9) << std::right << "4" << std::endl;
    std::cout << "Win Percentage:" << std::setw(11) << std::right << "83.3%" << std::endl;
    std::cout << "Current Streak:" << std::setw(11) << std::right << "5" << std::endl;
    std::cout << "Longest Streak:" << std::setw(11) << std::right << "5" << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << "--------------------------" << std::endl;
    std::cout << "WORD     ATTEMPTS      WIN" << std::endl;
    std::cout << "--------------------------" << std::endl;
    std::cout << "ABOVE" << std::setw(12) << "4" << std::setw(9) << std::right << "Yes" << std::endl;
    std::cout << "ABOVE           4      Yes" << std::endl;
    std::cout << "ABOVE           4      Yes" << std::endl;
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
                showTutorial();
                break;
            case 3:
                showStatistics();
                break;
            case 4:
                clearStatistics();
                showStatistics();
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
