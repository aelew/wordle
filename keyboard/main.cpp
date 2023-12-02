#include <unistd.h>
#include <iostream>
#include <vector>
#include "../wordle/utils.h"

using namespace std;

int main(int argc, char* argv[]) {
    while (true) {
        system("clear");
        for (int i = 0; i < keyboardRows.size(); i++) {
            vector<char> row = keyboardRows[i];
            int rowLength = row.size();

            for (int j = 0; j < 3; j++) {
                // Add extra padding to the left
                if (i == 1) {
                    cout << "  ";
                } else if (i == 2) {
                    cout << "       ";
                }

                for (int k = 0; k < row.size(); k++) {
                    char letter = row[k];
                    cout << getKeyColor(letter);
                    if (j == 1) {
                        cout << "| " << letter << " |";
                    } else {
                        cout << " --- ";
                    }
                }

                cout << RESET << endl;
            }
        }
        sleep(1);
    }
    return 0;
}
