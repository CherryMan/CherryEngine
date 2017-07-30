#include "mystates.h"

#include <iostream>
#include <thread>
#include <chrono>

void BaseState::render() {
    std::cout << "BASE count: " << countdown-- << std::endl;

    if (countdown == 0) {
        std::cerr << "BASE Done!"<< std::endl;
        countdown = 5;

        next_state();
    }
}

void SubBaseState::runme() {
    std::cout << "SUBB count: " << count-- << std::endl;

    if (count == 0) {
        std::cout << "SUBB Done!" << std::endl;
        count = 5;

        next_state();
    }
}

void NextState::run() {
    std::cout << "NEXT count: " << count-- << std::endl;

    if (count == 0) {
        std::cerr << "NEXT Done!" << std::endl;
        count = 5;

        change_state("base");
    }
}
