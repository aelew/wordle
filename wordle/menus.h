#ifndef MENUS_H
#define MENUS_H

#include <map>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>

#include "utils.h"
#include "statistic.h"
#include "game.h"

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
    int statCount = stats.size();
    
    // Calculate attempts/whether player has won for each word
    std::map<std::string, std::pair<int, bool>> wordAttemptMap; // <word, <attempts, hasWon>>
    for (int i = 0; i < statCount; i++) {
        Statistic stat = stats[i];
        std::pair<int, bool>& value = wordAttemptMap[stat.word];
        value.first++;
        if (stat.won) {
            value.second = true;
        }
    }

    // Calculate average attempts
    int words = 0;
    int attempts = 0;
    for (const auto entry : wordAttemptMap) {
        // Only consider words that were solved at least once
        if (entry.second.second) {
            attempts += entry.second.first;
            words++;
        }
    }
    int averageAttempts = words == 0 ? 0 : attempts / words;

    // Calculate win rate
    int wins = 0;
    for (int i = 0; i < statCount; i++) {
        if (stats[i].won) {
            wins++;
        }
    }
    float winRate = statCount == 0 ? 0 : wins / ((float) statCount); // cast to float to prevent integer division

    // Calculate current streak
    int currentStreak = 0;
    for (int i = statCount - 1; i >= 0; i--) {
        if (stats[i].won) {
            currentStreak++;
        } else {
            break;
        }
    }
    
    // Calculate longest streak
    int streak = 0;
    int longestStreak = 0;
    for (int i = 0; i < statCount; i++) {
        if (stats[i].won) {
            streak++;
        } else {
            if (streak > longestStreak) {
                longestStreak = streak;
            }
            streak = 0;
        }
    }
    if (streak > longestStreak) {
        // needed for if the player never loses
        longestStreak = streak;
    }

    std::cout << "==========================" << std::endl;
    std::cout << "    STATISTICS SUMMARY" << std::endl;
    std::cout << "==========================" << std::endl;
    std::cout << "Times Played:" << std::setw(13) << std::right << stats.size() << std::endl;
    std::cout << "Average Attempts:" << std::setw(9) << std::right << averageAttempts << std::endl;
    std::cout << "Win Percentage:" << std::setw(10) << std::right << std::fixed << std::setprecision(1) << winRate * 100 << "%" << std::endl;
    std::cout << "Current Streak:" << std::setw(11) << std::right << currentStreak << std::endl;
    std::cout << "Longest Streak:" << std::setw(11) << std::right << longestStreak << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << "--------------------------" << std::endl;
    std::cout << "WORD     ATTEMPTS      WIN" << std::endl;
    std::cout << "--------------------------" << std::endl;
    for (const auto& entry : wordAttemptMap) {
        std::cout << entry.first << std::setw(12) << entry.second.first << std::setw(9) << std::right << (entry.second.second ? "Yes" : "No") << std::endl;
    }
    std::cout << std::endl;
    std::cout << std::endl;
}

void showMainMenu() {
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
                Game game;
                game.play();
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
