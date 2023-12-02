#ifndef KEY_H
#define KEY_H

#include <iostream>

struct Key {
    char letter;
    std::string color;
    Key(char letter, std::string color) {
        this->letter = letter;
        this->color = color;
    }
};

#endif
