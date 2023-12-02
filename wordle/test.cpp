#include <igloo/igloo.h>
#include "utils.h"

using namespace igloo;

Context(WordleGame) {
    Spec(AllCorrectColoredGuess) {
        std::vector<std::string> result = getColoredGuess("SOLVE", "SOLVE");
        Assert::That(result[0], Equals(green(" --- ") + green(" --- ") + green(" --- ") + green(" --- ") + green(" --- ")));
        Assert::That(result[1], Equals(green("| S |") + green("| O |") + green("| L |") + green("| V |") + green("| E |")));
        Assert::That(result[2], Equals(green(" --- ") + green(" --- ") + green(" --- ") + green(" --- ") + green(" --- ")));
    }
    Spec(PartiallyCorrectColoredGuess) {
        std::vector<std::string> result = getColoredGuess("SOLVE", "STOLE");
        Assert::That(result[0], Equals(green(" --- ") + gray(" --- ") + yellow(" --- ") + yellow(" --- ") + green(" --- ")));
        Assert::That(result[1], Equals(green("| S |") + gray("| T |") + yellow("| O |") + yellow("| L |") + green("| E |")));
        Assert::That(result[2], Equals(green(" --- ") + gray(" --- ") + yellow(" --- ") + yellow(" --- ") + green(" --- ")));
    }
    Spec(OnlyWrongPositionColoredGuess) {
        std::vector<std::string> result = getColoredGuess("SOLVE", "PEARL");
        Assert::That(result[0], Equals(gray(" --- ") + yellow(" --- ") + gray(" --- ") + gray(" --- ") + yellow(" --- ")));
        Assert::That(result[1], Equals(gray("| P |") + yellow("| E |") + gray("| A |") + gray("| R |") + yellow("| L |")));
        Assert::That(result[2], Equals(gray(" --- ") + yellow(" --- ") + gray(" --- ") + gray(" --- ") + yellow(" --- ")));
    }
    Spec(NoMatchingLettersColoredGuess) {
        std::vector<std::string> result = getColoredGuess("SOLVE", "FRUIT");
        Assert::That(result[0], Equals(gray(" --- ") + gray(" --- ") + gray(" --- ") + gray(" --- ") + gray(" --- ")));
        Assert::That(result[1], Equals(gray("| F |") + gray("| R |") + gray("| U |") + gray("| I |") + gray("| T |")));
        Assert::That(result[2], Equals(gray(" --- ") + gray(" --- ") + gray(" --- ") + gray(" --- ") + gray(" --- ")));
    }
};

int main(int argc, const char* argv[]) {
    return TestRunner::RunAllTests(argc, argv);
}
