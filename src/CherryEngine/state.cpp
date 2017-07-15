#include <CherryEngine/state.h>

#include <iostream>
#include <thread>

#include <GLFW/glfw3.h>


void State::loop(State::state_fn fn, const int tickrate) {

    loop_info lp {fn, tickrate};
    
    loops.push_back(lp);

}

void State::substate(State &subst) {
    
    substates.push_back(&subst);
}

void State::run() {

    // Init each loop in its own thread
    for (auto &lp : loops) {
        lp.thr = new std::thread([&lp, this]() -> void {

                // These variables count ticks
                const double skip_ticks = 1 / lp.tickrate;
                double next_tick = glfwGetTime();

                // Set loop as running
                lp.running = true;

                // Main loop
                while (lp.running) {

                    // Wait for next tick
                    while (glfwGetTime() > next_tick) next_tick += skip_ticks;

                    // Function to loop over
                    lp.fn();
                }
        });
    }
    
    // Run each substate
    for (auto &st_ptr : substates) {
        st_ptr->run();
    }
}

void State::wait() const {

    for (auto &lp : loops) {
        lp.thr->join();
    }
    
    for (auto &st_ptr : substates) {
        st_ptr->wait();
    }
}
