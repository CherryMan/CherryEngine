#pragma once


#include <functional>
#include <memory>
#include <string>
#include <thread>
#include <vector>


using state_fn = std::function<void()>;

class State;
class StateImpl;
class StateMachine;

class StateImpl {

    friend class StateMachine;

public:

    StateImpl() = default;
    ~StateImpl();

    void substate(StateImpl &subst);
    void start();
    void wait() const;
    void stop();
    void next_state();
    void change_state(const std::string &st_name);

    void loop(state_fn fn, const double tickrate);

    // Define a single loop and its properties
    struct loop_info {
         state_fn fn;
         double tickrate;
         bool running = false;
         std::thread *thr;
    };

    // These store the loops tickrates, threads and substates
    std::vector<loop_info> loops;
    std::vector<StateImpl*> substates;

    // Stores the address to the StateMachine holding this State
    StateMachine *st_machine_ptr;

}; // StateImpl
