#include <CherryEngine/state.h>

#include <thread>


void State::loop(State::state_fn fn, int tickrate) {
    
    loops[fn] = tickrate;

}

void State::substate(State &subst) {
    
    substates.push_back(&subst)
}

void  State::run() {

    // Init each loop in its own thread
    for (auto &lp : loops) {
        //TODO
    }
    
    // Run each substate
    for (auto &st_ptr : substates) {
        st_ptr->run();
    }
}
