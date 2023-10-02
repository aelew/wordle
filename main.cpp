#include <iostream>
#include "utils.h"

using namespace std;

int main(int argc, char* argv[]) {
    // TODO: select this randomly from the words.txt
    string solution = "SLATE";

    string attempt;
    cin >> attempt;

    cout << green(attempt[0]) << " ";
    cout << yellow(attempt[1]) << " ";
    cout << gray(attempt[2]) << " ";
    cout << endl;

    return 0;
}
