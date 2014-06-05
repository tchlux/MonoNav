#include <stdio.h>   // For printf
#include <stdlib.h>  // for atof and atoi
#include <GL/glew.h> // All gl variables and functions
#include <GL/glfw.h> // All gl variables and functions
#include <fstream>   // For obj file reading
#include <iostream>  // For cout
#include <string>    // For holding file lines
#include <sstream> // For streaming file lines
#include <cmath>   // For infinity

#include "constants.h" // All necessary game constants
#include "List.h"    // For holding all the file information
#include "strops.h"  // String operations for line manipulation
#include "Parse.cc"
#include "Material.h"// For all material operations
#include "Model.h"   // Model class definition file
#include "viewGL.h"

using namespace std;

// Pre:  n/a
// Post: Some load variables are sest, default shader added
Model::Model(){
  toExtract = hasData = false; // Nothing has been loaded yet
  Min.set(INFINITY,INFINITY,INFINITY);
  Max.set(-INFINITY,-INFINITY,-INFINITY);
}

// Pre:  objFilename is a terminated character array that is an       
//       existing file in the current working directory
// Post: The obj file is loaded into this model object, if there was
//       already a loaded file, it is deleted ant replaced with the
//       new obj file information
void Model::load(const char * objFilename){
  Model::clear(); // Clear old data if it existed
  List<List<float>* > vertData; // The float data for the unique vertice
  List<List<float>* > textData; // Holder for texture data
  List<List<float>* > normData;  // Holder for normal data
  List<List<int>* > faceData;// Holder for the face data (and all
  //                           indices of data in other Lists
  char line[MAX_LINE_LENGTH]; //Holder for the current line from obj
  ifstream inFile(objFilename); //Open the file
  if (inFile.is_open()){ //Only if the file actually opened
    while (!inFile.eof()){ //For line in obj file
      inFile.getline(line, MAX_LINE_LENGTH); //Get the line data
      stringstream lineStr(line); // The string holder for the line
      addLine(lineStr, vertData, textData, normData, faceData);
      //Add data to the appropriate Lists 
    }  
    inFile.close(); //Done with file input
    extractData(vertData, textData, normData, faceData);
    // ^^ Extracts data from the Lists and puts them in arrays then
    //       sends the final information to the graphics card
    genBoundingBox(); // Generate the bounding box for this model
    Center.X = (Min.X+Max.X)/MIDPOINT; // Set the center X
    Center.Y = (Min.Y+Max.Y)/MIDPOINT; // Set the center Y
    Center.Z = (Min.Z+Max.Z)/MIDPOINT; // Set the center Z
    Momentum = (Max.X-Min.X)*(Max.Y-Min.Y)*(Max.Z-Min.Z);
    Radius = distS(Center, Min);    // Get the squared distance between
    if (Radius > 1) // If the Radius squared is > 1
      Radius = sqrt(Radius); // Then get the actual radius
    deleteSubElementsf(vertData);
    deleteSubElementsf(textData);
    deleteSubElementsf(normData); 
    // Face data has already been claered by "extractData"
  }
  else{ // The file did not exist
    cerr << "ERROR: Unable to open file <" << objFilename 
	 << ">" << endl;
  }
  // saveVerts
}

