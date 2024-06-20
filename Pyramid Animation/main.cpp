#include "pyramid.h"
#include <chrono>
#include <thread>

int main() {
    Pyramid pyramid(5, '*');
    float scale = 1.0f;
    bool increasing = true;

    while (true) {
        pyramid.draw(scale);

        // Adjust scaling
        if (increasing)
            scale += 0.1f;
        else
            scale -= 0.1f;

        // Reverse scaling direction
        if (scale >= 2.0f || scale <= 0.5f)
            increasing = !increasing;

        std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Adjust speed
        system("CLS"); // Clear console
    }

    return 0;
}
