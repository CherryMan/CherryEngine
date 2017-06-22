#pragma once


#include <CherryEngine/state.h>


class BaseState : public State {

public:
    BaseState() = default;

    void render() override;

};