// Pre:  line is terminated, space seperated line of numbers preceeded
//       by a character symbolizing purpose, vertData, normData,
//       textData, and faceData are initialized
// Post: The data is stored appropriately based off line data type,
//       any out of contex lines are ignored
void Model::addLine(stringstream & line, // so that it is not copied
		    List<List<float>* > & vertData, 
		    List<List<float>* > & textData,
		    List<List<float>* > & normData,		    
		    List<List<int>* > & faceData){   
  string id;
  line >> id; // Get the first element of the line
  if (streq(id.c_str(), VERTEX_SYMBOL)){ // Vertex line
    List<float> * vert = new List<float>(); // This line adds a vertex
    Parse::extractFloats(line, *vert); // Gets the values from line
    vertData.append(vert); // Adds the vertex to the list
  }
  else if (streq(id.c_str(), VERTEX_NORMAL_SYMBOL)){ // Norm line
    List<float> * normal = new List<float>(); // New normal
    Parse::extractFloats(line, *normal); // Get the float
    normData.append(normal); // Add normal to list
  }
  else if (streq(id.c_str(), VERTEX_TEXTURE_SYMBOL)){ // text line
    List<float> * texture = new List<float>();
    Parse::extractFloats(line, *texture);
    textData.append(texture);
  }
  else if (streq(id.c_str(), FACE_SYMBOL)){ // Face line
    List<int> * face = new List<int>();
    Parse::faceLine(line, *face);
    faceData.append(face); // Append this face to the list
  }
  else if (streq(id.c_str(), MAT_FILE_SYMBOL)){// Load Material
    materialLine(line);
  }
  else if (streq(id.c_str(), USE_MAT_SYMBOL)){ //Use material
    id.clear();      line >> id;
    Material * mat = getMatIndex(id.c_str());
    if (mat == MAT_NOT_FOUND){
      cerr << "MATERIAL ERROR: Material listed in material file was"
	   << " not found in materials list"  << endl;
    }
    else{
      mats.append(mat); // Append this pointer to a material
      if (toExtract)
	extractData(vertData, textData, normData, faceData); 
      // Extract this data to a VBOid list
      else 
	toExtract = true;
    }
  }
}

// Pre:  faceData is defined and has newly allocated Lists as elements
// Post: All the lists in faceData are deleted
void Model::deleteSubElementsi(List<List<int>* > & faceData){   
  for (int i=0; i<faceData.size(); i++){
    delete(faceData[i]);
  }
 faceData.clear();
}

// Pre:  vData is defined and has newly allocated Lists as elements
// Post: All the lists in faceData are deleted
void Model::deleteSubElementsf(List<List<float>* > & vData){
  for (int i=0; i<vData.size(); i++){
    delete(vData[i]);
  }
 vData.clear();  
}


// Pre:  line is from an mtl file and the id has already been
//       extracted
// Post: The material file information is read into mats
void Model::materialLine(std::stringstream & line){
  string fileName;
  line >> fileName; // Get the filename
  ifstream matFile(fileName.c_str()); // Open the file
  char cArray[MAX_LINE_LENGTH]; // Holds a line from mat file
  if (matFile.is_open()){ // If the file exists
    while (!matFile.eof()){ // Read in the file
      matFile.getline(cArray, MAX_LINE_LENGTH);
      stringstream matLine(cArray); // Holder for the line
      matFileLine(matLine);
    }
  }
  else{
    std::cerr << "ERROR: Material file not found" << std::endl;
  }
}

// Pre:  line is defined, has not been tampered with yet hahaha (no
//       extractions)
// Post: The data from this line is handled accordingly by .mtl file
//       standards
void Model::matFileLine(std::stringstream & line){
  string keyword; // Holds line segments from material file
  line >> keyword; // Get the line identifier
  if ( streq(keyword.c_str(), NEW_MAT_SYMBOL) ){
    line >> keyword; // Get the material name
    matDepot.append( new Material(strcpy(keyword.c_str())) );
  }
  else{
    matDepot.back()->addLine(keyword, line);
  }
}

// Post: A default material is created and set as the current
void Model::setDefaultMat(){
  matDepot.append(new Material()); // Default material to use
  std::cerr << "Model.cc Line 152: OBSOLETE CODE" << std::endl;
}

// Pre:  materialName is null terminated
// Post: The index of the material is returned, MAT_NOT_FOUND if the
//       material isn't found in matDepot
Material * Model::getMatIndex(const char * materialName){
  Material * matFound = MAT_NOT_FOUND;
  for (int material=0; ((material<matDepot.size())
  			&&(matFound==MAT_NOT_FOUND)); material++){
    if (streq((matDepot[material])->mat, materialName)){
      //^^ if the material name equals the name in the file
      matFound = matDepot[material]; //Save the material pointer
    }
  }
  return(matFound); // Return the pointer to that material
};

