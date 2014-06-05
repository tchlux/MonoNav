#ifndef INCLUDED_VIEWGL
#define INCLUDED_VIEWGL

#include <GL/glew.h>
#include <GL/glfw.h>
#include "glfwKeys.h"
#include "Shaders.h"
#include "Camera.h"

class viewGL{
  //  CI: This will initialize a gl viewing frame and hold the normal
  //  run loop operations for drawing in openGL

private:

  int width, height;          // Window width and height
  float ratio;                // Window aspect ratio  int height;
  Camera * camera;	      // Used for view matrix
  // GLFWwindow * window;	      // The display window

public:
  double mouseX,mouseY;       // The x and y position of the mouse

  static Shaders Shade;	      // Holds all shaders for viewGL

  // Pre:  None
  // Post: The gl window is initialized
  viewGL();

  // Pre:  None
  // Post: The gl window is initialized
  viewGL(Camera * cam);

  // Pre:  The gl class has been initialized
  // Post: The gl window is initialized
  void Window();

  // Pre:  w not used, x and y should be the cursor position
  // Post: The public member data for mouse position is set
  void setMousePosition(GLFWwindow * w, double x, double y);

private:

  // Post: Viewing window is initialized
  void initWindow();

  // Some basic init stuff that is more difficult to classify
  void initDefaults();

  // Post: The texture variable for the Model class is linked to GL
  void loadTexture();

public:

  // Pre:  Camera has been set
  // Post: Camera is set to perspective with window width and height
  void setCamera();

  // Pre:  Gl window has been initialized
  // Post: The standard loop operations are processed (only should be
  //       done once per main loop, checks for window size and adjusts
  //       if necessary, clears the current buffer for redrawing
  void beginLoop();

  // Pre:  All shapes have been drawn
  // Post: The attribute arrays are disabled
  void endLoop();

  // Pre:  Window() method has been called before
  // Post: The openGL context window is closed
  void close();

  // Pre:  The shaders were successfully compiled and linked
  // Post: All allocated buffers are freed
  ~viewGL();
};

#endif
