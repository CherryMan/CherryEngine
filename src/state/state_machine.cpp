#include "state_machine.h"

#include <cstddef>
#include <string>

#include <CherryEngine/state.h>

#include "state_impl.h"


void StateMachine::setmap(const StateMap &stm) {

    st_map = stm;


}

void StateMachine::start(const std::size_t st_index) {

    st_map[st_index]->st_machine_ptr = this;
    current_index = st_index;

    st_map[st_index]->start();
    st_map[st_index]->wait();

}

void StateMachine::start(const std::string &st_name) {
    
    start(st_map.get_index(st_name));

}

void StateMachine::next_state() {

    st_map[current_index]->stop(); 
    start(current_index + 1);

}

void StateMachine::change_state(const std::string &st_name) {

    st_map[current_index]->stop();
    start(st_name);

}
