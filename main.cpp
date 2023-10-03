#include <iostream>
#include <fstream>
#include <vector>
#include "utils.h"

using namespace std;

int contains(string word, char letter) {
    for (int i = 0; i < word.length(); i++) {
        if (word[i] == letter) {
            return i;
        }
    }
    return -1;
}

int main(int argc, char* argv[]) {
    // Get words from `words.txt`
    vector<string> words = get_words();
    if (words.size() == 0) {
        cerr << "Your words.txt file does not exist or has no words to choose from!" << endl;
        return 1;
    }
    
    int randomWordIndex = get_random_number(0, words.size() - 1);

    // Select a random word
    string solution = strtoupper(words[randomWordIndex]);
    string originalSolution = solution;

    string attempt;
    cin >> attempt;

    attempt = strtoupper(attempt);

    for (int i = 0; i < attempt.length(); i++) {
        if (attempt[i] == solution[i]) {
            solution[i] = '-';
            cout << green(attempt[i]) << " ";
        } else {
            int pos = contains(solution, attempt[i]);
            if (pos != -1) {
                cout << yellow(attempt[i]) << " ";
                solution[pos] = '-';
            } else {
                cout << gray(attempt[i]) << " ";
            }
        }
    }
    cout << endl;

    cout << originalSolution << endl;

    return 0;
}