// Pre:  vertData is defined and has some set of vertices in it
// Post: The min (x,y,z) and max (x,y,z) are saved to bounding box
void Model::getBoundaries(List<List<float>* > & vertData){
  int numVerts = vertData.size();
  for (int vert=0; vert<numVerts; vert++){
    List<float> * v = vertData[vert];
    // Get min values from file
    if (v->get(0) < Min.X)  Min.X = v->get(0);
    if (v->get(1) < Min.Y)  Min.Y = v->get(1);
    if (v->get(2) < Min.Z)  Min.Z = v->get(2);
    // Get max values from file
    if (v->get(0) > Max.X)  Max.X = v->get(0);
    if (v->get(1) > Max.Y)  Max.Y = v->get(1);
    if (v->get(2) > Max.Z)  Max.Z = v->get(2);
  }
}

// Pre:  vertData, faceData, textData, and normal data have been
//       initialized.  
// Post: The data is appropriately extracted from the various Lists
//       into proper arrays and then sent to the graphics card through
//       dataToGL method
void Model::extractData(List<List<float>* > & vertData, 
			List<List<float>* > & textData,
			List<List<float>* > & normData,
			List<List<int>* > & faceData){
  // /////////////////////////////////////////////////////////////////
  // for (int face=0; face<faceData.size(); face++){
  //   List<int> * curr = faceData[face];
  //   std::cerr << "*(faceData[face]): " << *(faceData[face]) << std::endl;
  // }

  // for (int vert=0; vert<vertData.size(); vert++){
  //   List<float> * curr = vertData[vert];
  //   std::cerr << "*(vertData[vert]): " << *(vertData[vert]) << std::endl;
  // }
  // /////////////////////////////////////////////////////////////////

  getBoundaries(vertData); // Check for bounding box vertices
  GLfloat *vertexData, *normalData, *textureData;
  vertexData = normalData = textureData = NULL; // Set all to NULL
  int currShader = normData.size()>0 ?
    (textData.size()>0 ? VTN_SHADER : VN_SHADER) :
    (textData.size()>0 ? VT_SHADER  : V_SHADER);  
  int tDsize = faceData.size() * FACE_DATA_SET * COORDS_PER_TEXT;
  int nDsize = faceData.size() * FACE_DATA_SET * FLOATS_PER_NORMAL;
  int vDsize = faceData.size() * FACE_DATA_SET * FLOATS_PER_VERTEX;
  // Gets the current shader based off of the size of the lists
  switch (currShader){ // Switch on most recent material
  case VTN_SHADER: // Vertex texture normal shader
    textureData = new float[tDsize];
    createVBO(textData, faceData, textureData, VT_SHADER); // For texture
  case VN_SHADER:
    normalData = new float[nDsize];
    createVBO(normData, faceData, normalData, VN_SHADER); // For normal
  case V_SHADER:
    vertexData = new float[vDsize];
    createVBO(vertData, faceData, vertexData, V_SHADER); // For vertex
    break;
  case VT_SHADER: // Vertex texture shader
    vertexData = new float[vDsize];
    textureData = new float[tDsize];
    createVBO(textData, faceData, textureData, VT_SHADER); // For texture
    createVBO(vertData, faceData, vertexData, V_SHADER); // For vertex
    break;
  }
  dataToGL(vertexData, textureData, normalData, 
	   vDsize, tDsize, nDsize);
  delete[]vertexData;
  if (textureData != NULL)
    delete[]textureData;
  if (normalData != NULL)
    delete[]normalData;
  deleteSubElementsi(faceData);
  // ^^ Deletes dynamically allocated sub-lists (resets face info)
}

void lprint(GLfloat * data, int size){
  std::cerr << "[";
  for (int i=0; i<size; i++){
    std::cerr << data[i];
    if (i<size-1)
      std::cerr << ", ";
  }
  std::cerr << "]" << std::endl;
}


