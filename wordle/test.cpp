#include <igloo/igloo.h>
#include "utils.h"

using namespace igloo;

std::string exec(std::string command) {
   char buffer[128];
   std::string result = "";

   // Open pipe to file
   FILE* pipe = popen((command + " 2>&1").c_str(), "r");
   if (!pipe) {
      return "popen failed!";
   }

   // read till end of process:
   while (!feof(pipe)) {

      // use buffer to read and add to result
      if (fgets(buffer, 128, pipe) != NULL)
         result += buffer;
   }

   pclose(pipe);
   result.erase(result.find_last_not_of(" \t\n\r\f\v") + 1);
   return result;
}

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
