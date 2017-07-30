#pragma once

#include <cstddef>
#include <string>

#include <CherryEngine/state.h>


class StateMachine {

public:

    StateMachine() = delete;
    StateMachine(const StateMap stm);

    // Start by index or name
    void start(const std::size_t st_index = 0);
    void start(const std::string &st_name);

    // Switch to next state, called by states
    void next_state();
    void change_state(const std::string &st_name);

    // Stop the current machine completely
    void stop();

private:

    // These two variables share the same index
    StateMap st_map;
    std::vector<std::unique_ptr<StateMachine>> sub_machines;

    // Current index of st_map and sub_machines
    std::size_t current_index = 0;

};
