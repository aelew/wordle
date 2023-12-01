#ifndef GAME_H
#define GAME_H

#include <iostream>
#include "utils.h"

struct Game {
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
};

#endif
