#pragma once


#include <functional>
#include <map>
#include <thread>
#include <tuple>
#include <utility>
#include <vector>

// TODO find cleaner solution
// CB should be isolated under a namespace somehow
#define CB(fn) [&]() { fn(); }

class State;

class State {

public:

    // Create a new substate
    virtual void substate(State &subst) final;

    // Run the state after its configuration
    virtual void run() final;

    // Wait for substates and threads to terminate
    virtual void wait() const final;


protected:

    // state_fn is a pointer to a state method
    //using state_fn = void (*)();
    using state_fn = std::function<void()>;

    struct loop_info {
         state_fn fn;
         int tickrate;
         bool running = false;
         std::thread *thr;
    };

    // These store the loops tickrates, threads and substates
    std::vector<loop_info> loops;
    std::vector<State*> substates;

    // Add a coroutine
    // If tickrate is 0, loop is as fast as possible
    virtual void loop(state_fn fn, const int tickrate) final;

};