// Pre:  Vertex data and face data, vbo is defined and of appropriate
//       length for the data type it expects extracted, shaderType is
//       the identifier for which values to extract
// Post: This vbo is filled with the information from vData in fData's
//       desired order based off of the shader identifier
void Model::createVBO(List<List<float>* > & vData,
		      List<List<int>* > & fData, float * vbo,
		      int shaderType){
  int topSize = fData.size(); // The number of faces
  int innerSize = (fData.back())->size(); // numbers in face line
  int vDataInner = (vData.back())->size(); // numbers in vertex data line
  int inc = innerSize / FACE_DATA_SET; // The increment for extraction
  int max = 0;
  if (shaderType == VN_SHADER)
    shaderType = innerSize == 6 ? VT_SHADER : VN_SHADER;
  // If there are only 6 elements, then it goes v,n,v,n,v,n so the
  //       starting index of the normals is 1 (VT_SHADER)
  for (int outer=0; outer<topSize; outer++){ // for face in list
    for (int inner=shaderType; inner<innerSize; inner+=inc){ 
      // for appropriate data set in face
      int index = (*fData[outer])[inner] - 1; // Index in vData to grab
      for (int fV=0; fV<vDataInner; fV++){ // for float in vertex
	int vboIndex = (outer*(FACE_DATA_SET*vDataInner))+(inner/inc)*vDataInner+fV;
	vbo[vboIndex] = (*(vData[index]))[fV];
	if (vboIndex > max)
	  max = vboIndex;
      } // End grab float from vertex
    } // End grab vertex in face
  } // End grab face in list
}

// Pre:  vertex, texture, and normal are all arrays of floats that
//       have been either initialized to NULL or allocated an array
//       with new.  The size variables in respective order must be
//       correct
// Post: The pointers to the arrays are given to gl, which sends their
//       information to the graphics card.  The identifiers that are
//       returned are stored locally in member data (DEFAULT_ID)
//       remains if there is no data in the array
void Model::dataToGL(GLfloat * vertexData, GLfloat * textureData, 
		     GLfloat * normalData, int vDsize, int tDsize,
		     int nDsize){
  numVerts.append(vDsize / FLOATS_PER_VERTEX); // Add the number of
  //       verts for this data set to a list
  vboIDs.append(DEFAULT_ID);
  nboIDs.append(DEFAULT_ID);
  tboIDs.append(DEFAULT_ID);
  int sizeMinOne = vboIDs.size()-1; //All list sizes are the same
  //Generate, fill, and link the vertex data to an identifier
  glGenBuffers(ONE_VBO_ID, &(vboIDs[sizeMinOne]));
  glBindBuffer(GL_ARRAY_BUFFER, (vboIDs[sizeMinOne]));
  glBufferData(GL_ARRAY_BUFFER, vDsize * BYTES_PER_FLOAT, vertexData,
	       GL_STATIC_DRAW);
  if (textureData != NULL){
    glGenBuffers(ONE_VBO_ID, &(tboIDs[sizeMinOne]));
    glBindBuffer(GL_ARRAY_BUFFER, (tboIDs[sizeMinOne]));
    glBufferData(GL_ARRAY_BUFFER, tDsize * BYTES_PER_FLOAT,
		 textureData, GL_STATIC_DRAW);
  }
  if (normalData != NULL){ // If there is normalData
    glGenBuffers(ONE_VBO_ID, &(nboIDs[sizeMinOne]));
    glBindBuffer(GL_ARRAY_BUFFER, (nboIDs[sizeMinOne]));
    glBufferData(GL_ARRAY_BUFFER, nDsize * BYTES_PER_FLOAT,
		 normalData, GL_STATIC_DRAW);
  }
  hasData = true; //Now the data has been sent to GL
}

