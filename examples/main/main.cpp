#include <CherryEngine/main.h>
#include <CherryEngine/state.h>

#include "base_state.h"

int main(int argc, char **argv) {


    BaseState client = BaseState();

    StateMap stmap { {"base", client} };

    start(&client);

    return 0;
}
