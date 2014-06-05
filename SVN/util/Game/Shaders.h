#ifndef DEFINED_SHADERS
#define DEFINED_SHADERS

#include "iostream" // For the ostream operator
#include <GL/glew.h> // All gl variables and functions
#include <GL/glfw.h> // All gl variables and functions
#include "constants.h" // For all define statements

class Shaders{
  // This class will hold each of the shaders that could be used by
  // the model objects in Game and the pointers to them

private:

  GLuint attID[NUMPROGS][MAXATTS]; // Holder for all attribute id's

public:

  // No specific operations
  Shaders();

  // Post: All the shaders are compiled and linked, the variables are
  //       saved and the index operator is ready to be used for access
  void initialize();

  // Gets the pointer to the array of attributes desired
  GLuint get(int shader, int value){return(attID[shader][value]);};
  GLuint * operator[](int shader) { return(attID[shader]); };

  // Pre:  V_SHADER <= prog <= VTN_SHADER
  // Post: All the values that gl has stored for the listed attributes
  //       are printed out, for seeing what is loaded into memory
  void printValues(int prog);

private:
  // Pre:  id is a valid shader id in gl, shader is terminated
  // Post: The error log for the failed compile is printed
  void printCompileLog(GLuint id, const char * shader);

  // Pre:  file is the name of the file with the shader in it,
  //       index is the number shader to be compiled (e.g. V_SHADER)
  //       gl_shader_type is a GL variable (VERTEX or FRAGMENT)
  //       shadID is the index of this shader in viewGL::Shade
  //       shader_name is the string that is the shader type ("vertex")
  // Post: This shader is compiled and the id is saved in
  //       [index][shadID] of viewGL::Shade
  void CompileShader(const char * file, int index, 
		     GLint gl_shader_type, int shadID, 
		     const char * shader_name);
                    
  // This is the general purpose method for linking shaders
  void LinkShaders(int index);

  //  This calls the compile and link for each shader file
  void CompileLink(const char* vShad, const char* fShad, int index);

  // Links all the attributes to array variables
  void linkAttributes();

  // Will get the uniform varibale from the graphics card and send
  //  them all listed to the ostream provided
  friend std::ostream & operator<<(std::ostream & out, Shaders & s);
};

#endif