// Pre:  All necessary arrays of data have been sent to the graphics
//       card and can be accessed with their ID's.  These two matrices
//       must be of length 16 or NULL
// Post: The shapes and faces are drawn through glFunctions with the
//       appropriate shader dependent on the values stored in member
//       data. 
void Model::draw(float * mvMatrix, float * mvpMatrix, float * nMatrix){
  if (hasData){ //If there is vertex data
    for (int segment=0; segment<mats.size(); segment++){
      Material * currMat = mats[segment];
      GLuint vboID = vboIDs[segment];
      GLuint tboID = tboIDs[segment];
      GLuint nboID = nboIDs[segment];
      if (nboID == DEFAULT_ID){ // Either V or VT shaders are used
	if (tboID == DEFAULT_ID) // This is just a V_SHADER
	  setDrawV(segment, currMat, mvpMatrix);
	else // This is a VT_SHADER
	  setDrawVT(segment, currMat, mvpMatrix);
      }
      else{ // Either VN or VTN shader is being used
	if (tboID == DEFAULT_ID) // This is a VN_SHADER
	  setDrawVN(segment, currMat, mvpMatrix, mvMatrix, nMatrix);
	else // This is a VTN_SHADER
	  setDrawVTN(segment, currMat, mvpMatrix, mvpMatrix, nMatrix);
      }
      //This array is set for all types of shaders
      //glVertexAttribPointer(index, size, type, normalized, stride, pointer)
      glDrawArrays(GL_TRIANGLES, START_IND, numVerts[segment]);
      //      glDrawArrays(Mode, first value, number of vertices)
      glDisableVertexAttribArray(vboIDs[segment]);
      glDisableVertexAttribArray(tboIDs[segment]);
      glDisableVertexAttribArray(nboIDs[segment]);
    }
    //glUniform[type] is passed an identifier and then the appropriate
    //number of variables to be stored in what that ID points to 
  }
}

// Pre:  segment is the index in vboIDs, mvpMatrix is set properly
// Post: The parameters for the vertex shader are set
void Model::setDrawV(int segment, Material * currMat, float * mvpMatrix){
  glUniformMatrix4fv(viewGL::Shade[V_SHADER][mvID], NUM_MATRICES, NEEDS_TRANSPOSE, mvpMatrix);
  glUseProgram(viewGL::Shade[V_SHADER][pID]);
  // ka material
  glUniform4f(viewGL::Shade[V_SHADER][aID], currMat->ka[0], 
	      currMat->ka[1], currMat->ka[2], currMat->ka[3]);
  glEnableVertexAttribArray	(viewGL::Shade[V_SHADER][vID]);
  glBindBuffer		(GL_ARRAY_BUFFER, vboIDs[segment]);
  glVertexAttribPointer	(viewGL::Shade[V_SHADER][vID], 
			 FLOATS_PER_VERTEX, GL_FLOAT, 
			 GL_FALSE, STRIDE, NULL);
}

// Pre:  segment is the index in vboIDs, currMat defined, mvpMatrix is
//       properly defined
// Post: The parameters for the vertex-texture shader are set
void Model::setDrawVT(int segment, Material * currMat, float * mvpMatrix){
  glUniformMatrix4fv(viewGL::Shade[VT_SHADER][mvID], NUM_MATRICES, NEEDS_TRANSPOSE, mvpMatrix);
  glActiveTexture(GL_TEXTURE0); // Only one texture per shade
  glUseProgram(viewGL::Shade[VT_SHADER][pID]);
  glEnableVertexAttribArray	(viewGL::Shade[VT_SHADER][tcID]);
  glBindBuffer		(GL_ARRAY_BUFFER, tboIDs[segment]);
  glVertexAttribPointer	(viewGL::Shade[VT_SHADER][tcID], 
			 COORDS_PER_TEXT, GL_FLOAT, 
			 GL_FALSE, STRIDE, NULL);

  glUniform1i(viewGL::Shade[VT_SHADER][tsID], 0);
  // 0 is for 1st index, only one active texture map at a
  //	  time, if there was a normal map then it could goto 1
  // ka material
  glUniform4f(viewGL::Shade[VT_SHADER][aID], currMat->ka[0], 
	      currMat->ka[1], currMat->ka[2], currMat->ka[3]);

  glEnableVertexAttribArray	(viewGL::Shade[VT_SHADER][vID]);
  glBindBuffer		(GL_ARRAY_BUFFER, vboIDs[segment]);
  glVertexAttribPointer	(viewGL::Shade[VT_SHADER][vID], 
			 FLOATS_PER_VERTEX, GL_FLOAT, 
			 GL_FALSE, STRIDE, NULL);

}

