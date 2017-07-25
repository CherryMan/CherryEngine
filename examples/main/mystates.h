#pragma once


#include <CherryEngine/state.h>

class BaseState : public State {

public:
    BaseState() {
        loop(CB(render), 1);
    }

private:
    int countdown = 5;

    void render();
};


class NextState : public State {

public:
    NextState() {
        loop(CB(run), 0.5);
    }

private:
    int count = 0;

    void run();
};
