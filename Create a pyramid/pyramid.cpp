#include <iostream>
#include "Pyramid.h"

Pyramid::Pyramid() {
    height = 0;
}

void Pyramid::setHeight(int h) {
    height = h;
}

void Pyramid::displayPyramid() {
    for (int i = 1; i <= height; i++) {
        // Print spaces
        for (int j = 1; j <= height - i; j++)
            std::cout << " ";

        // Print stars
        for (int k = 1; k <= 2 * i - 1; k++)
            std::cout << "*";

        std::cout << std::endl;
    }
}
