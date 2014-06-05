#include <GL/glew.h>
#include <GL/glfw.h>
#include <stdlib.h>
#include <stdio.h>
#include "Model.h"
#include "viewGL.h"
#include <iostream>


char * TITLE = "Testing viewGL.cc";

// Pre:  None
// Post: The gl window is initialized
viewGL::viewGL(){
  // Initialize GLFW
  if(!glfwInit()) {
    fprintf(stderr, "Failed to initialize GLFW\n");
    exit(EXIT_FAILURE);
  }
  // Open a window and create its OpenGL context
  if(!glfwOpenWindow(640, 480, 0, 0, 0, 0, 0, 0, GLFW_WINDOW))
    {
      fprintf(stderr, "Failed to open GLFW window\n");
      glfwTerminate();
      exit(EXIT_FAILURE);
    }
  glfwSetWindowTitle(TITLE);
  // Ensure we can capture the escape key being pressed below
  if(glewInit() != GLEW_OK) {
    fprintf(stderr, "Failed to initialize OpenGL Extensions\n");
    glfwTerminate();
    exit(EXIT_FAILURE);
  }
  glfwEnable( GLFW_STICKY_KEYS );
  // Enable vertical sync (on cards that support it)
  glfwSwapInterval(1);  
  // enable depth testing
  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);

}

// Pre:  Gl window has been initialized
// Post: The standard loop operations are processed (only should be
//       done once per main loop, checks for window size and adjusts
//       if necessary, clears the current buffer for redrawing
void viewGL::loopOps(){
  // Get window size (may be different than the requested size)
  glfwGetWindowSize(&width, &height);

  // Set the rendering viewport location and dimensions
  height = height > 0 ? height : 1; //conditional operator
  // bool statement ? true case : false case
  glViewport(0, 0, width, height);

  // Clear color buffer to black
  // Clear color buffer
  glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

  // Select and setup the projection matrix
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity(); // This is used for the projection matrix
  ratio = width / (float) height;
  glOrtho(-ratio, ratio, -1.0f, 1.0f, 1.0f, -1.0f);

  // // Select and setup the modelview matrix
  // glMatrixMode(GL_MODELVIEW);  
  // glLoadIdentity();
}
