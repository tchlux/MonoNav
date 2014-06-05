#include <GL/glew.h>
#include <GL/glfw.h>
#include <iostream>
#include <fstream>
#include "string.h"

#include "constants.h"
#include "Shaders.h"

// Returns a c-string with the contents of the specified file.
// WARNING: This function does not check if the specified file exists
//          or is readable.
// WARNING: This function returns a c-string that must be deleted by
//          the calling function
char *read_file(const char *file_name) {
  int file_length;   char *file_string;
  std::ifstream file_stream(file_name, std::ifstream::binary);
  file_stream.seekg(0, file_stream.end); // Go to end of file
  file_length = file_stream.tellg(); // Get the # of characters in file
  file_stream.seekg(0, file_stream.beg); // Go back to beginning
  file_string = new char[file_length + 1]; // Create array for file
  file_stream.read(file_string, file_length); // Read file from begg.
  file_stream.close(); // Close file
  file_string[file_length] = '\0'; // Terminate file
  return file_string;
}

// Prints the contents of array, len must be <= the length of the array
void printArray(GLfloat * array, int len){
  std::cerr << "[";
  for (int i=0; i<len; i++){
    std::cerr << array[i];
    if (i<(len-1))
      std::cerr << ", ";
  }
  std::cerr << "]" << std::endl;
}

// No specific action
Shaders::Shaders(){};

// Post: All the shaders are compiled and linked, the variables are
//       saved and the index operator is ready to be used for access
void Shaders::initialize(){
  // Compile and link shaders
  CompileLink(V_VSHADER_FILE, V_FSHADER_FILE, V_SHADER);
  CompileLink(VT_VSHADER_FILE, VT_FSHADER_FILE, VT_SHADER);
  CompileLink(VN_VSHADER_FILE, VN_FSHADER_FILE, VN_SHADER);
  CompileLink(VTN_VSHADER_FILE, VTN_FSHADER_FILE, VTN_SHADER);
  linkAttributes(); // Link all attributes to their id's
}

// This calls the compile and link for each shader file
void Shaders::CompileLink(const char* vShad, const char* fShad, 
			  int index){
  CompileShader(vShad, index, GL_VERTEX_SHADER, 
		vShadID, VERTEX_SHADER);
  CompileShader(fShad, index, GL_FRAGMENT_SHADER, 
		fShadID, FRAGMENT_SHADER);
  LinkShaders(index);
}

// Pre:  file is the name of the file with the shader in it,
//       index is the number shader to be compiled (e.g. V_SHADER)
//       gl_shader_type is a GL variable (VERTEX or FRAGMENT)
//       shadID is the index of this shader in viewGL::Shade
//       shader_name is the string that is the shader type ("vertex")
// Post: This shader is compiled and the id is saved in
//       [index][shadID] of viewGL::Shade
void Shaders::CompileShader(const char * file, int index, 
			    GLint gl_shader_type, int shadID, 
			    const char * shader_name){
  // Load and compile fragment shader
  attID[index][shadID] = glCreateShader(gl_shader_type);
  const char *shader_source = read_file(file);
  glShaderSource(attID[index][shadID], STRINGS_IN_SHADER,
		 &shader_source, LENGTH_SHADER_STRINGS);
  delete[] shader_source;
  glCompileShader(attID[index][shadID]);
  GLint result;
  // Verify fragment shader compiled
  glGetShaderiv(attID[index][shadID], GL_COMPILE_STATUS, &result);
  if (result == GL_FALSE)
    printCompileLog(attID[index][shadID], shader_name); 
}

// Post: The shaders are linked and then verified to have linked
//        properly
void Shaders::LinkShaders(int index){
  // Link shaders
  attID[index][pID] = glCreateProgram(); // Returns non-zero identifier for
  //        an empty program object.  This is ready to be linked to
  //        various shaders
  glAttachShader(attID[index][pID], attID[index][vShadID]);
  glAttachShader(attID[index][pID], attID[index][fShadID]);
  glLinkProgram(attID[index][pID]);
  GLint result;
  // Verify shaders linked
  glGetProgramiv(attID[index][pID], GL_LINK_STATUS, &result);
  if (result == GL_FALSE) {
    char * log;
    int info_log_length;
    printf("Error linking shaders.\n");
    glGetProgramiv(attID[index][pID], GL_INFO_LOG_LENGTH, &info_log_length);
    log = new char[info_log_length];
    glGetProgramInfoLog(attID[index][pID], info_log_length, NULL, log);
    printf("%s\n", log);
    delete[] log;
  }  
}

