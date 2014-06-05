#include <stdio.h>   // For printf
//#include <stdlib.h>  // for something
#include <GL/glew.h> // All gl variables and functions
//#include <GL/glfw.h> // All gl variables and functions
#include <fstream>   // For obj file reading
#include <iostream>  // For cout

#include "Model.h"   // Model class definition file
#include "strops.h"  // String operations for line manipulation

#define FLOATS_PER_VERTEX 3 //How many floats are in a vertex
#define VERTS_PER_FACE 3    // 
#define NUM_START 2         //Where on the lines numbers begin in obj
#define MAX_NUM_DIGITS 5    //Max digits in vertex number
#define MAX_LINE_LENGTH 100 //Max length line in obj file

#define VERTEX_SYMBOL "v"   //Symbol in obj file for a vertex
#define FACE_SYMBOL "f"     //Symbol in obj file for a face line
#define MAT_FILE_SYMBOL "mtllib" //symbol for material file
#define USE_MAT_SYMBOL "usemtl"  //symbol for material usage

#define SPACE ' '           //Used for retrieving numbers from lines
#define DRAW_WITH_COLOR false //Whether or not to use color in drawing

// Pre:  None
// Post: numVerts initialized
Model::Model(){
  hasData = false; // Nothing has been loaded yet
  numVerts = 0;	   // No vertices yet
  x_rot = 0.0f;         // default to no rotation
  y_rot = 0.0f;         // ""
  delta_rot = 1.0f;     // ""
}

// Pre:  line is terminated, space seperated line of numbers preceeded
//       by a character symbolizing purpose, verts and faceData have
//       already been defined and initialized
// Post: The data is stored appropriately based off line data type,
//       vertex data going to verts, face data going to faceData, any
//       out of contex lines are ignored
void Model::addLine(char * line, std::vector<float> & verts, 
		    std::vector<int> & faceData){ 
  int size = 0; //Holder for line length
  char ** splitLine = split(line, SPACE, size);
  if (size > 0){
    if ((streq(splitLine[0], FACE_SYMBOL))     || 
	(streq(splitLine[0], VERTEX_SYMBOL))   ||
	(streq(splitLine[0], MAT_FILE_SYMBOL)) ||
	(streq(splitLine[0], USE_MAT_SYMBOL))){
      for (int arg=1; arg<size; arg++){
	if (streq(splitLine[0], VERTEX_SYMBOL)){
	  verts.push_back(atof(splitLine[arg]));
	}
	else if (streq(splitLine[0], FACE_SYMBOL)){
	  faceData.push_back(atoi(splitLine[arg]));
	}
	else if (streq(splitLine[0], MAT_FILE_SYMBOL)){
	  //Load this material file
	}
	else if (streq(splitLine[0], USE_MAT_SYMBOL)){
	  //Use this material for the object
	}
      }
    }
    for (int arg=0; arg<size; arg++){
      delete(splitLine[arg]);
    }
    delete(splitLine);
  }
}

// Pre:  vertData is an occupied array of vertices
//       colorData is also occupied 
// Post: The pointers to the arrays are given to gl, which sends their
//       information to the graphics card.
void Model::dataToGL(GLfloat * vertData, GLfloat * colorData){
  glClear(GL_COLOR_BUFFER_BIT);

  // Create vertex buffer
  glGenBuffers(1, &vBuffID); //Get the buffer id number
  glBindBuffer(GL_ARRAY_BUFFER, vBuffID); //Bind buffer to the id
  glBufferData(GL_ARRAY_BUFFER, numVerts, vertData, GL_STATIC_DRAW);

  // Create color buffer
  glGenBuffers(1, &cBuffID);
  glBindBuffer(GL_ARRAY_BUFFER, cBuffID);
  glBufferData(GL_ARRAY_BUFFER, numVerts, colorData, GL_STATIC_DRAW);

  hasData = true; //Now the data has been sent to GL
}

