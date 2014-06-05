#include <GL/glew.h>
#include <GL/glfw.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <fstream>

#include "constants.h"
#include "Shaders.h"
#include "Light.h"
#include "Model.h"
#include "viewGL.h"

Shaders viewGL::Shade;  // Initialize the shader handler

// Pre:  
// Post: Nothing happens for the default constructor
viewGL::viewGL(){ camera = NULL; };

// Pre:  
// Post: Nothing happens for the default constructor
viewGL::viewGL(Camera * cam){
  camera = cam;
  setCamera();
}

// Pre:  Camera has been set
// Post: 
void viewGL::setCamera(){
  glfwGetWindowSize(&width, &height);
  height = height > 0 ? height : 1; //conditional operator
  ratio = width / (float) height;
  camera->setMem(-ratio, ratio, -1.0f, 1.0f, -1.0f, 1.0f);
  // camera->setMem(-1, 1, -1.0f, 1.0f, -10.0f, 10.0f);
  camera->persp();
  // camera->ortho();
};

// Pre:  The gl class has been initialized
// Post: The gl window is initialized
void viewGL::Window(){  
  viewGL::initWindow();   // The viewing window
                          // and size 
  viewGL::initDefaults(); // Depth testing and clear color
  // viewGL::loadTexture(); // Load the texture data variables
  Shade.initialize(); // Initialize the shader
}

// Pre:  w not used, x and y should be the cursor position
// Post: The public member data for mouse position is set
void viewGL::setMousePosition(GLFWwindow * w, double x, double y){
  mouseX = x; mouseY = y;
}

// Post: Initialize the viewing window
void viewGL::initWindow(){
  // Initialize GLFW
  if(!glfwInit()) {
    std::cerr << "Failed to initialize GLFW: " << std::endl;
    exit(EXIT_FAILURE);
  }
  // Open a window and create its OpenGL context
  //  window =   glfwOpenWindow(640, 480, 0, 0, 0, 0, 
  //		 16, 0, GLFW_WINDOW );

  if(!glfwOpenWindow(640, 480, 0, 0, 0, 0, 16, 0, GLFW_WINDOW )){
    std::cerr << "Failed to open GLFW window" << std::endl;
    glfwTerminate();
    exit(EXIT_FAILURE);
  }
  // Check to make sure the gl extensions initialized
  if(glewInit() != GLEW_OK) {
    std::cerr << "Failed to initialize OpenGL Extensions\n" 
	      << std::endl;
    glfwTerminate();
    exit(EXIT_FAILURE);
  } 

  glfwSetWindowTitle(WINDOW_TITLE);
  // Ensure we can capture the escape key being pressed below

  // glfwSetCursorPosCallback(window, setMousePosition);
			   // void(*setMousePosition)
			   // (GLFWwindow*,double,double));
}

// Some basic init stuff that is more difficult to classify
void viewGL::initDefaults(){
  glfwEnable( GLFW_STICKY_KEYS );

  // Enable vertical sync (on cards that support it)
  glfwSwapInterval(SWAP_INTERVAL);  
  // Set clear color
  glClearColor(CLEAR, CLEAR, CLEAR, CLEAR);
  // enable depth testing
  glEnable(GL_DEPTH_TEST);
  // Guarentee that depth function is set to less. should default here
  glDepthFunc(GL_LESS);
}

// Post: The texture variable for the Model class is linked to GL
void viewGL::loadTexture(){
  std::cerr << "viewGL.cc Line 82: NOT AVAILABLE METHOD" << std::endl;

  // //glGenTextures( # of texture names to be given, an array that
  // //               stores the texture id name)
  // glGenTextures(NUM_TEXTURES, &viewGL::Shade[VTN_SHADER][tID]);
  // //glBindTexture( target to be bound, name of a texture)
  // glBindTexture(GL_TEXTURE_2D, viewGL::Shade[VTN_SHADER][tID]);
}

// Pre:  Gl window has been initialized
// Post: The standard loop operations are processed (only should be
//       done once per main loop, checks for window size and adjusts
//       if necessary, clears the current buffer for redrawing
void viewGL::beginLoop(){
  // Get window size (may be different than the requested size)
  glfwGetWindowSize(&width, &height);
  // Set the rendering viewport location and dimensions
  height = height > 0 ? height : 1; //conditional operator
  // bool statement ? true case : false case
  glViewport(0, 0, width, height);
  // Clear color buffer to black
  // Clear color buffer
  glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

  //Specifies which matrix stack is the target for subsequent matrix
  // operations. In this case, the Projection matrix stack is used.
  ratio = width / (float) height;
  if ((camera->left() != -ratio)||(camera->right() != ratio)){
    camera->setMem(-ratio, ratio, -1.0f, 1.0f, 1.0f, -1.0f);
    //left,right,bottom,top,nearVal,farVal (near is negative?)
    camera->ortho(); // Recalculate the ortho matrix
  }
}

// Pre:  All shapes have been drawn
// Post: The attribute arrays are disabled
void viewGL::endLoop(){
  glfwSwapBuffers();
}

// Pre:  Window() method has been called before
// Post: The openGL context window is closed
void viewGL::close(){
  // Close OpenGL window and terminate GLFW
  glfwTerminate();
}

// Pre:  The shaders were successfully compiled and linked
// Post: All allocated buffers are freed
viewGL::~viewGL(){
  // Deallocate buffer memory
  for (int shaderNum=0; shaderNum<NUMPROGS; shaderNum++){
    glDeleteProgram(Shade[shaderNum][pID]);    
  }

}
