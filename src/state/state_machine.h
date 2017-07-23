#pragma once

#include <string>

#include <CherryEngine/state.h>


class StateMachine {

public:

    void setmap(const StateMap &stm);
    void start(const std::string &stname);
    void next_state();
    void change_state(const std::string &st_name);

private:

    StateMap st_map;

};