// Pre:  objFilename is a terminated character array that is an       
//       existing file in the current working directory
// Post: The obj file is loaded into this model object, if there was
//       already a loaded file, it is deleted ant replaced with the
//       new obj file information
void Model::load(char * objFilename){
  if (hasData){
    // Deallocate buffer memory
    glDeleteBuffers(1, &vBuffID);
  }
  std::vector<float> verts; // The float data for the unique vertices
  std::vector<int> faceData;// Holder for the face data
  char line[MAX_LINE_LENGTH]; //Holder for the current line from obj
  std::ifstream inFile(objFilename); //Open the file
  if (inFile.is_open()){ //Only if the file actually opened
    while (!inFile.eof()){ //For line in obj file
      inFile.getline(line, MAX_LINE_LENGTH); //Get the line data
      Model::addLine(line, verts, faceData); //Add it to this class
    }  
    inFile.close(); //Done with file input
    GLfloat * vertData;    // The float data for all verts in face order
    GLfloat * colorData;   // The float data for all colors
    numVerts = faceData.size()*VERTS_PER_FACE;// #of verts in Model
    vertData = new float[numVerts];
    colorData = new float[numVerts];
    for (int v=0; v<faceData.size(); v++){
      for (int f=0; f<FLOATS_PER_VERTEX; f++){
	vertData[v*FLOATS_PER_VERTEX+f] = verts[(faceData[v]-1)*
						FLOATS_PER_VERTEX+f];
	colorData[v*FLOATS_PER_VERTEX+f] = (((float)
					     (v*FLOATS_PER_VERTEX+f))
					    / ((float) numVerts));
      }
    }//^^Puts vertex data into the vertData in appropriate order
    // Also generates some numbers for the colors of the faces

    dataToGL(vertData, colorData);//Send the data to the graphics card

    for (int i=0; i<numVerts; i++){
      std::cerr << "vertData: " << vertData[i]<< std::endl;
    }
  }
  else{
    std::cerr << "ERROR: Unable to open file <" << objFilename 
	      << ">" << std::endl;
  }
}

// Pre:  Gl window has been initialized
// Post: Check for events specific to this object
void Model::events(){
  // Handle user input
  if (glfwGetKey(GLFW_KEY_UP) == GLFW_PRESS) {
    x_rot += delta_rot;
  }
  if (glfwGetKey(GLFW_KEY_DOWN) == GLFW_PRESS) {
    x_rot -= delta_rot;
  }
  if (glfwGetKey(GLFW_KEY_LEFT) == GLFW_PRESS) {
    y_rot += delta_rot;
  }
  if (glfwGetKey(GLFW_KEY_RIGHT) == GLFW_PRESS) {
    y_rot -= delta_rot;
  }
}

// Pre:  vertData and colorData have been initialized
// Post: The vertices are drawn through glFunctions
void Model::draw(){
  if (hasData){ //If there is vertex data
    // Select and setup the modelview matrix
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity(); //Start new vertex draw operation (so that shapes
    // do not overlap)

    // // Rotate view
    glRotatef(x_rot, 1.0f, 0.0f, 0.0f);
    glRotatef(y_rot, 0.0f, 1.0f, 0.0f);

    // Draw using vertex buffer object
    glEnableClientState(GL_VERTEX_ARRAY);
    glBindBuffer(GL_ARRAY_BUFFER, vBuffID);
    glVertexPointer(3, GL_FLOAT, 0, NULL);
    glEnableClientState(GL_COLOR_ARRAY);

    if (DRAW_WITH_COLOR){
      glBindBuffer(GL_ARRAY_BUFFER, cBuffID);
      glColorPointer(3, GL_FLOAT, 0, NULL);
    }

    glDrawArrays(GL_TRIANGLES, 0, numVerts);
  }
}

// Pre:  class has been initialized
// Post: If data is loaded it is cleared from gl, otherwise NULL
void Model::clear(){
  if (hasData){
    glDeleteBuffers(1, &vBuffID);
    glDeleteBuffers(1, &cBuffID);
    hasData = false;
  }
}

// Pre:  None
// Post: The arrays of stored data are freed from memory
Model::~Model(){
  if (hasData){
    // Deallocate buffer memory
    glDeleteBuffers(1, &vBuffID);
    glDeleteBuffers(1, &cBuffID);
  }
}


// ======================================
//      Testing code, possible reuse     
// ======================================

  // std::cerr << "Split line: "<<size << std::endl;
  // for (int i=0; i<size; i++){
  //   for (int c=0; c<alen(splitLine[i]); c++){
  //     std::cerr << splitLine[i][c];
  //   }
  //   std::cerr << std::endl;
  // }

