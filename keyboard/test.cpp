#include <igloo/igloo.h>
#include "../wordle/utils.h"

using namespace igloo;

Context(WordleKeyboard) {
    static void SetUpContext() {
        std::ofstream file;
        file.open("../keys.txt", std::ios::trunc);
        file << "Q," << RESET << "\nW," << RESET << "\nE," << GREEN << "\nR," << GRAY << "\nT," << GRAY << "\nY," << RESET << "\nU," << RESET << "\nI," << RESET << "\nO," << YELLOW << "\nP," << GRAY 
            << "\nA," << GRAY << "\nS," << GREEN << "\nD," << RESET << "\nF," << RESET << "\nG," << RESET << "\nH," << RESET << "\nJ," << RESET << "\nK," << RESET << "\nL," << YELLOW 
            << "\nZ," << RESET << "\nX," << RESET << "\nC," << GRAY << "\nV," << RESET << "\nB," << RESET << "\nN," << RESET << "\nM," << RESET << "";
        file.close();
    }
    static void TearDownContext() {
        clearFile("../keys.txt");
    }
    Spec(FirstRowColors) {
        Assert::That(getKeyColor('Q'), Equals(RESET));
        Assert::That(getKeyColor('E'), Equals(GREEN));
        Assert::That(getKeyColor('R'), Equals(GRAY));
        Assert::That(getKeyColor('T'), Equals(GRAY));
        Assert::That(getKeyColor('O'), Equals(YELLOW));
        Assert::That(getKeyColor('P'), Equals(GRAY));
    }
    Spec(SecondRowColors) {
        Assert::That(getKeyColor('A'), Equals(GRAY));
        Assert::That(getKeyColor('S'), Equals(GREEN));
        Assert::That(getKeyColor('F'), Equals(RESET));
        Assert::That(getKeyColor('L'), Equals(YELLOW));
    }
    Spec(ThirdRowColors) {
        Assert::That(getKeyColor('Z'), Equals(RESET));
        Assert::That(getKeyColor('C'), Equals(GRAY));
        Assert::That(getKeyColor('N'), Equals(RESET));
        Assert::That(getKeyColor('M'), Equals(RESET));
    }
};

int main(int argc, const char* argv[]) {
    return TestRunner::RunAllTests(argc, argv);
}
