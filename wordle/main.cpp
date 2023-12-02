#include "wordle.h"

int main(int argc, char* argv[]) {
    Wordle wordle;
    while (true) {
        wordle.printMainMenu();

        int option;
        std::cin >> option;

        switch (option) {
            case 1:
                wordle.play();
                break;
            case 2:
                wordle.printTutorial();
                break;
            case 3:
                wordle.printStatistics();
                break;
            case 4:
                clearFile("stats.txt");
                wordle.printStatistics();
                break;
            case 5:
                std::cout << "Goodbye!" << std::endl;
                return 0;
            default:
                std::cerr << "Uh oh! You didn't enter a valid option." << std::endl;
                // Reset the fail state of cin
                std::cin.clear();
                std::cin.ignore();
                break;
        }

        if (option > 0 && option < 5) {
            std::cout << "Press [enter] to continue" << std::endl;
            std::cin.ignore();
            std::cin.get();
        }
    }
}
