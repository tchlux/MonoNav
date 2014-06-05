#ifndef MODEL_DEFINED
#define MODEL_DEFINED

#include <GL/glew.h> 
#include <GL/glfw.h> 
#include "Vertex.h"  
#include "List.h"    
#include "Material.h"
#include "viewGL.h"  

using namespace std;

class Model{
  // CI:  This is a class that will hold the vertices and faces of a
  //      shape for the purpose of drawing in opengl, if numVerts != 0
  //      then it is considered vertData and colorData have some
  //      elements in them that must be freed upon deletion

private:

  bool hasData;	// Stores whether or not a file has been loaded
  bool toExtract; // Whether or not a usemtl line has been found
  List<Material*> matDepot; // All materials from file
  List<Material*> mats;  // All materials for this class in order of
                         //  usage according to VBO
  List<GLuint> vboIDs; // The list of vboID's 
  List<GLuint> nboIDs; // list of normal buffer objects
  List<GLuint> tboIDs; // list of texture buffer objects
  List<int> numVerts;  // The number of vertices in correspondence to
                       //  the same index locations in the boID's
  Vertex Min; // Min point for the bounding box
  Vertex Max; // Max point for the bounding box  

public:  
  float Momentum;// The momentum of this object
  float Radius;  // The approximate radius of this object
  Vertex Center; // The center of this model object based on bBox
  Vertex bBox[BOUNDING_BOX_SIZE]; // Holds the vertices of the model
  Vertex nBox[NORMAL_BOX_SIZE];

  friend class viewGL; //Give the window access to the static vars

  // Pre:  n/a
  // Post: Some load variables are sest, default shader added
  Model();

  // Pre:  None
  // Post: The arrays of stored data are freed from memory
  ~Model();

  // Pre:  objFilename is a terminated character array that is an       
  //       existing file in the current working directory
  // Post: The obj file is loaded into this model object, if there was
  //       already a loaded file, it is deleted ant replaced with the
  //       new obj file information
  void load(const char * objFilename);

  // Pre:  line is terminated, space seperated line of numbers preceeded
  //       by a character symbolizing purpose, vertData, normData,
  //       textData, and faceData are initialized
  // Post: The data is stored appropriately based off line data type,
  //       any out of contex lines are ignored
  void addLine(stringstream & line, // so that it is not copied
	       List<List<float>* > & vertData, 
	       List<List<float>* > & textData,
	       List<List<float>* > & normData,		    
	       List<List<int>* > & faceData);

  // Pre:  faceData is defined and has newly allocated Lists as elements
  // Post: All the lists in faceData are deleted
  void deleteSubElementsi(List<List<int>* > & faceData);

  // Pre:  vData is defined and has newly allocated Lists as elements
  // Post: All the lists in faceData are deleted
  void deleteSubElementsf(List<List<float>* > & vData);

  // Pre:  line is from an mtl file and the id has already been
  //       extracted
  // Post: The material file information is read into mats
  void materialLine(std::stringstream & line);

  // Pre:  line is defined, has not been tampered with yet hahaha (no
  //       extractions)
  // Post: The data from this line is handled accordingly by .mtl file
  //       standards
  void matFileLine(std::stringstream & line);

  // Post: A default material is created and set as the current
  void setDefaultMat();

  // Pre:  materialName is null terminated
  // Post: The index of the material is returned, MAT_NOT_FOUND if the
  //       material isn't found in matDepot
  Material * getMatIndex(const char * materialName);

  // Pre:  vertData is defined and has some set of vertices in it
  // Post: The min (x,y,z) and max (x,y,z) are saved to bounding box
  void getBoundaries(List<List<float>* > & vertData);

  // Pre:  vertData, faceData, textData, and normal data have been
  //       initialized.  
  // Post: The data is appropriately extracted from the various Lists
  //       into proper arrays and then sent to the graphics card through
  //       dataToGL method
  void extractData(List<List<float>* > & vertData, 
		   List<List<float>* > & textData,
		   List<List<float>* > & normData,
		   List<List<int>* > & faceData);

  // Pre:  Vertex data and face data, vbo is defined and of appropriate
  //       length for the data type it expects extracted, shaderType is
  //       the identifier for which values to extract
  // Post: This vbo is filled with the information from vData in fData's
  //       desired order based off of the shader identifier
  void createVBO(List<List<float>* > & vData,
		 List<List<int>* > & fData, float * vbo,
		 int shaderType);

  // Pre:  vertex, texture, and normal are all arrays of floats that
  //       have been either initialized to NULL or allocated an array
  //       with new.  The size variables in respective order must be
  //       correct
  // Post: The pointers to the arrays are given to gl, which sends
  //       their information to the graphics card.  The identifiers
  //       that are returned are stored locally in member data
  //       (DEFAULT_ID)
  //       remains if there is no data in the array
  void dataToGL(GLfloat * vertexData, GLfloat * textureData, 
		GLfloat * normalData, int vDsize, int nDsize,
		int tDsize);

  // Pre:  segment is the index in vboIDs, mvpMatrix is set properly
  // Post: The parameters for the vertex shader are set
  void setDrawV(int segment, Material * currMat, float * mvpMatrix);

  // Pre:  segment is the index in vboIDs, currMat defined, mvpMatrix is
  //       properly defined
  // Post: The parameters for the vertex-texture shader are set
  void setDrawVT(int segment, Material * currMat, float * mvpMatrix);

  // Pre:  segment is the index in vboIDs, currMat defined, mvpMatrix,
  //       mvMatrix, and nMatrix are all defined properly
  // Post: The parameters for the vertex-normal shader are set
  void setDrawVN(int segment, Material * currMat, 
		 float *mvpMatrix, float *mvMatrix, 
		 float *nMatrix);

  // Pre:  segment is the index in vboIDs, currMat defined, mvpmatrix,
  //       mvMatrix, and nMatrix are all defined properly
  // Post: The parameters for the vertex-texture-normal shader are set
  void setDrawVTN(int segment, Material * currMat,
		  float * mvpMatrix, float * mvMatrix, 
		  float * nMatrix);

  // Pre:  All necessary arrays of data have been sent to the graphics
  //       card and can be accessed with their ID's.  These two
  //       matrices must be of length 16 or NULL
  // Post: The shapes and faces are drawn through glFunctions with the
  //       appropriate shader dependent on the values stored in member
  //       data. 
  void draw(float * mvMatrix, float * mvpMatrix, float * nMatrix);

  // Pre:  Min and Max are set to the bounding corners of this model
  // Post: All 8 vertices that make up the bounding box are generated
  void genBoundingBox();

  // Pre:  If matDepot or bBox have elements in them, they were
  //       allocated with 'new'
  // Post: If data is loaded it is cleared from gl and member data,
  //       otherwise nothin will happen
  void clear();

  // Post: All information regarding Models is printed to the termeinal
  void print();

  // Pre:  out and mod are defined properly
  // Post: The information in mod is sent to this ostream
  friend ostream & operator<<(ostream & out, Model & mod);

};

#endif
