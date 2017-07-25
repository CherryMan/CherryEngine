#include <CherryEngine/state.h>

#include <algorithm>
#include <cstddef>
#include <initializer_list>
#include <utility>
#include <thread>

#include "../state/state_impl.h"
#include "../state/state_machine.h"


// State definitions
State::State() : d_ptr(std::make_shared<StateImpl>()) {}

void State::substate(State &subst) { d_ptr->substate(*(subst.d_ptr)); }
void State::next_state() { d_ptr->next_state(); }
void State::change_state(const std::string &st_name) { d_ptr->change_state(st_name); }
void State::loop(state_fn fn, const double tickrate) { d_ptr->loop(fn, tickrate); }


// StateMap definitions
StateMap::StateMap(std::initializer_list<std::pair<std::string, State&>> init) {

    for (auto &it : init) {

        values.push_back(it.second.d_ptr);
        keys.push_back(it.first);

    }
}

std::shared_ptr<StateImpl> StateMap::operator[](const std::size_t i) {
    return values[i];
}

std::shared_ptr<StateImpl> StateMap::operator[](const std::string& k) {
    return values[get_index(k)];
}

std::size_t StateMap::get_index(const std::string& k) {

    std::size_t r = -1;

    auto it = std::find(keys.cbegin(), keys.cend(), k);

    if (it == keys.end()) {
        r = -1;
    } else {
        r =  it - keys.begin();
    }

    return r;
}
