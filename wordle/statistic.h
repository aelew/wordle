#ifndef STATISTIC_H
#define STATISTIC_H

#include <iostream>

struct Statistic {
    std::string word, attempt;
    bool won;
    Statistic(std::string word, std::string attempt, bool won) {
        this->word = word;
        this->attempt = attempt;
        this->won = won;
    }
};

#endif
