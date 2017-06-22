#include <CherryEngine/main.h>
#include <CherryEngine/state.h>

#include "../core.h"


void start(State *st) {
    init();
    loop(st);
    end();
}
