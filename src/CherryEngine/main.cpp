#include <CherryEngine/main.h>
#include <CherryEngine/state.h>

#include "core.h"


void start(StateMap &st_map, const std::string &st_name) {
    init();
    loop(st_map, st_name);
    end();
}