// Pre:  id is a valid shader id in gl, shader is terminated
// Post: The error log for the failed compile is printed
void Shaders::printCompileLog(GLuint id, const char * shader){
  int info_log_length;
  std::cerr << "Error compiling " << shader << " shader" << std::endl;
  glGetShaderiv(id, GL_INFO_LOG_LENGTH, &info_log_length);
  char * log = new char[info_log_length];
  glGetShaderInfoLog(id, info_log_length, NULL, log);
  std::cerr << log << std::endl;
  delete[] log; // Delete the dynamic array
}

// Links all the attributes to array variables
void Shaders::linkAttributes(){
  for (int sn=V_SHADER; sn<=VTN_SHADER; sn++){
    GLint programID = attID[sn][pID];
    glUseProgram(programID); // Use the current program id
    switch (sn){ // Which shader (program id) should be used
    case VT_SHADER: // Shader number == Vertex Texture shader
      attID[sn][mvpID] = glGetUniformLocation(programID, MODEL_VIEW_PROJECTION_MATRIX4F);
      attID[sn][tsID] = glGetUniformLocation(programID, TEXTURE_SAMPLER);
      attID[sn][tcID] = glGetAttribLocation(programID, TEX_COORD_2F);
      attID[sn][vID] = glGetAttribLocation(programID, VERTEX_3F);
      break;
    case VTN_SHADER: // Shader number == Vertex Texture Normal shader
      attID[sn][tsID] = glGetUniformLocation(programID, TEXTURE_SAMPLER);
      attID[sn][tcID] = glGetAttribLocation(programID, TEX_COORD_2F);
    case VN_SHADER: // Shader number == Vertex Normal shader
      attID[sn][mvID] = glGetUniformLocation(programID, MODEL_VIEW_MATRIX4F);
      attID[sn][nmID] = glGetUniformLocation(programID, NORMAL_MATRIX4F);
      attID[sn][dID] = glGetUniformLocation(programID, DIFFUSE_COLOR_4F); 
      attID[sn][sID] = glGetUniformLocation(programID, SPECULAR_COLOR_4F);
      attID[sn][scID] = glGetUniformLocation(programID, SPECULAR_COEFFICIENT_1F);
      attID[sn][lpID] = glGetUniformLocation(programID, LIGHT_POSITION_3F);
      attID[sn][lcID] = glGetUniformLocation(programID, LIGHT_COLOR_4F);
      attID[sn][afID] = glGetUniformLocation(programID, ATTENUATION_FACTOR_1F);
      attID[sn][nID]  = glGetAttribLocation(programID, NORMAL_3F);
    case V_SHADER: // Shader number == Vertex Shader
      attID[sn][mvpID] = glGetUniformLocation(programID, MODEL_VIEW_PROJECTION_MATRIX4F);
      attID[sn][aID] = glGetUniformLocation(programID, AMBIENT_COLOR_4F);
      attID[sn][vID] = glGetAttribLocation(programID, VERTEX_3F);
      break;
    } // End switch
  } // All appropriate attributes should be linked for the shaders
}

