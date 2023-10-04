#include <iostream>
#include <fstream>
#include <vector>
#include "utils.h"

using namespace std;


bool contains(vector<int> numbers, int value) {
    for (int i = 0; i < numbers.size(); i++) {
        if (numbers[i] == value) {
            return true;
        }
    }
    return false;
}

int main(int argc, char* argv[]) {
    // Get words from `words.txt`
    vector<string> words = get_words();
    if (words.size() == 0) {
        cerr << "Your words.txt file does not exist or has no words to choose from!" << endl;
        return 1;
    }

    // Get a random index in the words vector
    int randomWordIndex = get_random_number(0, words.size() - 1);

    // Select a random word
    string solution = strtoupper(words[randomWordIndex]);

    bool solved = false;
    int remainingTries = 6;

    while (remainingTries != 0) {
        string solutionTemp = solution;

        string attempt;
        cin >> attempt;

        attempt = strtoupper(attempt);
        int correctCount = 0;

        vector<int> greenPos;
        vector<int> yellowPos;

        for (int i = 0; i < attempt.length(); i++) {
            if (attempt[i] == solutionTemp[i]) {
                solutionTemp[i] = '-';
                greenPos.push_back(i);
                correctCount++;
            }
        }

        for (int i = 0; i < attempt.length(); i++) {
            int pos = contains(solutionTemp, attempt[i]);
            if (pos != -1) {
                yellowPos.push_back(i);
            }
        }

        for (int i = 0; i < attempt.length(); i++) {
            if (contains(greenPos, i)) {
                cout << green(attempt[i]) << " ";
            } else if (contains(yellowPos, i)) {
                cout << yellow(attempt[i]) << " ";
            } else {
                cout << gray(attempt[i]) << " ";
            }
        }

        cout << endl;

        if (correctCount == solution.length()) {
            solved = true;
            break;
        }

        remainingTries--;
    }

    if (solved) {
        cout << "Splendid!" << endl;
    } else {
        cout << "The word was: " << solution << "\n\nBetter luck next time!" << endl;
    }

    return 0;
}
