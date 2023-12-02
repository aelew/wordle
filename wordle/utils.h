#ifndef UTILS_H
#define UTILS_H

#define YELLOW "\033[33m"
#define GRAY "\033[90m"
#define GREEN "\033[32m"

#define BOLD "\033[1m"
#define RESET "\033[0m"

#include <ostream>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include "statistic.h"
#include "key.h"

std::vector<std::vector<char>> keyboardRows = {
    { 'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P' },
    { 'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L' },
    { 'Z', 'X', 'C', 'V', 'B', 'N', 'M' }
};

std::vector<std::string> getWords() {
    std::vector<std::string> words;

    std::ifstream file;
    file.open("words.txt", std::ios::in);
    if (!file.is_open()) {
        return words;
    }

    std::string word;
    while (getline(file, word)) {
        words.push_back(word);
    }

    file.close();
    return words;
}

std::vector<std::string> getAllowedWords() {
    std::vector<std::string> words;

    std::ifstream file;
    file.open("allowed.txt", std::ios::in);
    if (!file.is_open()) {
        return words;
    }

    std::string word;
    while (getline(file, word)) {
        words.push_back(word);
    }

    file.close();
    return words;
}

std::vector<std::string> split(std::string str, char delimiter) {
    std::vector<std::string> parts;
    std::string currentPart = ""; 
    for (int i = 0; i < str.size(); i++) {
        if (str[i] == delimiter) {
            if (currentPart != "") {
                parts.push_back(currentPart);
                currentPart = "";
            } 
            continue;
        }
        currentPart += str[i];
    }
    if (currentPart.size() != 0) {
        parts.push_back(currentPart);
    }
    return parts;
}

std::vector<Statistic> getStatistics() {
    std::vector<Statistic> stats;

    std::ifstream file;
    file.open("stats.txt", std::ios::in);
    if (!file.is_open()) {
        return stats;
    }

    std::string line;
    while (getline(file, line)) {
        std::vector<std::string> parts = split(line, ',');
        Statistic stat(parts[0], parts[1], stoi(parts[2]));
        stats.push_back(stat);
    }

    file.close();
    return stats;
}

void clearStatistics() {
    std::ofstream file;
    file.open("stats.txt", std::ofstream::trunc);
    file.close();
}

std::vector<Key> getKeys() {
    std::vector<Key> keys;

    std::ifstream file;
    file.open("../keys.txt", std::ios::in);
    if (!file.is_open()) {
        return keys;
    }

    std::string line;
    while (getline(file, line)) {
        std::vector<std::string> parts = split(line, ',');
        Key key(parts[0][0], parts[1]);
        keys.push_back(key);
    }

    file.close();
    return keys;
}

void clearKeyData() {
    std::ofstream file;
    file.open("../keys.txt", std::ofstream::trunc);
    file.close();
}

std::string getKeyColor(char letter) {
    std::vector<Key> keys = getKeys();
    for (int i = 0; i < keys.size(); i++) {
        Key key = keys[i];
        if (key.letter == letter) {
            return key.color;
        }
    }
    return RESET;
}

int getRandomNumber(int min, int max) {
    srand((unsigned) time(NULL));
    int range = max - min + 1;
    return min + (rand() % range);
}

std::string strtoupper(std::string str) {
    for (int i = 0; i < str.length(); i++) {
        str[i] = toupper(str[i]);
    }
    return str;
}

int contains(std::string word, char letter) {
    for (int i = 0; i < word.length(); i++) {
        if (word[i] == letter) {
            return i;
        }
    }
    return -1;
}

bool contains(std::vector<int> numbers, int value) {
    for (int i = 0; i < numbers.size(); i++) {
        if (numbers[i] == value) {
            return true;
        }
    }
    return false;
}

std::string green(std::string text) {
    std::string result = GREEN;
    result += text;
    result += RESET;
    return result;
}

std::string yellow(std::string text) {
    std::string result = YELLOW;
    result += text;
    result += RESET;
    return result;
}

std::string gray(std::string text) {
    std::string result = GRAY;
    result += text;
    result += RESET;
    return result;
}

void updateKeyState(char letter, std::string color) {
    std::vector<Key> keys = getKeys();
    if (keys.size() == 0) {
        for (int i = 0; i < keyboardRows.size(); i++) {
            for (int j = 0; j < keyboardRows[i].size(); j++) {
                char letter = keyboardRows[i][j];
                keys.push_back(Key(letter, RESET));
            }
        }
    }

    std::ofstream file;
    file.open("../keys.txt", std::ios::trunc);

    for (int i = 0; i < keys.size(); i++) {
        Key key = keys[i];
        if (key.letter == letter) {
            key.color = color;
        }
        file << key.letter << ',' << key.color << std::endl;
    }

    file.close();
}

std::vector<std::string> getColoredGuess(std::string solution, std::string attempt) {
    int correctCount = 0;

    std::vector<int> greenPos;
    std::vector<int> yellowPos;

    for (int i = 0; i < attempt.length(); i++) {
        if (attempt[i] == solution[i]) {
            solution[i] = '-';
            greenPos.push_back(i);
            correctCount++;
        }
    }

    for (int i = 0; i < attempt.length(); i++) {
        int pos = contains(solution, attempt[i]);
        if (pos != -1) {
            yellowPos.push_back(i);
        }
    }

    std::string firstLine = "", secondLine = "", thirdLine = "";

    for (int i = 0; i < attempt.length(); i++) {
        char letter = attempt[i];

        std::string firstLineText = " --- ";

        std::string secondLineText = "| ";
        secondLineText += letter;
        secondLineText += " |";

        std::string thirdLineText = " --- ";

        if (contains(greenPos, i)) {
            firstLine += green(firstLineText);
            secondLine += green(secondLineText);
            thirdLine += green(thirdLineText);
            updateKeyState(letter, GREEN);
        } else if (contains(yellowPos, i)) {
            firstLine += yellow(firstLineText);
            secondLine += yellow(secondLineText);
            thirdLine += yellow(thirdLineText);
            updateKeyState(letter, YELLOW);
        } else {
            firstLine += gray(firstLineText);
            secondLine += gray(secondLineText);
            thirdLine += gray(thirdLineText);
            updateKeyState(letter, GRAY);
        }
    }

    return { firstLine, secondLine, thirdLine };
}

#endif
