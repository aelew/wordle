#ifndef GAME_H
#define GAME_H

#include <iostream>
#include "utils.h"

struct Game {
    void play() {
        clearKeyData();

        // Get words from `words.txt`
        std::vector<std::string> words = getWords();
        if (words.size() == 0) {
            std::cerr << "Your words.txt file does not exist or has no words to choose from!" << std::endl;
            return;
        }

        // Get a random index in the words vector
        int randomWordIndex = getRandomNumber(0, words.size() - 1);

        // Select a random word
        // std::string solution = strtoupper(words[randomWordIndex]);
        std::string solution = "SOLVE";

        bool solved = false;
        int remainingTries = 6;
        std::string statData = "";

        while (remainingTries != 0) {
            std::cout << "Your guess: ";

            std::string attempt;
            std::cin >> attempt;
            attempt = strtoupper(attempt);

            bool valid = false;

            // Search words.txt and allowed.txt to see if the guess is a valid 5-letter word
            for (int i = 0; i < words.size(); i++) {
                if (attempt == strtoupper(words[i])) {
                    valid = true;
                    break;
                }
            }
            std::vector<std::string> allowedWords = getAllowedWords();
            for (int i = 0; i < allowedWords.size(); i++) {
                if (attempt == strtoupper(allowedWords[i])) {
                    valid = true;
                    break;
                }
            }

            if (valid) {
                solved = checkAttempt(solution, attempt);
                statData += solution + "," + attempt + "," + (solved ? "1" : "0") + "\n";
                if (solved) {
                    break;
                }
                remainingTries--;
            } else {
                std::cout << "That doesn't seem like a valid word. Try again!" << std::endl;
            }
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
