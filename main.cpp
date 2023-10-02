#include <iostream>
#include "utils.h"

using namespace std;

int contains(string word, char c) {
    for (int i = 0; i < word.length(); i++) {
        if (word[i] == c) {
            return i;
        }
    }
    return -1;
}

int main(int argc, char* argv[]) {
    // TODO: select this randomly from the words.txt
    string solution = "SLATE";
    string originalSolution = solution;

    string attempt;
    cin >> attempt;

    // cout << green(attempt[0]) << " ";
    // cout << yellow(attempt[1]) << " ";
    // cout << gray(attempt[2]) << " ";
    // cout << endl;

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

    return 0;
}
