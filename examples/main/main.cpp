#include <iostream>

#include <CherryEngine/main.h>
#include <CherryEngine/state.h>
#include <CherryEngine/log.h>

#include "mystates.h"

int main(int argc, char **argv) {

    BaseState basest;
    SubBaseState subbst;
    NextState nextst;

    error << "This is an error, a very bad one" << std::endl;
    warning << "I'm warning you dammit\n";
    status << "Just giving some info\n";

    StateMap sub_stmap {{"subb", subbst}};

    StateMap stmap {{"base", basest.substate(sub_stmap)},
                    {"next", nextst}};

    start(stmap, "base");

    return 0;
}
