#include <iostream>
#include "Pyramid.h"

int main() {
    int height;
    std::cout << "Enter the height of the pyramid: ";
    std::cin >> height;

    Pyramid pyramid;
    pyramid.setHeight(height);
    pyramid.displayPyramid();

    return 0;
}
