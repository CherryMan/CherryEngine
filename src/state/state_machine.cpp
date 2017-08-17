#include "state_machine.h"

#include <iostream>
#include <cstddef>
#include <memory>
#include <string>
#include <thread>

#include <CherryEngine/state.h>

#include "state/state_impl.h"


StateMachine::StateMachine(const StateMap stm) {
    st_map = stm;

    // Set each StateMap's parent machine address
    for (std::size_t i = 0; i < st_map.size(); i++){
        st_map[i]->st_machine_ptr = this;

        // Make sure the substate isn't null
        // Then setup the submachine
        if (st_map[i]->substate_map) {
            std::unique_ptr<StateMachine> sbm(
                    new StateMachine(*(st_map[i]->substate_map))
                );
            sub_machines.push_back(std::move(sbm));
        } else {
            std::unique_ptr<StateMachine> sbm;
            sub_machines.push_back(std::move(sbm));
        }
    }
}

void StateMachine::start(const std::size_t st_index) {

    current_index = st_index;

    // Start a submachine in its own thread
    if (sub_machines[current_index]) {
        new std::thread([&]() -> void {
            sub_machines[current_index]->start();
        });
    }

    // Start the State
    st_map[current_index]->start();
}

void StateMachine::start(const std::string &st_name) {
    start(st_map.get_index(st_name));
}

void StateMachine::next_state() {

    stop();

    // Loop back to first state if necessary
    if (current_index + 1 < st_map.size()) {
        start(current_index + 1);
    } else {
        start(0);
    }
}

void StateMachine::change_state(const std::string &st_name) {

    stop();

    start(st_name);
}

void StateMachine::stop() {
    st_map[current_index]->stop();

    if (sub_machines[current_index]) {
        sub_machines[current_index]->stop();
    }
}
