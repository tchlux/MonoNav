#include <iostream>
#include <stdio.h>
#include <GL/glew.h>
#include <GL/glfw.h>
#include "viewGL.h"
#include "Model.h"
#include "Light.h"
#include "Clone.h"

#define GLFW_KEY_C 67

using namespace std;

// Pre:  Cam is defined
// Post: 
void moveCamera(Camera * cam){
  // Handle user input
  if (glfwGetKey(GLFW_KEY_SPACE)){
    if (glfwGetKey(GLFW_KEY_UP) == GLFW_PRESS) {
      cam->rotate(-1.0f, 1, 0, 0);
      // cam->translate(0.0, 0.0, -0.01);
    }
    if (glfwGetKey(GLFW_KEY_DOWN) == GLFW_PRESS) {
      cam->rotate(1.0f, 1, 0, 0);
      // cam->translate(0.0, 0.0, 0.01);
    }
    if (glfwGetKey(GLFW_KEY_LEFT) == GLFW_PRESS) {
      cam->rotate(-1.0f, 0, 1, 0);
    }
    if (glfwGetKey(GLFW_KEY_RIGHT) == GLFW_PRESS) {
      cam->rotate(1.0f, 0, 1, 0);
    }      
  }
  else{
    if (glfwGetKey(GLFW_KEY_UP) == GLFW_PRESS) {
      cam->translate(0.0, 0.0, 0.02);
    }
    if (glfwGetKey(GLFW_KEY_DOWN) == GLFW_PRESS) {
      cam->translate(0.0, 0.0, -0.02);
    }
    if (glfwGetKey(GLFW_KEY_LEFT) == GLFW_PRESS) {
      cam->translate(0.02, 0.0, 0.0);
    }
    if (glfwGetKey(GLFW_KEY_RIGHT) == GLFW_PRESS) {
      cam->translate(-0.02, 0.0, 0.0);
    }      
  }
  
}

// Pre:  Cam is defined
// Post: 
void moveClone(Clone * clo){
  // Handle user input
  if (glfwGetKey(GLFW_KEY_SPACE)){
    if (glfwGetKey(GLFW_KEY_UP) == GLFW_PRESS) {
      clo->rotate(-1.0f, 1, 0, 0);
      // clo->translate(0.0, 0.0, -0.01);
    }
    if (glfwGetKey(GLFW_KEY_DOWN) == GLFW_PRESS) {
      clo->rotate(1.0f, 1, 0, 0);
      // clo->translate(0.0, 0.0, 0.01);
    }
    if (glfwGetKey(GLFW_KEY_LEFT) == GLFW_PRESS) {
      clo->rotate(-1.0f, 0, 1, 0);
    }
    if (glfwGetKey(GLFW_KEY_RIGHT) == GLFW_PRESS) {
      clo->rotate(1.0f, 0, 1, 0);
    }      
  }
  else{
    if (glfwGetKey(GLFW_KEY_UP) == GLFW_PRESS) {
      clo->translate(0.0, 0.02, 0.0);
    }
    if (glfwGetKey(GLFW_KEY_DOWN) == GLFW_PRESS) {
      clo->translate(0.0, -0.02, 0.0);
    }
    if (glfwGetKey(GLFW_KEY_LEFT) == GLFW_PRESS) {
      clo->translate(-0.02, 0.0, 0.0);
    }
    if (glfwGetKey(GLFW_KEY_RIGHT) == GLFW_PRESS) {
      clo->translate(0.02, 0.0, 0.0);
    }      
  }
  
}

int main(int argc, char * argv[]){
  int status = 0; // Normal execution status
  if (argc < 2){
    status = 1; // Usage error
    std::cerr << "ERROR USAGE: give a single obj file" << std::endl;
  }
  else{
    Camera cam;// One camera for viewing movement
    viewGL gl(&cam); // Viewing window and shaders handler
    gl.Window(); // Activate the viewing window
    Model mod; // One model for testing model functionalities
    mod.load(argv[1]); // Load a obj for this model
    Model Dot; Dot.load("bboxdot.obj");
    Clone dot(&Dot, &cam);
    Clone test(&mod, &cam); // This will actually be the instance of the model
    Clone test1(&mod, &cam); // This will actually be the instance of the model
    test.translate(0.0,0.0,-1.0); // Move one to the right
    test1.translate(1.0,0.0,-1.0); // Move one to the right
    Light lig; // One light for testing light functionalities
    lig.set_position(0.0f, 0.0f, 1.0f);
    lig.set_color(1.0f, 1.0f, 1.0f);
    lig.set_attenuation(0.7f);
    while(glfwGetKey(GLFW_KEY_ESC) != GLFW_PRESS &&
	  glfwGetWindowParam(GLFW_OPENED)){
      gl.beginLoop(); //Run standard check loop ops
      moveClone(&test1);      lig.activate();
      test.draw(); //Draw this clone
      test.drawBBox(dot); test1.drawBBox(dot);
      test1.draw(); //Draw this clone
      gl.endLoop();
      if (Clone::Collides(test, test1, true))
	lig.set_color(0.2f,0.2f,0.2f);
      else lig.set_color(1.0f,1.0f,1.0f);
    }
    // Close OpenGL window and terminate GLFW
    gl.close();
  }
  return(status); // Return exectution state
}
