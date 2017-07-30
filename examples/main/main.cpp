#include <iostream>

#include <CherryEngine/main.h>
#include <CherryEngine/state.h>

#include "mystates.h"

int main(int argc, char **argv) {

    BaseState basest;
    SubBaseState subbst;
    NextState nextst;

    StateMap sub_stmap {{"subb", subbst}};

    StateMap stmap {{"base", basest.substate(sub_stmap)},
                    {"next", nextst}};

    start(stmap, "base");

    return 0;
}
