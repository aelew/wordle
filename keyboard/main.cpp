#include <iostream>
#include <vector>

using namespace std;

string getKeyData(int line, char letter) {
    if (line == 1) {
        std::string data = "";
        data += "| ";
        data += letter;
        data += " |";
        return data;
    }
    return " --- ";
}

int main(int argc, char* argv[]) {
    vector<vector<char>> rows = {
        { 'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P' },
        { 'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L' },
        { 'Z', 'X', 'C', 'V', 'B', 'N', 'M' }
    };

    for (int i = 0; i < rows.size(); i++) {
        vector<char> row = rows[i];
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
                cout << getKeyData(j, letter);
            }

            cout << endl;
        }
    }

    return 0;
}
