#ifndef UTILS_H
#define UTILS_H

#define GREEN_BG "\033[42;30m"
#define YELLOW_BG "\033[43;30m"
#define GRAY_BG "\033[47;30m"
#define RESET "\033[0m"

#include <string>
#include <vector>
#include <fstream>
#include <iostream>

std::vector<std::string> get_words() {
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

int get_random_number(int min, int max) {
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

std::string green(char letter) {
    std::string result = GREEN_BG;
    result += letter;
    result += RESET;
    return result;
}

std::string yellow(char letter) {
    std::string result = YELLOW_BG;
    result += letter;
    result += RESET;
    return result;
}

std::string gray(char letter) {
    std::string result = GRAY_BG;
    result += letter;
    result += RESET;
    return result;
}

bool check_attempt(std::string solution, std::string attempt) {
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

    for (int i = 0; i < attempt.length(); i++) {
        if (contains(greenPos, i)) {
            std::cout << green(attempt[i]);
        } else if (contains(yellowPos, i)) {
            std::cout << yellow(attempt[i]);
        } else {
            std::cout << gray(attempt[i]);
        }
        if (i < attempt.length() - 1) {
            std::cout << " ";
        }
    }

    std::cout << std::endl;
    return correctCount == solution.length();
}

#endif
