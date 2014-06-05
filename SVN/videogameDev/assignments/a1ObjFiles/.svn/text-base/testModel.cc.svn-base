#include <iostream>
#include <stdio.h>

#include "Model.h"
#include <GL/glfw.h>
#include "viewGL.h"

using namespace std;

// Pre:  the name of the file to be loaded in argv[1]
// Post: Testing the model class, loading the cube.obj file
int main(int argc, char * argv[]){
  int status = 0; //Normal execution
  if (argc != 2){
    std::cerr << "ERROR: Usage ./testModel filename.obj" << std::endl;
    status = 1; //Usage error
    return(status);
  }
  viewGL gl; //Initialize all gl stuff
  Model test; //Initialize a model class for drawing
  test.load(argv[1]); //Load in the image file

  while(glfwGetKey(GLFW_KEY_ESC) != GLFW_PRESS &&
	glfwGetWindowParam(GLFW_OPENED)){

    gl.loopOps(); //Run standard check loop ops

    test.events(); //Check for events for this model
    test.draw(); //Draw this model
    glfwSwapBuffers();
  }    
  // Close OpenGL window and terminate GLFW
  glfwTerminate();
  exit(EXIT_SUCCESS);
  return(status);
}