// Pre:  segment is the index in vboIDs, currMat defined, mvpMatrix,
//       mvMatrix, and nMatrix are all defined properly
// Post: The parameters for the vertex-normal shader are set
void Model::setDrawVN(int segment, Material * currMat, 
		      float *mvpMatrix, float *mvMatrix, 
		      float *nMatrix){
  glUniformMatrix4fv(viewGL::Shade[VN_SHADER][mvpID], NUM_MATRICES, NEEDS_TRANSPOSE, mvpMatrix);
  glUniformMatrix4fv(viewGL::Shade[VN_SHADER][mvID], NUM_MATRICES, NEEDS_TRANSPOSE, mvMatrix);
  glUniformMatrix4fv(viewGL::Shade[VN_SHADER][nmID], NUM_MATRICES, NEEDS_TRANSPOSE, nMatrix);

  glUseProgram(viewGL::Shade[VN_SHADER][pID]);

  glEnableVertexAttribArray	(viewGL::Shade[VN_SHADER][nID]);
  glBindBuffer		(GL_ARRAY_BUFFER, nboIDs[segment]);
  glVertexAttribPointer	(viewGL::Shade[VN_SHADER][nID], 
			 FLOATS_PER_VERTEX, GL_FLOAT, 
			 GL_FALSE, STRIDE, NULL);
  // ka material
  glUniform4f(viewGL::Shade[VN_SHADER][aID], currMat->ka[0], 
	      currMat->ka[1], currMat->ka[2], currMat->ka[3]);
  // kd materials
  glUniform4f(viewGL::Shade[VN_SHADER][dID], currMat->kd[0], 
	      currMat->kd[1], currMat->kd[2], currMat->kd[3]);
  // ks materials
  glUniform4f(viewGL::Shade[VN_SHADER][sID], currMat->ks[0], 
	      currMat->ks[1], currMat->ks[2], currMat->ks[3]);
  // sc material
  glUniform1f(viewGL::Shade[VN_SHADER][scID], currMat->ns);

  glEnableVertexAttribArray	(viewGL::Shade[VN_SHADER][vID]);
  glBindBuffer		(GL_ARRAY_BUFFER, vboIDs[segment]);
  glVertexAttribPointer	(viewGL::Shade[VN_SHADER][vID], 
			 FLOATS_PER_VERTEX, GL_FLOAT, 
			 GL_FALSE, STRIDE, NULL);
  //  viewGL::Shade.printValues(VN_SHADER);
}

// Pre:  segment is the index in vboIDs, currMat defined, mvpmatrix,
//       mvMatrix, and nMatrix are all defined properly
// Post: The parameters for the vertex-texture-normal shader are set
void Model::setDrawVTN(int segment, Material * currMat,
		      float * mvpMatrix, float * mvMatrix, 
		      float * nMatrix){
  glUniformMatrix4fv(viewGL::Shade[VTN_SHADER][mvpID], NUM_MATRICES, NEEDS_TRANSPOSE, mvpMatrix);
  glUniformMatrix4fv(viewGL::Shade[VTN_SHADER][mvID], NUM_MATRICES, NEEDS_TRANSPOSE, mvMatrix);
  glUniformMatrix4fv(viewGL::Shade[VTN_SHADER][nmID], NUM_MATRICES, NEEDS_TRANSPOSE, nMatrix);
  glActiveTexture(GL_TEXTURE0); // Only one texture per shade
  glUseProgram(viewGL::Shade[VTN_SHADER][pID]);

  glEnableVertexAttribArray	(viewGL::Shade[VTN_SHADER][tcID]);
  glBindBuffer		(GL_ARRAY_BUFFER, tboIDs[segment]);
  glVertexAttribPointer	(viewGL::Shade[VTN_SHADER][tcID], 
			 COORDS_PER_TEXT, GL_FLOAT, 
			 GL_FALSE, STRIDE, NULL);
  glUniform1i(viewGL::Shade[VTN_SHADER][tsID], 0);      

  glEnableVertexAttribArray	(viewGL::Shade[VTN_SHADER][nID]);
  glBindBuffer		(GL_ARRAY_BUFFER, nboIDs[segment]);
  glVertexAttribPointer	(viewGL::Shade[VTN_SHADER][nID], 
			 FLOATS_PER_VERTEX, GL_FLOAT, 
			 GL_FALSE, STRIDE, NULL);
  // ka material
  glUniform4f(viewGL::Shade[VTN_SHADER][aID], currMat->ka[0], 
	      currMat->ka[1], currMat->ka[2], currMat->ka[3]);
  // kd materials
  glUniform4f(viewGL::Shade[VTN_SHADER][dID], currMat->kd[0], 
	      currMat->kd[1], currMat->kd[2], currMat->kd[3]);
  // ks materials
  glUniform4f(viewGL::Shade[VTN_SHADER][sID], currMat->ks[0], 
	      currMat->ks[1], currMat->ks[2], currMat->ks[3]);
  // sc material
  glUniform1f(viewGL::Shade[VTN_SHADER][scID], currMat->ns);

  glEnableVertexAttribArray	(viewGL::Shade[VTN_SHADER][vID]);
  glBindBuffer		(GL_ARRAY_BUFFER, vboIDs[segment]);
  glVertexAttribPointer	(viewGL::Shade[VTN_SHADER][vID], 
			 FLOATS_PER_VERTEX, GL_FLOAT, 
			 GL_FALSE, STRIDE, NULL);
  //  viewGL::Shade.printValues(VTN_SHADER);
}

