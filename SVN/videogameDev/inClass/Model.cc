#include <stdio.h>   // For printf
#include <stdlib.h>  // for something
#include <GL/glew.h> // for the frame display
#include <GL/glfw.h> // All gl variables and functions
#include <fstream>   // For obj file reading
#include <iostream>  // For cout

#include "Model.h"   // Model class definition file

#define FLOATS_PER_VERTEX 3 //How many floats are in a vertex
#define VERTS_PER_FACE 3    // 
#define NUM_START 2         //Where on the lines numbers begin in obj
#define MAX_NUM_DIGITS 5    //Max digits in vertex number
#define MAX_LINE_LENGTH 100 //Max length line in obj file

#define VERTEX_SYMBOL 'v'   //Symbol in obj file for a vertex
#define FACE_SYMBOL 'f'     //Symbol in obj file for a face line

#define SPACE ' '           //Used for retrieving numbers from lines

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
  char symbol = line[0]; //First character is symbol for line
  if ((symbol==FACE_SYMBOL)||(symbol==VERTEX_SYMBOL)){
    int numSize = 0;      //Current size of num
    char num[MAX_NUM_DIGITS]; //Holder for current number
    for (int index=NUM_START; line[index]!='\0'; index++){
      if (line[index] != SPACE){
	num[numSize] = line[index]; //Get this 'numeric' character (-,.)
	numSize++; //Increment numSize
      }
      else{
	num[numSize] = '\0'; //Terminate the number
	if (symbol == VERTEX_SYMBOL){
	  verts.push_back(atof(num)); //Get the float form of the num	  
	}
	else if (symbol == FACE_SYMBOL){
	  faceData.push_back(atoi(num)); //Get the int form
	}

	numSize = 0; //Reset the number index holder
      } // End else{     ...
    } // End for (int i...
  }
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
    numVerts = faceData.size()*VERTS_PER_FACE;// #of verts in Model
    vertData = new float[numVerts];

    for (int v=0; v<faceData.size(); v++){
      for (int f=0; f<FLOATS_PER_VERTEX; f++){
	vertData[v*FLOATS_PER_VERTEX+f] = verts[(faceData[v]-1)*
						FLOATS_PER_VERTEX+f];
      }
    }//^^Puts vertex data into the vertData in appropriate order
    glClear(GL_COLOR_BUFFER_BIT);

    // Create vertex buffer
    glGenBuffers(1, &vBuffID); //Get the buffer id number
    glBindBuffer(GL_ARRAY_BUFFER, vBuffID); //Bind buffer to the id
    glBufferData(GL_ARRAY_BUFFER, numVerts, vertData, GL_STATIC_DRAW);
    hasData = true; //Now the data has been sent to GL
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
  glLoadIdentity(); //Start new vertex draw operation (so that shapes
                    // do not overlap)

  // Rotate view
  glRotatef(x_rot, 1.0f, 0.0f, 0.0f);
  glRotatef(y_rot, 0.0f, 1.0f, 0.0f);

  // Draw using vertex buffer object
  glEnableClientState(GL_VERTEX_ARRAY);
  glBindBuffer(GL_ARRAY_BUFFER, vBuffID);
  glVertexPointer(3, GL_FLOAT, 0, NULL);
  glEnableClientState(GL_COLOR_ARRAY);

  // glBindBuffer(GL_ARRAY_BUFFER, color_buffer_id);    
  // glColorPointer(3, GL_FLOAT, 0, NULL);

  glDrawArrays(GL_TRIANGLES, 0, numVerts);
}

// Pre:  None
// Post: The arrays of stored data are freed from memory
Model::~Model(){
  if (hasData){
    // Deallocate buffer memory
    glDeleteBuffers(1, &vBuffID);
  // glDeleteBuffers(1, &color_buffer_id);
  }
}

