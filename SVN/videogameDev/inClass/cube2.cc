//========================================================================
// This is a small test application for GLFW.
// The program opens a window (640x480),
// and renders a multi-colored cube.
//========================================================================

#include <stdio.h>
#include <stdlib.h>
#include <GL/glfw.h>

#include <iostream>
#include "Model.h"

#define VERTICES_PER_TRIANGLE 3

int main(int argc, char * argv[]) {
    int width, height;      // Window width and height
    float ratio;            // Window aspect ratio

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
    glfwSetWindowTitle("Cube");

    // Ensure we can capture the escape key being pressed below
    glfwEnable( GLFW_STICKY_KEYS );

    // Enable vertical sync (on cards that support it)
    glfwSwapInterval(1);

    Model test; //Initialize a model class for drawing
    test.load(argv[1]); //Load in the image file

    do {
        // // Handle user input
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

      test.events();

        // Get window size (may be different than the requested size)
        glfwGetWindowSize(&width, &height);

        // Set the rendering viewport location and dimensions
        height = height > 0 ? height : 1;
        glViewport(0, 0, width, height);

        // Clear color buffer to black
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Select and setup the projection matrix
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        ratio = width / (float) height;
	glOrtho(-ratio, ratio, -1.0f, 1.0f, 1.0f, -1.0f);

        // Select and setup the modelview matrix
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

	// // Rotate view
        // glRotatef(x_rot, 1.0f, 0.0f, 0.0f);
	// glRotatef(y_rot, 0.0f, 1.0f, 0.0f);

	// // Draw triangle using vertex array
	// glEnableClientState(GL_VERTEX_ARRAY);
	// glEnableClientState(GL_COLOR_ARRAY);
	// glVertexPointer(3, GL_FLOAT, 0, vertices);
	// glColorPointer(3, GL_FLOAT, 0, colors);
	// glDrawArrays(GL_TRIANGLES, 0,
	// 	     numTriangles*VERTICES_PER_TRIANGLE);
	// glDisableClientState(GL_VERTEX_ARRAY);
	// glDisableClientState(GL_COLOR_ARRAY);
	test.draw();
        // Swap buffers
        glfwSwapBuffers();

    } // Check if the ESC key was pressed or the window was closed
    while(glfwGetKey(GLFW_KEY_ESC) != GLFW_PRESS &&
           glfwGetWindowParam(GLFW_OPENED));

    // Close OpenGL window and terminate GLFW
    glfwTerminate();
    exit(EXIT_SUCCESS);
}
