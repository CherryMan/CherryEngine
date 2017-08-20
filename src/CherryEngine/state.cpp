#include <CherryEngine/state.h>

#include <algorithm>
#include <cstddef>
#include <initializer_list>
#include <iostream>
#include <iterator>
#include <utility>
#include <thread>

#include <GLFW/glfw3.h>

#include "state/state_machine.h"


// State definitions

/*
State &State::substate(const StateMap stm) { d_ptr->substate(stm); return *this;}
void State::next_state() { d_ptr->next_state(); }
void State::change_state(const std::string &st_name) { d_ptr->change_state(st_name); }
void State::loop(state_fn fn, const double tickrate) { d_ptr->loop(fn, tickrate); }
*/

State::~State() {
    stop();
}

State &State::substate(const StateMap stm) {
    substate_map = std::move(std::make_shared<StateMap>(stm));

    return *this;
}

void State::start() {

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

void State::wait() const {

    for (auto &lp : loops) {
        lp.thr->join();
    }
}

void State::stop() {
    for (auto &lp : loops) {
        lp.running = false;
    }
}

void State::next_state() {
    st_machine_ptr->next_state();
}

void State::change_state(const std::string &st_name) {
    st_machine_ptr->change_state(st_name);
}

void State::loop(state_fn fn, const double tickrate) {

    loop_info lp {fn, tickrate};
    loops.push_back(lp);

}

// StateMap definitions
StateMap::StateMap(std::initializer_list<std::pair<std::string, State&>> init) {

    for (auto &it : init) {
        values.push_back(&it.second);
        keys.push_back(it.first);
    }
}

State *StateMap::operator[](const std::size_t i) {

    // TODO use custom logger instead of cerr
    if (i >= size()) {
        std::cerr << "Accessed StateMap with invalid index of " << i << "\n"
                  << "Possible values are "
                  << 0 << "-" << size() << "\n"
                  << "or the following names: ";

                  for (const auto &s : keys) {
                    std::cerr << s << " ";
                  }

                  std::cerr << std::endl;
    }

    return values[i];
}

State *StateMap::operator[](const std::string& k) {
    return values[get_index(k)];
}

std::size_t StateMap::get_index(const std::string& k) {

    std::size_t r = -1;

    auto it = std::find(keys.cbegin(), keys.cend(), k);

    if (it == keys.end()) {

        // TODO same as last todo, use logger
        std::cerr << "Invalid key of "
                  << k << "\n"
                  << "Possible values are: ";
        for (const auto &s : keys) {
            std::cout << s << " ";
        }

        std::cerr << std::endl;

    } else {
        r =  it - keys.begin();
    }

    return r;
}

std::size_t StateMap::size() {
    return values.size();
}
