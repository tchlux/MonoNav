#ifndef INCLUDED_LIGHT

#define INCLUDED_LIGHT

#include <GL/glew.h>
#include <GL/glfw.h>
#include "viewGL.h"

class Light{
  // CI:  This is a defualt object for emitting rays of colors
private:
  float xLoc, yLoc, zLoc; // X,Y, and Z coordinates of this light
  float rCol, gCol, bCol; // r,g, and b colors for this light
  float attenuation;	  // The attenuation for this light instance

public:

  friend class viewGL;

  // Post: Initializes location and attenuation to default values
  Light(){
    xLoc = yLoc = zLoc = 0.0;
    rCol = gCol = bCol = 1.0;
    attenuation = 0.0;
  };

  // Pre:  x, y, and z are valid
  // Post: This light's position is set to x,y,z
  void set_position(float x, float y, float z){
    xLoc = x;
    yLoc = y;
    zLoc = z;
  };

  // Pre:  r,g,b are all valid and initialized
  // Post: Colors are set to this class instance
  void set_color(float r, float g, float b){
    rCol = r;
    gCol = g;
    bCol = b;
  };

  // Pre:  Attenuation is valid floating point number
  // Post: the attenuation for this light is saved
  void set_attenuation(float factor){
    attenuation = factor;
  };

  // Post: This light is turned on
  void activate(){
    // For all shaders that include lighting, set the variables
    for (int shader=VN_SHADER; shader<=VTN_SHADER; shader++){
      glUniform3f(viewGL::Shade[shader][lpID], xLoc, yLoc, zLoc);    
      glUniform4f(viewGL::Shade[shader][lcID], rCol, gCol, bCol, 0.0);
      glUniform1f(viewGL::Shade[shader][afID], attenuation);
    }
  }

  // Pre:  All contents of light are sent to out
  // Post:   
  friend std::ostream & operator<<(std::ostream & out, Light & lig){
    out << "Light.h PRINT INFO: " << std::endl;
    out << "pos, color, att ID's: " 
	<< viewGL::Shade[VTN_SHADER][lpID] << ", "
	<< viewGL::Shade[VTN_SHADER][lcID] << ", " 
	<< viewGL::Shade[VTN_SHADER][afID] << std::endl;
    out << "x,y,z: "<< lig.xLoc
	<< ", "     << lig.yLoc
	<< ", "     << lig.zLoc << std::endl;
    out << "r,g,b: "<< lig.rCol 
	<< ", "     << lig.gCol
	<< ", "     << lig.bCol << std::endl;
    out << "Attenuation: " << lig.attenuation;
    return(out);
  }

  // Post: Sends current attribute info to the terminal
  void print(){
    std::cerr << (*this) << std::endl;
  }

};

#endif
