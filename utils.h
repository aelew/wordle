#ifndef UTILS_H
#define UTILS_H

#define YELLOW "\033[33m"
#define GRAY "\033[90m"
#define GREEN "\033[32m"

#define BOLD "\033[1m"
#define RESET "\033[0m"

#include <string>
#include <vector>
#include <fstream>
#include <iostream>

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

bool checkAttempt(std::string solution, std::string attempt) {
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
        std::string firstLineText = " --- ";

        std::string secondLineText = "| ";
        secondLineText += attempt[i];
        secondLineText += " |";

        std::string thirdLineText = " --- ";

        if (contains(greenPos, i)) {
            firstLine += green(firstLineText);
            secondLine += green(secondLineText);
            thirdLine += green(thirdLineText);
        } else if (contains(yellowPos, i)) {
            firstLine += yellow(firstLineText);
            secondLine += yellow(secondLineText);
            thirdLine += yellow(thirdLineText);
        } else {
            firstLine += gray(firstLineText);
            secondLine += gray(secondLineText);
            thirdLine += gray(thirdLineText);
        }
    }

    std::cout << firstLine << std::endl;
    std::cout << secondLine << std::endl;
    std::cout << thirdLine << std::endl;

    return correctCount == solution.length();
}

#endif
