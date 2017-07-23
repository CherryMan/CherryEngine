#include "state_impl.h"

#include <GLFW/glfw3.h>


// StateImpl definitions
void StateImpl::substate(StateImpl &subst) {

    substates.push_back(&subst);
}

void StateImpl::start() {

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
        st_ptr->start();
    }
}

void StateImpl::wait() const {

    for (auto &lp : loops) {
        lp.thr->join();
    }

    for (auto &st_ptr : substates) {
        st_ptr->wait();
    }
}

void StateImpl::stop() {

    for (auto &lp : loops) {
        lp.running = false;
    }

    for (auto &st_ptr : substates) {
        st_ptr->stop();
    }

}

void StateImpl::next_state() {

    st_machine_ptr->next_state();

}

void StateImpl::change_state(const std::string &st_name) {

    st_machine_ptr->change_state(st_name);

}

void StateImpl::loop(state_fn fn, const int tickrate) {

    loop_info lp {fn, tickrate};
    loops.push_back(lp);

}

