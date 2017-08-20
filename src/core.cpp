#include <iostream>

#include <CherryEngine/state.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "core.h"
#include "common.h"
#include "state/state_machine.h"


void init() {

    if (!glfwInit()) {
        // TODO error logger
    }

    glfw_window = glfwCreateWindow(640, 480, "title", NULL, NULL);
}

void loop(StateMap &st_map, const std::string &st_name) {

    StateMachine st_m(st_map);

    st_m.start(st_name);

    // TODO remove
    // This is a placeholder to join threads
    while (true)
        ; // null statement
}

void end() {
    glfwTerminate();
}
