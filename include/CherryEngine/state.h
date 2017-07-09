#pragma once


#include <map>
#include <utility>
#include <vector>


class State;

class State {

public:

    // Used for calling the loop method
    virtual State() = 0;

    // state_ptr is a pointer to a state method
    typedef void (State::*state_fn)();

    // Create coroutine
    virtual void loop(state_fn fn, int tickrate = 0) final;

    // Create a new substate
    virtual void substate(State &subst) final;

    // Run the state after its configuration
    virtual void run() final;

    // Wait for substates and threads to terminate
    virtual void wait() const final;


protected:

    // These store the loops and substates
    std::map<state_fn, int> loops;
    std::vector<State*> substates;
};
