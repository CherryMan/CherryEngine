#include "state_impl.h"

#include <iostream>

#include <GLFW/glfw3.h>
#include <CherryEngine/state.h>

#include "state_machine.h"


// StateImpl definitions
StateImpl::~StateImpl() {
    stop();
}

void StateImpl::substate(const StateMap stm) {
    substate_map = std::move(std::make_shared<StateMap>(stm));
}

void StateImpl::start() {

    // Init each loop in its own thread
    for (auto &lp : loops) {

        lp.thr = std::move(new std::thread([&]() -> void {

                // Wait for previous loop to finish
                while (!lp.stopped)
                    ; // null statement

                // These variables count ticks
                const double skip_ticks = 1 / lp.tickrate;
                double next_tick = glfwGetTime();

                // Set vars
                lp.running = true;
                lp.stopped = false;

                // Main loop
                while (lp.running) {

                    // Function to loop over
                    lp.fn();

                    // Update counters
                    next_tick += skip_ticks;

                    // Wait for next tick or for loop to end
                    while (lp.running && glfwGetTime() < next_tick)
                        ; // null statement
                }

                lp.stopped = true;

        })); // lambda; new thread; move
    }
}

void StateImpl::wait() const {

    for (auto &lp : loops) {
        lp.thr->join();
    }
}

void StateImpl::stop() {

    for (auto &lp : loops) {
        lp.running = false;
    }
}

void StateImpl::next_state() {

    st_machine_ptr->next_state();

}

void StateImpl::change_state(const std::string &st_name) {

    st_machine_ptr->change_state(st_name);

}

void StateImpl::loop(state_fn fn, const double tickrate) {

    loop_info lp {fn, tickrate};
    loops.push_back(lp);

}
