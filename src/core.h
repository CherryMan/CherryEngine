#pragma once


#include <string>

#include <CherryEngine/state.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// Initialize the libs (glfw, opengl, ...)
void init();

// Main game loop
void loop(StateMap &st_map, const std::string &st_name);

// Terminate cleanly
void end();
