#pragma once


#include <CherryEngine/state.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// Initialize the libs (glfw, opengl, ...)
void init();

// Main game loop
void loop(State *st);

// Terminate cleanly
void end();
