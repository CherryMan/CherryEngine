#pragma once


#include <functional>
#include <initializer_list>
#include <map>
#include <memory>
#include <string>
#include <utility>


// TODO find cleaner solution
// CB should be isolated under a namespace somehow
#define CB(fn) [&]() { fn(); }


// state_fn is a pointer to a state method
using state_fn = std::function<void()>;


class State;
class StateMap;
class StateImpl; // internal implementation


class State {

    friend class StateMap;

public:

    // Create a new substate
    virtual void substate(State &subst) final;

    // Run the state after its configuration
    virtual void start() final;

    // Wait for substates and threads to terminate
    virtual void wait() const final;

    // Stop the state, used for switching
    virtual void stop() final;

    // Switch to the next state in the ordering under the StateMap
    virtual void next_state() final;

    // Switch to a specific state defined under the StateMap
    virtual void change_state(const std::string &st_name) final;


protected:

    // Add a coroutine
    // If tickrate is 0, loop is as fast as possible
    virtual void loop(state_fn fn, const int tickrate) final;


private:

    // Internal implementation
    StateImpl* d_ptr;

};


class StateMap {

public:

    StateMap() = delete;
    StateMap(std::initializer_list<std::pair<const std::string&, State&> > init);

private:

    std::map<std::string, StateImpl&> priv_map;
};
