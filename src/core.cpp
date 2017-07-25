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

    StateMachine st_m;

    st_m.setmap(st_map);
    st_m.start(st_name);

/*
    // Ticks per second (note: temporary)
    const int tickspeed = 25;

    // GLFW uses seconds
    const double interval = 1 / (double) tickspeed;

    // Loop variables
    double next_tick = 0;

    // Game loop
    // Updates according to tickspeed
    // Renders as fast as possible
    // Note: interp will be added
    while (!glfwWindowShouldClose(glfw_window)) {

        while (glfwGetTime() > next_tick) {
            glfwPollEvents();
            // TODO update

            next_tick += interval;
        }

        // TODO render

    }
*/
}

void end() {
    glfwTerminate();
}
