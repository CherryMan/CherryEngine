#pragma once


#include <cstddef>
#include <functional>
#include <initializer_list>
#include <memory>
#include <string>
#include <thread>
#include <utility>
#include <vector>


// TODO find cleaner solution
// CB should be isolated under a namespace somehow
#define CB(fn) [&]() { this->fn(); }

// state_fn is a pointer to a state method
using state_fn = std::function<void()>;

class State;
class StateMap;
class StateMachine; // internal class


class State {

    friend class StateMachine;

public:

    State() = default;
    ~State();
    State(StateMap &stm);

    // Create a new substate
    virtual State &substate(const StateMap stm) final;

    // Switch to the next state in the ordering under the StateMap
    virtual void next_state() final;

    // Switch to a specific state defined under the StateMap
    virtual void change_state(const std::string &st_name) final;


protected:

    // Add a coroutine
    // If tickrate is 0, loop is as fast as possible
    virtual void loop(state_fn fn, const double tickrate) final;


private:

    // Meant to be used by StateMachine

    // Define a single loop and its properties
    struct loop_info {
         state_fn fn;
         double tickrate;
         bool running = false;
         bool stopped = true;
         std::thread *thr;
    };

    // These store the loops tickrates, threads and substates
    std::vector<loop_info> loops;
    std::shared_ptr<StateMap> substate_map;

    // Stores the address to the StateMachine holding this State
    StateMachine *st_machine_ptr;

    // Join threads
    virtual void wait() const final;

    // Start/Stop the current state
    virtual void start() final;
    virtual void stop() final;

};


class StateMap {

public:

    StateMap() = default;
    StateMap(std::initializer_list<std::pair<std::string, State&>> init);

    State *operator[](const std::size_t i);
    State *operator[](const std::string& k);

    std::size_t get_index(const std::string& k);
    std::size_t size();

private:

    // Store the keys and values in order
    std::vector<std::string> keys;
    std::vector<State*> values;
};
