#include "state_impl.h"

#include <GLFW/glfw3.h>

#include <CherryEngine/state.h>

#include "state_machine.h"


// StateImpl definitions
StateImpl::~StateImpl() {
    stop();
}

void StateImpl::substate(StateImpl &subst) {
    substates.push_back(&subst);
}

void StateImpl::start() {

    // Init each loop in its own thread
    for (auto &lp : loops) {

        //auto &st = st_ptr;

        lp.thr = std::move(new std::thread([&lp]() -> void {

                // These variables count ticks
                const double skip_ticks = 1 / lp.tickrate;
                double next_tick = glfwGetTime();

                // Set loop as running
                lp.running = true;

                // Main loop
                while (lp.running) {

                    // Update counters
                    next_tick += skip_ticks;

                    // Wait for next tick
                    while (glfwGetTime() < next_tick)
                        ; // null statement

                    // Function to loop over
                    lp.fn();
                }
        })); // lambda; new thread; move
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

void StateImpl::loop(state_fn fn, const double tickrate) {

    loop_info lp {fn, tickrate};
    loops.push_back(lp);

}
