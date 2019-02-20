#ifndef ___MAIN_H___
#define ___MAIN_H___

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <vector>

#include "globals.h"
#include "graphics.h"
#include "graph.h"

Graphics graphics;

double lastX, lastY;
int firstMouse = 1;
float camera_speed = 0.05f;
float camera_speed_enhanced = 0.125f;

void processInput(GLFWwindow* window);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void cursor_callback(GLFWwindow* window, double xpos, double ypos);

#endif ___MAIN_H___