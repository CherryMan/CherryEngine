#pragma once

#include <cstddef>
#include <string>

#include <CherryEngine/state.h>


class StateMachine {

public:

    void setmap(const StateMap &stm);
    void start(const std::size_t st_index);
    void start(const std::string &st_name);
    void next_state();
    void change_state(const std::string &st_name);

private:

    StateMap st_map;
    std::size_t current_index;

};
