#include <GL/glew.h>
#include <GL/glfw.h> // To send texture data to graphics card
#include <iostream> // For cerr statements
#include <fstream> // To read in ppm files
#include <stdlib.h>  // for atof and atoi
#include <vector>    // For dynamic arrays (simplicity)
#include <sstream>

#include "strops.h"  // for streq, strcpy, split and delSplit
#include "constants.h" // All necessary constants
#include "Material.h"

typedef unsigned char uchar; // Used for shortening of statments

// Default constructor
// Post: This material is ready to be used by a shader
Material::Material(){
  mat = strcpy(DEFAULT_MATERIAL_NAME); // Set default name
  for (int ch=0; ch<(CHANNELS-1); ch++){ // -1 so the fourth channel
                                         // isn't set
    ka[ch] = DEFAULT_MAT_KA;
    kd[ch] = DEFAULT_MAT_KD;
    ks[ch] = DEFAULT_MAT_KS;
  }
  ka[CHANNELS-1] = kd[CHANNELS-1] = ks[CHANNELS-1] = DEFAULT_FOURTH_CH;
  ns = DEFAULT_MAT_NS;
}

// Pre:  Material is terminated properly
// Post: This material is ready to be read from a file
Material::Material(char * material){
  mat = material;
}

// Pre:  inFile, width, and height are defined
// Post: width and height are read from the header of the file, inFile
//       is now ready to have image data extracted
void Material::getSize(std::ifstream & inFile, int & width,
		       int & height){
  width = height = 0; // Initialize width and height to 0
  char line[MAX_LINE_LENGTH]; // Holder for line from inFile
  for(int fileLine=0; fileLine<PPM_HEADER_SIZE; fileLine++){
    inFile.getline(line, MAX_LINE_LENGTH); // Get next line from file
    if (fileLine == WH_HEADER_LINE){ // If it is the w/h line
      char ** splitLine; // Used to hold the file header information
      int size; // Used to hold the splitLine size
      splitLine = split(line, SPACE, size); // Split line by spaces
      width = atoi(splitLine[WIDTH_INDEX]); // Get the width
      height = atoi(splitLine[HEIGHT_INDEX]); // Get the height
      delSplit(splitLine, size); // Free memory from split
    }
  }
}

// Pre:  filename is terminated, width and height are defined
// Post: The file is read into a vector
std::vector<uchar> * Material::getTexture(const char * filename, 
					  int & width, int & height){
  std::ifstream inFile(filename);
  std::vector<uchar> * image = new std::vector<uchar>;
  getSize(inFile, width, height); // Get the width and height
  for(int d=1; d<=(width*height*BYTES_PER_PIXEL); d++){// (! inFile.eof()){
    if ((d % (BYTES_PER_PIXEL) == 0)){
      image->push_back(DEFAULT_ALPHA);
    }
    else{
      image->push_back(inFile.get());
    }
  }
  inFile.close();
  return(image);
}

// Pre:  rawData has all ppm file image data in it, data is large
//        enough to hold all of the data in rawData. width>0 height>0
// Post: The data is organized and flipped so that it is ready to be
//       sent to the graphics card
void Material::flipExtract(std::vector<uchar> & rawData,
			   uchar * data, int width, int height){
  int dataIndex;
  int byteWidth = width * BYTES_PER_PIXEL;
  int size = height * byteWidth;
  for (int d=0; d<rawData.size(); d++){
    dataIndex = (size - ((d/byteWidth)+1)*(byteWidth)) + d%(byteWidth);
    data[dataIndex] = rawData[d];
  } // ^^ Flips the image to be bottom left oriented
    //    data[d] = rawData[d]; // Default upsidedown load
}

// Pre:  fileName is terminated
// Post: The texture data is sent to the graphics card
void Material::loadTexture(const char * fileName){
  int width, height;  // Holder for image size
  std::vector<uchar> & raw = *(getTexture(fileName, width, height));
  uchar data[width*height*BYTES_PER_PIXEL]; // holder for formatted pix data
  if (raw.size() != width*height*BYTES_PER_PIXEL){
    std::cerr << "PPM SIZE ERROR" << "\nExpected: " 
	      << width * height * BYTES_PER_PIXEL << "\nActual: " << raw.size() 
	      << std::endl;
  }
  flipExtract(raw, data, width, height); // Put raw pixel info in data

  //(target,level,internalFormat,width,height,border,format,type,data)
  glTexImage2D(GL_TEXTURE_2D, IMAGE_LEVEL, GL_RGBA, width, height,
	       IMAGE_BORDER, GL_RGBA, GL_UNSIGNED_BYTE, data);
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
  // These two lines allow for the magnification and minimizing of the
  //  objects on draw operations
}

// Pre:  all proceeding space separated elements of line are floats,
//       floats is an array
// Post: The values from line are read into the float array
void Material::getFloats(std::stringstream & line, float * floats){
  int index = 0;
  for (int index=0; ((index<CHANNELS)&&(!line.eof())); index++){
    line >> floats[index];
  }
}

// Pre:  Splitline is defined two-d char array, size is the length
// Post: The line is read in and added to the mat file appropriately
void Material::addLine(std::string & id, std::stringstream & line){
  if (streq(id.c_str(), KA_SYMBOL)){
    getFloats(line, ka);
  }
  else if (streq(id.c_str(), KD_SYMBOL)){
    getFloats(line, kd);
  }
  else if (streq(id.c_str(), KS_SYMBOL)){
    getFloats(line, ks);
  }
  else if (streq(id.c_str(), NS_SYMBOL)){
    line >> ns;
  }
  else if (streq(id.c_str(), MAP_KD_SYMBOL)){
    std::string file; // To get the character arry form of the line
    line >> file; // Extract the fileName
    loadTexture(file.c_str()); // Load in the ppm file for texture
  }  
}

// Pre:  out and mat are defined properly
// Post: The information in mat is sent to this ostream
std::ostream & operator<<(std::ostream & out, Material & mat){
  out << "Material: " << mat.mat << std::endl;
  out << "Ka: ";
  for (int channel=0; channel<CHANNELS; channel++){
    out << mat.ka[channel] << " ";
  }
  out << std::endl << "Kd: ";
  for (int channel=0; channel<CHANNELS; channel++){
    out << mat.kd[channel] << " ";
  }
  out << std::endl << "Ks: ";

  for (int channel=0; channel<CHANNELS; channel++){
    out << mat.ks[channel] << " ";
  }
  out << std::endl << "Ns: " << mat.ns << std::endl;
  return(out);
}

// Post: If material isn't NULL it is freed from memory
Material::~Material(){
  if (mat != NULL){
    delete(mat);
  }
}
