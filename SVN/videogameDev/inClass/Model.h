#ifndef MODEL_DEFINED
#define MODEL_DEFINED

#include <stdlib.h>
#include <vector>
#include "GL/glfw.h"

class Model{
  // CI:  This is a class that will hold the vertices and faces of a
  //      shape for the purpose of drawing in opengl, if numVerts != 0
  //      then it is considered vertData and colorData have some
  //      elements in them that must be freed upon deletion

private:

  bool hasData;	       // Stores whether or not a file has been loaded
  GLuint vBuffID;      // vertex buffer id's
  int numVerts;	       // Number of vertices in the current model
  float x_rot;         // X rotation scaling factor
  float y_rot;         // Y rotation scaling factor
  float delta_rot;     // Ammount rotation changes on key press

public:  

  // Pre:  None
  // Post: numVerts initialized
  Model();

  // Pre:  line is terminated, space seperated line of numbers
  //       preceeded by a character symbolizing purpose, verts and
  //       faceData have already been defined and initialized
  // Post: The data is stored appropriately based off line data type,
  //       vertex data going to verts, face data going to faceData,
  //       any out of contex lines are ignored
  void addLine(char * line, std::vector<float> & verts, 
	       std::vector<int> & faceData);

  // Pre:  objFilename is a terminated character array that is an
  //       existing file in the current working directory
  // Post: The obj file is loaded into this model object, if there was
  //       already a loaded file, it is deleted ant replaced with the
  //       new obj file information
  void load(char * objFilename);

  // Pre:  Gl window has been initialized
  // Post: Check for events specific to this object
  void events();

  // Pre:  vertData and colorData have been initialized
  // Post: The vertices are drawn through glFunctions
  void draw();

  // Pre:  None
  // Post: The arrays of stored data are freed from memory
  ~Model();

};

#endif
