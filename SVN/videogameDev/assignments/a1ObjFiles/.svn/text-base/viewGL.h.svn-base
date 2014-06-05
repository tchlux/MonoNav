#ifndef INCLUDED_VIEWGL
#define INCLUDED_VIEWGL


class viewGL{
  //  CI: This will initialize a gl viewing frame and hold the normal
  //  run loop operations for drawing in openGL

private:

  int width, height;          // Window width and height
  float ratio;                // Window aspect ratio  int height;

public:

  // Pre:  None
  // Post: The gl window is initialized
  viewGL();

  // Pre:  Gl window has been initialized
  // Post: The standard loop operations are processed (only should be
  //       done once per main loop, checks for window size and adjusts
  //       if necessary, clears the current buffer for redrawing
  void loopOps();

};

#endif
