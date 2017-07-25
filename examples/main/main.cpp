#include <iostream>

#include <CherryEngine/main.h>
#include <CherryEngine/state.h>

#include "mystates.h"

int main(int argc, char **argv) {


    BaseState basest;
    NextState nextst;

    StateMap stmap {{"base", basest},
                    {"next", nextst}};

    start(stmap, "base");

    return 0;
}
