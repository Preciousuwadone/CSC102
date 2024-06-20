#pragma once

#include <iostream>
#include <cmath>

class Pyramid {
private:
    int height;
    char symbol;

public:
    Pyramid(int h, char s) : height(h), symbol(s) {}

    void draw(int scale) {
        int scaled_height = static_cast<int>(round(height * scale));
        for (int i = 1; i <= scaled_height; ++i) {
            for (int j = 1; j <= scaled_height - i; ++j) {
                std::cout << " ";
            }
            for (int j = 1; j <= 2 * i - 1; ++j) {
                std::cout << symbol;
            }
            std::cout << std::endl;
        }
    }
};
