#include "mystates.h"

#include <iostream>
#include <thread>
#include <chrono>

void BaseState::render() {
    std::cout << "Countdown: " << countdown-- << std::endl;

    if (countdown == 0) {
        std::cout << "Done!" << std::endl;
        countdown = 5;

        next_state();
    }
}

void NextState::run() {
    std::cout << "Countup: " << count++ << std::endl;

    if (count == 5) {
        std::cout << "Done!" << std::endl;
        count = 0;

        change_state("base");
    }
}
