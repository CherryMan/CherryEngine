#include "base_state.h"

#include <iostream>
#include <thread>
#include <chrono>

void BaseState::render() {
    std::cout << ++count << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
}
