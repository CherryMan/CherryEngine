#pragma once


#include <CherryEngine/state.h>

class BaseState : public State {

public:
    BaseState() {
        loop(CB(render), 1);
    }

private:
    int count = 0;

    void render();
};