// Pre:  
// Post: All the values that gl has stored for the listed attributes
//       are printed out, for seeing what is loaded into memory
void Shaders::printValues(int prog){
  GLfloat values[MATRIX_SIZE];
  GLint programID = attID[prog][pID];
  glUseProgram(programID); // Use the current program id
  switch (prog){ // Which shader (program id) should be used
  case VT_SHADER: // Shader number == Vertex Texture shader
    glGetUniformfv(programID,         attID[prog][mvpID], values);
    std::cerr << "MVP matrix:    "; printArray(values,MATRIX_SIZE);
    break;
  case VTN_SHADER: // Same for VTN and VN
  case VN_SHADER: // Shader number == Vertex Normal shader
    glGetUniformfv(programID, attID[prog][mvID], values);
    std::cerr << "Model view:    "; printArray(values,MATRIX_SIZE);
    glGetUniformfv(programID, attID[prog][nmID], values);
    std::cerr << "Normal matrix: "; printArray(values,MATRIX_SIZE);
    glGetUniformfv(programID,       attID[prog][dID] , values);
    std::cerr << "Diffuse ID:    "; printArray(values,4);
    glGetUniformfv(programID,       attID[prog][sID] , values);
    std::cerr << "Model view:    "; printArray(values,4);
    glGetUniformfv(programID,       attID[prog][scID], values);
    std::cerr << "Specular Coef: "; printArray(values,1);
    glGetUniformfv(programID,       attID[prog][lpID], values);
    std::cerr << "Light Pos:     "; printArray(values,3);
    glGetUniformfv(programID,       attID[prog][lcID], values);
    std::cerr << "Light color:   "; printArray(values,4);
    glGetUniformfv(programID,       attID[prog][afID], values);
    std::cerr << "Attenuation F: "; printArray(values,1);
  case V_SHADER: // Shader number == Vertex Shader
    glGetUniformfv(programID,         attID[prog][mvpID], values);
    std::cerr << "MVP matrix:    "; printArray(values,MATRIX_SIZE);
    glGetUniformfv(programID,         attID[prog][aID], values);
    std::cerr << "Ambient colors:"; printArray(values,4);
    break;
  } // End switch   

}


// Will get the uniform varibale from the graphics card and send
//  them all listed to the ostream provided
std::ostream & operator<<(std::ostream & out, Shaders & s){
  out << std::endl;
  for (int prog=V_SHADER; prog<=VTN_SHADER; prog++){
    out << "prog:      		 " << prog << std::endl;
    out << "=====================" << std::endl;
    out << "s.get(prog,pID):	 " << s.get(prog,pID) << std::endl;
    out << "s.get(prog,vShadID):     " << s.get(prog,vShadID) << std::endl;
    out << "s.get(prog,fShadID):     " << s.get(prog,fShadID) << std::endl;
    switch (prog){ // Which shader (program id) should be used
      case VT_SHADER:
	out << "s.get(prog,mvpID):	 " << s.get(prog,mvpID) << std::endl;
	out << "s.get(prog,tsID):	 " << s.get(prog,tsID) << std::endl;
	out << "s.get(prog,tcID):        " << s.get(prog,tcID) << std::endl;
	out << "s.get(prog,vID):         " << s.get(prog,vID) << std::endl;
	break;
      case VTN_SHADER:
	out << "s.get(prog,tsID):	 " << s.get(prog,tsID) << std::endl;
	out << "s.get(prog,tcID):        " << s.get(prog,tcID) << std::endl;
      case VN_SHADER:
	out << "s.get(prog,mvID):	 " << s.get(prog,mvID) << std::endl;
	out << "s.get(prog,nmID):	 " << s.get(prog,nmID) << std::endl;
	out << "s.get(prog,dID):	 " << s.get(prog,dID) << std::endl;
	out << "s.get(prog,sID):	 " << s.get(prog,sID) << std::endl;
	out << "s.get(prog,scID):	 " << s.get(prog,scID) << std::endl;
	out << "s.get(prog,lpID):	 " << s.get(prog,lpID) << std::endl;
	out << "s.get(prog,lcID):	 " << s.get(prog,lcID) << std::endl;
	out << "s.get(prog,afID):	 " << s.get(prog,afID) << std::endl;
	out << "s.get(prog,nID):         " << s.get(prog,nID) << std::endl;
      case V_SHADER:
	out << "s.get(prog,mvpID):	 " << s.get(prog,mvpID) << std::endl;
	out << "s.get(prog,aID):	 " << s.get(prog,aID) << std::endl;
	out << "s.get(prog,vID):         " << s.get(prog,vID) << std::endl;
	break;
      } // End switch
    out << std::endl << "=====================" << std::endl;
  }
  return(out);
}
