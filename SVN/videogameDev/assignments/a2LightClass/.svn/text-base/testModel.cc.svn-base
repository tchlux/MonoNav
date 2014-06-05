#include <iostream>
#include <stdio.h>
#include <GL/glew.h>
#include <GL/glfw.h>
#include "viewGL.h"
#include "Model.h"
#include "Light.h"

using namespace std;

// Pre:  the name of the file to be loaded in argv[1]
// Post: Testing the model class, loading the cube.obj file
int main(int argc, char * argv[]){
  int status = 0; //Normal execution
  if (argc != 2){
    std::cerr << "ERROR: Usage ./testModel .obj" << std::endl;
    status = 1; //Usage error
    return(status);
  }
  viewGL gl; //Initialize all gl stuff
  Model mod1; //Initialize a model class for drawing
  Light lig; //Initialize a light class for lighting
  mod1.load(argv[1]); //Load in the model file
  lig.set_position(1.0f, 0.0f, 1.0f);
  lig.set_color(0.8f, 0.8f, 1.0f);
  lig.set_attenuation(1.0);
  lig.activate(); // Turn on the lights
  while(glfwGetKey(GLFW_KEY_ESC) != GLFW_PRESS &&
	glfwGetWindowParam(GLFW_OPENED)){

    gl.beginLoop(); //Run standard check loop ops

    mod1.events(); //Check for events for this model
    mod1.draw(); //Draw this model

    gl.endLoop();
  }
  // Close OpenGL window and terminate GLFW
  glfwTerminate();
  return(status);
}


// Materials should be read in differently.
// Currently it will only handle one material.  That means that the
// main loop for reading materials has to be moved into the model
// class. Otherwise you could give the material files the list, and
// the model just have one bin for all materials.  Probably the latter
// is a better thought.
