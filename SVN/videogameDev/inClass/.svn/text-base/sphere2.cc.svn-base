//========================================================================
// This is a small test application for GLFW.
// The program opens a window (640x480),
// and renders a flat shaded sphere.
//========================================================================

#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>
#include <GL/glfw.h>

#include <iostream>
#include "Model.h"

const int BYTES_PER_VERTEX = 12;

int main(int argc, char * argv[]) {
  int width, height;          // Window width and height
  float ratio;                // Window aspect ratio
  // float x_rot = 0.0f;         // X rotation scaling factor
  // float y_rot = 0.0f;         // Y rotation scaling factor
  // float delta_rot = 1.0f;     // Ammount rotation changes on key press
  //  int number_of_vertices = 3; // Number of vertices in buffer
  //  int buffer_size = number_of_vertices * BYTES_PER_VERTEX;
  // GLfloat vertices[] = {-0.6f, -0.4f, 0.0f, // vertex coordinates
  // 			0.6f, -0.4f, 0.0f,
  // 			0.0f, 0.6f, 0.0f};
  // GLfloat colors[] = {0.1f, 0.4f, 0.8f,     // vertex colors
  // 		      0.1f, 0.4f, 0.8f,
  // 		      0.1f, 0.4f, 0.8f};
  // GLuint vertex_buffer_id, color_buffer_id; // vertex buffer id's

  Model test;

  // Initialize GLFW
  if(!glfwInit()) {
    fprintf(stderr, "Failed to initialize GLFW\n");
    exit(EXIT_FAILURE);
  }

  // Open a window and create its OpenGL context
  if(!glfwOpenWindow(640, 480, 0, 0, 0, 0, 16, 0, GLFW_WINDOW)) {
    fprintf(stderr, "Failed to open GLFW window\n");
    glfwTerminate();
    exit(EXIT_FAILURE);
  }
  glfwSetWindowTitle("Sphere");

  if(glewInit() != GLEW_OK) {
    fprintf(stderr, "Failed to initialize OpenGL Extensions\n");
    glfwTerminate();
    exit(EXIT_FAILURE);
  }

  // Ensure we can capture the escape key being pressed below
  glfwEnable( GLFW_STICKY_KEYS );

  // Enable vertical sync (on cards that support it)
  glfwSwapInterval(1);

  if (argc == 2){
    test.load(argv[1]);    
  }
  else{
    std::cerr << "ERROR USAGE: missing .obj file" << std::endl;
  }

  // // Create vertex buffer
  // glGenBuffers(1, &vertex_buffer_id);
  // glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_id);
  // glBufferData(GL_ARRAY_BUFFER, buffer_size, vertices, GL_STATIC_DRAW);

  // // Create color buffer
  // glGenBuffers(1, &color_buffer_id);
  // glBindBuffer(GL_ARRAY_BUFFER, color_buffer_id);
  // glBufferData(GL_ARRAY_BUFFER, buffer_size, colors, GL_STATIC_DRAW);

  // enable depth testing
  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);

  do {
    // Handle user input
    test.events();
	
    // if (glfwGetKey(GLFW_KEY_UP) == GLFW_PRESS) {
    //     x_rot += delta_rot;
    // }
    // if (glfwGetKey(GLFW_KEY_DOWN) == GLFW_PRESS) {
    //     x_rot -= delta_rot;
    // }
    // if (glfwGetKey(GLFW_KEY_LEFT) == GLFW_PRESS) {
    //     y_rot += delta_rot;
    // }
    // if (glfwGetKey(GLFW_KEY_RIGHT) == GLFW_PRESS) {
    //     y_rot -= delta_rot;
    // }

    // Get window size (may be different than the requested size)
    glfwGetWindowSize(&width, &height);

    // Set the rendering viewport location and dimenstions
    height = height > 0 ? height : 1;
    glViewport(0, 0, width, height);

    // Clear color buffer
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

    // Select and setup the projection matrix
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    ratio = width / (float) height;
    glOrtho(-ratio, ratio, -1.0f, 1.0f, -1.0f, 1.0f);

    // Select and setup the modelview matrix
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Rotate view
    // glRotatef(x_rot, 1.0f, 0.0f, 0.0f);
    // glRotatef(y_rot, 0.0f, 1.0f, 0.0f);

    // // Draw sphere using vertex buffer object
    // glEnableClientState(GL_VERTEX_ARRAY);
    // glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_id);
    // glVertexPointer(3, GL_FLOAT, 0, NULL);
    // glEnableClientState(GL_COLOR_ARRAY);
    // glBindBuffer(GL_ARRAY_BUFFER, color_buffer_id);    
    // glColorPointer(3, GL_FLOAT, 0, NULL);
    // glDrawArrays(GL_TRIANGLES, 0, number_of_vertices);

    test.draw();

    // Swap buffers
    glfwSwapBuffers();

  } // Check if the ESC key was pressed or the window was closed
  while(glfwGetKey(GLFW_KEY_ESC) != GLFW_PRESS &&
	glfwGetWindowParam(GLFW_OPENED));

  // // Deallocate buffer memory
  // glDeleteBuffers(1, &vertex_buffer_id);
  // glDeleteBuffers(1, &color_buffer_id);
    
  // Close OpenGL window and terminate GLFW
  glfwTerminate();
  exit(EXIT_SUCCESS);
}
