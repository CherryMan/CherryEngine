#pragma once


#include <cstddef>
#include <functional>
#include <initializer_list>
#include <memory>
#include <string>
#include <utility>
#include <vector>


// TODO find cleaner solution
// CB should be isolated under a namespace somehow
#define CB(fn) [&]() { this->fn(); }


// state_fn is a pointer to a state method
using state_fn = std::function<void()>;


class State;
class StateMap;
class StateImpl; // internal implementation


class State {

    friend class StateMap;

public:

    State();

    // Create a new substate
    virtual void substate(State &subst) final;

    // Switch to the next state in the ordering under the StateMap
    virtual void next_state() final;

    // Switch to a specific state defined under the StateMap
    virtual void change_state(const std::string &st_name) final;


protected:

    // Add a coroutine
    // If tickrate is 0, loop is as fast as possible
    virtual void loop(state_fn fn, const double tickrate) final;


private:

    // Internal implementation
    std::shared_ptr<StateImpl> d_ptr;

};


class StateMap {

public:

    StateMap() = default;
    StateMap(std::initializer_list<std::pair<std::string, State&>> init);

    std::shared_ptr<StateImpl> operator[](const std::size_t i);
    std::shared_ptr<StateImpl> operator[](const std::string& k);

    std::size_t get_index(const std::string& k);

private:

    // Store the keys and values in order
    std::vector<std::string> keys;
    std::vector<std::shared_ptr<StateImpl>> values;

};