// Pre:  Min and Max are set to be the bounding corners of this model
// Post: All 8 vertices that make up the bounding box are generated
void Model::genBoundingBox(){
  bBox[0] = Min; 
  bBox[1].set(Min.X,Min.Y,Max.Z);  bBox[2].set(Min.X,Max.Y,Min.Z);
  bBox[3].set(Max.X,Min.Y,Min.Z);  bBox[4].set(Min.X,Max.Y,Max.Z);
  bBox[5].set(Max.X,Min.Y,Max.Z);  bBox[6].set(Max.X,Max.Y,Min.Z);
  bBox[BOUNDING_BOX_SIZE-1] = Max;
}

// Pre:  If matDepot or bBox have elements in them, they were
//       allocated with 'new'
// Post: If data is loaded it is cleared from gl and member data,
//       otherwise nothin will happen
void Model::clear(){
  if (hasData){
    for (int sh=0; sh<mats.size(); sh++){ // Clear all IDs
      glDeleteBuffers(1, &(vboIDs[sh]));
      glDeleteBuffers(1, &(tboIDs[sh]));
      glDeleteBuffers(1, &(nboIDs[sh]));      
    }
    for (int m=0; m<matDepot.size(); m++){ // Delete all unique mats
      delete(matDepot[m]);
    }
    vboIDs.clear(); tboIDs.clear(); nboIDs.clear();    
    toExtract = false;
    hasData = false;
    numVerts.clear(); mats.clear(); matDepot.clear();
  }
}

// Pre:  None
// Post: The arrays of stored data are freed from memory
Model::~Model(){
  if (hasData) Model::clear();
}

// Pre:  out and mod are defined properly
// Post: The information in mod is sent to this ostream
ostream & operator<<(ostream & out, Model & mod){
  out << "__Member___  ___Data___" << endl;
  out << "hasData:     " << mod.hasData << std::endl;
  out << "matDepot:    " << mod.matDepot << std::endl;
  out << "mats:        " << mod.mats << std::endl;
  out << "vboIDs:      " << mod.vboIDs << std::endl;
  out << "nboIDs:      " << mod.nboIDs << std::endl;
  out << "tboIDs:      " << mod.tboIDs << std::endl;
  out << "numVerts:    " << mod.numVerts << std::endl;
  out << "Min corner:  (" << mod.Min.X << ", " << mod.Min.Y << ", " 
      << mod.Min.Z << ")" << std::endl;
  out << "Max corner:  (" << mod.Max.X << ", " << mod.Max.Y << ", " 
      << mod.Max.Z << ")" << std::endl;
  out << "Center:      (" << mod.Center.X << ", " << mod.Center.Y
      << ", " << mod.Center.Z << ")" << std::endl;
  out << "Radius:      " << mod.Radius;
  return(out);
}

// Post: All information regarding Models is printed to the termeinal
void Model::print(){
  std::cerr << (*this) << std::endl;
}

// std::cerr << "[";
// for(int i=0;i<9;i++){std::cerr<<vertexData[i];if(i<8)std::cerr<<",";}
// std::cerr << "]" << std::endl;

