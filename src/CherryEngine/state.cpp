#include <CherryEngine/state.h>

#include "../state/state_impl.h"
#include "../state/state_machine.h"

#include <initializer_list>
#include <iostream>
#include <utility>
#include <thread>


// State definitions
void State::substate(State &subst) { d_ptr->substate(*(subst.d_ptr)); }
void State::start() { d_ptr->start(); }
void State::wait() const { d_ptr->wait(); }
void State::stop() { d_ptr->stop(); }
void State::next_state() { d_ptr->next_state(); }
void State::change_state(const std::string &st_name) { d_ptr->change_state(st_name); }
void State::loop(state_fn fn, const int tickrate) { d_ptr->loop(fn, tickrate); }


// StateMap definitions
StateMap::StateMap(std::initializer_list<std::pair<const std::string&, State&>> init) {

    /*
    for (auto &it : init) {
        priv_map[it.first] = *(it.second.d_ptr;
    }
    */

}
