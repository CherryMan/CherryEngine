#include "state_machine.h"

#include <string>

#include <CherryEngine/state.h>


void StateMachine::setmap(const StateMap &st_map) {

    this->st_map = st_map;

}

void StateMachine::start(const std::string &st_name) {

}

void StateMachine::next_state() {

}

void StateMachine::change_state(const std::string &st_name) {

}
