#ifndef MATERIAL_DEFINED
#define MATERIAL_DEFINED

#include <iostream>
#include <vector>    // For dynamic arrays (simplicity)
#include "constants.h"

typedef unsigned char uchar; // Used for shortening of statments

class Material{
  // CI:  This is a storage class for material information
public:
  const char * mat; // The name of the material
  float ka[CHANNELS], kd[CHANNELS], ks[CHANNELS]; // material specs
  float ns; // Ns value for this material

  // Default constructor
  // Post: This material is ready to be used by a shader
  Material();

  // Pre: material is terminated properly
  // Post: This material is ready to be read from a file
  Material(char * material);

  // Pre:  inFile, width, and height are defined
  // Post: width and height are read from the header of the file,
  //       inFile is now ready to have image data extracted
  void getSize(std::ifstream & inFile, int & width,
	       int & height);

  // Pre:  filename is terminated, width and height are defined
  // Post: The file is read into a vector
  std::vector<uchar> * getTexture(const char * filename, 
				  int & width, int & height);

  // Pre:  rawData has all ppm file image data in it, data is large
  //        enough to hold all the data in rawData. width>0 height>0
  // Post: The data is organized and flipped so that it is ready to be
  //       sent to the graphics card
  void flipExtract(std::vector<uchar> & rawData, uchar * data, 
		   int width, int height);

  // Pre:  fileName is terminated
  // Post: The texture data is sent to the graphics card
  void loadTexture(const char * fileName);

  // Pre:  all proceeding space separated elements of line are floats,
  //       floats is an array
  // Post: The values from line are read into the float array
  void getFloats(std::stringstream & line, float * floats);

  // Pre:  Splitline is defined two-d char array, size is the length
  // Post: The line is read in and added to the mat file appropriately
  void addLine(std::string & id, std::stringstream & line);

  // Post: If material isn't NULL it is freed from memory
  ~Material();

  // Pre:  out and mat are defined properly
  // Post: The information in mat is sent to this ostream
  friend std::ostream & operator<<(std::ostream & out, Material & mat);

};

#endif
