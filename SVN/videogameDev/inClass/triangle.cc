//========================================================================
// This is a small test application for GLFW.
// The program opens a window (640x480),
// and renders a spinning colored triangle.
//========================================================================

#include <stdio.h>
#include <stdlib.h>
#include <GL/glfw.h>

int main(void) {
    int width, height;   // Window width and height
    float ratio;         // Window aspect ratio
    float time;          // Time elapsed
    float x_rot = 50.0f; // X rotation scaling factor
    float y_rot = 25.0f; // Y rotation scaling factor
    float pos;		 // varibale for scaling position

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
    glfwSetWindowTitle("Spinning Triangle");

    // Ensure we can capture the escape key being pressed below
    glfwEnable( GLFW_STICKY_KEYS );

    // Enable vertical sync (on cards that support it)
    glfwSwapInterval(1);

    do {
        // Get window size (may be different than the requested size)
        glfwGetWindowSize(&width, &height);

        // Set the rendering viewport location and dimenstions
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

	// Draw a triangle
	time = (float) glfwGetTime();

	glRotatef(time * x_rot, 0.0f, 0.0f, 1.0f);

	glBegin(GL_TRIANGLES);
	glColor3f(0.1f, 0.4f, 0.8f);
	glVertex3f(-0.6f, -0.4f, 0.0f);
	glVertex3f(0.6f, -0.4f, 0.0f);
	glVertex3f(0.0f, 0.6f, 0.0f);
	glEnd();



	glLoadIdentity();
	glRotatef(time * -x_rot/2, 0.0f, 0.0f, 1.0f);	    
	for (float i=0.0; i<5; i++){	    
	  glLoadIdentity();
	  pos = i / 5.0;
	  glRotatef((time * -x_rot/2) / pos, 0.0f, 0.0f, 1.0f);	    
	  glBegin(GL_TRIANGLES);
	  glColor3f(0.8f, 0.8f*pos, 0.1f);
	  glVertex3f(-1.2f*pos, -0.2f*pos, 0.0f);
	  glVertex3f(-.6f*pos, -0.2f*pos, 0.0f);
	  glVertex3f(-.9f*pos, 0.3f*pos, 0.0f);
	  glEnd();

	  glBegin(GL_TRIANGLES);
	  glColor3f(0.8f, 0.8f*pos, 0.1f);
	  glVertex3f(1.2f*pos, 0.3f*pos, 0.0f);
	  glVertex3f(.6f*pos, 0.3f*pos, 0.0f);
	  glVertex3f(.9f*pos, -0.2f*pos, 0.0f);
	  glEnd();

	  glBegin(GL_TRIANGLES);
	  glColor3f(0.8f*pos, 0.8f, 0.1f);
	  glVertex3f(0.3f*pos, 1.2f*pos, 0.0f);
	  glVertex3f(0.3f*pos, .6f*pos, 0.0f);
	  glVertex3f(-0.2*pos, .9f*pos, 0.0f);
	  glEnd();

	  glBegin(GL_TRIANGLES);
	  glColor3f(0.8f*pos, 0.8f, 0.1f);
	  glVertex3f(-.3f*pos, -1.2f*pos, 0.0f);
	  glVertex3f(-.3f*pos, -.6f*pos, 0.0f);
	  glVertex3f(.2*pos, -.9f*pos, 0.0f);
	  glEnd();

	}
        // Swap buffers
        glfwSwapBuffers();

    } // Check if the ESC key was pressed or the window was closed
    while(glfwGetKey(GLFW_KEY_ESC) != GLFW_PRESS &&
           glfwGetWindowParam(GLFW_OPENED));

    // Close OpenGL window and terminate GLFW
    glfwTerminate();
    exit(EXIT_SUCCESS);
}
