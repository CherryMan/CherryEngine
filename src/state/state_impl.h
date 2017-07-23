#pragma once


#include <functional>
#include <string>
#include <thread>
#include <vector>

#include "state_machine.h"

using state_fn = std::function<void()>;

class StateImpl;

class StateImpl {

public:

    void substate(StateImpl &subst);
    void start();
    void wait() const;
    void stop();
    void next_state();
    void change_state(const std::string &st_name);

    void loop(state_fn fn, const int tickrate);

    // Define a single loop and its properties
    struct loop_info {
         state_fn fn;
         int tickrate;
         bool running = false;
         std::thread *thr;
    };


    // These store the loops tickrates, threads and substates
    std::vector<loop_info> loops;
    std::vector<StateImpl*> substates;

    // Stores the address to the StateMachine holding this State
    StateMachine *st_machine_ptr;

}; // State::StateImpl
 
