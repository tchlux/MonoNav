//========================================================================
// This is a small test application for GLFW.
// The program opens a window (640x480),
// and renders a texture mapped triangle.
//========================================================================

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>
#include <GL/glfw.h>

#include <iostream>
#include <fstream>

#define PI 3.141592653589793238463
#define BYTES_PER_FLOAT 4
#define FLOATS_PER_QUAD 18
#define FLOATS_PER_VERTEX 3

#include <fstream>

#define WIDTH 256
#define HEIGHT 256
#define PIXELS WIDTH*HEIGHT
#define BYTES_PER_PIXEL 4
#define BYTES_IN_PPM PIXELS * BYTES_PER_PIXEL
#define DEFAULT_ALPHA 255

// Pre:  BYTES_IN_PPM and filename == "animal.ppm"
// Post: The file is read into an array
unsigned char * getTexture(){
  std::ifstream infile("animal.ppm");
  unsigned char * image = new unsigned char[BYTES_IN_PPM];
  for (int pix=0; pix<BYTES_IN_PPM; pix++){
    if ((pix % BYTES_PER_PIXEL) == 0){
      image[pix] = DEFAULT_ALPHA;
    }
    else{
      image[pix] = infile.get();
    }
  }
  return(image);
}

// doesn't check file exists or contents
// returned string must be deleted
char *read_file(const char *file_name) {
  int file_length;
  char *file_string;
  std::ifstream file_stream(file_name, std::ifstream::binary);
  file_stream.seekg(0, file_stream.end);
  file_length = file_stream.tellg();
  file_stream.seekg(0, file_stream.beg);
  file_string = new char[file_length + 1];
  file_stream.read(file_string, file_length);
  file_stream.close();
  file_string[file_length] = '\0';
  return file_string;
}

int main(void) {
    int width, height;          // Window width and height
    float ratio;                // Window aspect ratio
    float x_rot = 0.0f;         // X rotation scaling factor
    float y_rot = 0.0f;         // Y rotation scaling factor
    float delta_rot = 1.0f;     // Ammount rotation changes on key press

    GLuint vertex_shader_id;            // vertex shader handle
    GLuint fragment_shader_id;          // fragment shader handle
    const char *vertex_shader_source;   // vertex shader source code
    const char *fragment_shader_source; // fragment shader souce code
    GLuint program_id;                  // shader program handle
    GLint result;                       // shader compile and link result
    GLint ambient_id;                   // shader material ambient handle
    GLint diffuse_id;                   // shader material diffuse handle
    GLint specular_id;                  // shader material specular handle
    GLint specular_coefficient_id;      // shader material specular handle
    GLint light_position_id;            // shader light position handle
    GLint light_color_id;               // shader light color handle
    GLint attenuation_factor_id;        // shader light attenuation handle
    GLint vertex_id;                    // shader vertex handle
    GLint normal_id;                    // shader normal handle
    GLint tex_coord_id;                 // shader texture coordinate handle
    GLint texture_sampler_id;           // shader texture sampler handle

    GLuint texture_id;  // texture data handle

    unsigned char * texture_data = getTexture();
    // unsigned char texture_data[32] = {255, 0,   0,   255,
    // 				      0,   255, 0,   255,
    // 				      0,   0,   255, 255,
    // 				      255, 255, 255, 255,
    // 				      0,   255, 255, 255,
    // 				      255, 0,   255, 255,
    // 				      255, 255, 0,   255,
    // 				      0,   0,   0,   255};


    GLfloat vertices[] = {-0.6f, -0.4f, 0.0f, // vertex coordinates
			  0.6f, -0.4f, 0.0f,
			  0.0f, 0.6f, 0.0f};
    GLfloat normals[] = {0.0f, 0.0f, 1.0f,    // vertex normals
			 0.0f, 0.0f, 1.0f,
			 0.0f, 0.0f, 1.0f};
    GLfloat tex_coords[] = {0.0f, 0.0f,       // vertex texture coords
			    1.0f, 0.0f,
			    0.5f, 1.0f};
    int vertices_length = 9;    // number of floats in vertex array
    int tex_coords_length = 6;  // number of floats in texture coord array
    int buffer_size;            // number of bytes in vbo
    GLuint vertex_buffer_id;    // vertex buffer handle
    GLuint normal_buffer_id;    // normal buffer handle
    GLuint tex_coord_buffer_id; // texture coordinate buffer handle

    // Initialize GLFW
    if(!glfwInit()) {
        fprintf(stderr, "Failed to initialize GLFW\n");
        exit(EXIT_FAILURE);
    }
    // Open a window and create its OpenGL context
    if(!glfwOpenWindow(640, 480, 0, 0, 0, 0, 16, 0, GLFW_WINDOW)) {
        fprintf(stderr, "Failed to open GLFW window\n");
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    glfwSetWindowTitle("");

    // Initialize GLEW
    if(glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to initialize OpenGL Extensions\n");
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    // Ensure we can capture the escape key being pressed below
    glfwEnable( GLFW_STICKY_KEYS );

    // Enable vertical sync (on cards that support it)
    glfwSwapInterval(1);

    // Load texture
    glGenTextures(1, &texture_id);
    glBindTexture(GL_TEXTURE_2D, texture_id);

    // Load and compile vertex shader
    vertex_shader_id = glCreateShader(GL_VERTEX_SHADER);
    vertex_shader_source = read_file("texture.vert");
    glShaderSource(vertex_shader_id, 1, &vertex_shader_source, NULL);
    delete[] vertex_shader_source;
    glCompileShader(vertex_shader_id);

    // Verify vertex shader compiled
    glGetShaderiv(vertex_shader_id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE) {
      char *log;
      int info_log_length;
      printf("Error compiling vertex shader\n");
      glGetShaderiv(vertex_shader_id, GL_INFO_LOG_LENGTH, &info_log_length);
      log = new char[info_log_length];
      glGetShaderInfoLog(fragment_shader_id, info_log_length, NULL, log);
      printf("%s\n", log);
      delete[] log;
    }

    // Load and compile fragment shader
    fragment_shader_id = glCreateShader(GL_FRAGMENT_SHADER);
    fragment_shader_source = read_file("texture.frag");
    glShaderSource(fragment_shader_id, 1, &fragment_shader_source, NULL);
    delete[] fragment_shader_source;
    glCompileShader(fragment_shader_id);

    // Verify fragment shader compiled
    glGetShaderiv(fragment_shader_id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE) {
      char *log;
      int info_log_length;
      printf("Error compiling fragment shader\n");
      glGetShaderiv(fragment_shader_id, GL_INFO_LOG_LENGTH, &info_log_length);
      log = new char[info_log_length];
      glGetShaderInfoLog(fragment_shader_id, info_log_length, NULL, log);
      printf("%s\n", log);
      delete[] log;
    }

    // Link shaders
    program_id = glCreateProgram();
    glAttachShader(program_id, vertex_shader_id);
    glAttachShader(program_id, fragment_shader_id);
    glLinkProgram(program_id);

    // Verify shaders linked
    glGetProgramiv(program_id, GL_LINK_STATUS, &result);
    if (result == GL_FALSE) {
      char *log;
      int info_log_length;
      printf("Error linking shaders.\n");
      glGetProgramiv(program_id, GL_INFO_LOG_LENGTH, &info_log_length);
      log = new char[info_log_length];
      glGetProgramInfoLog(program_id, info_log_length, NULL, log);
      printf("%s\n", log);
      delete[] log;
    }

    // Set shader
    glUseProgram(program_id);

    // Set shader uniform variables
    ambient_id = glGetUniformLocation(program_id, "ambient_color_4f");
    diffuse_id = glGetUniformLocation(program_id, "diffuse_color_4f");
    specular_id = glGetUniformLocation(program_id, "specular_color_4f");
    specular_coefficient_id = glGetUniformLocation(program_id, "specular_coefficient_1f");
    light_position_id = glGetUniformLocation(program_id, "light_position_3f");
    light_color_id = glGetUniformLocation(program_id, "light_color_4f");
    attenuation_factor_id = glGetUniformLocation(program_id, "attenuation_factor_1f");
    texture_sampler_id = glGetUniformLocation(program_id, "textureSampler");

    // Set shader attribute variables
    vertex_id = glGetAttribLocation(program_id, "vertex_3f");
    normal_id = glGetAttribLocation(program_id, "normal_3f");
    tex_coord_id = glGetAttribLocation(program_id, "tex_coord_2f");

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 256,256, 0, GL_RGBA, GL_UNSIGNED_BYTE, texture_data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    // Create vertex buffer
    buffer_size = vertices_length * BYTES_PER_FLOAT;
    glGenBuffers(1, &vertex_buffer_id);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_id);
    // glBufferData(GL_ARRAY_BUFFER, buffer_size, vertices, GL_STATIC_DRAW);
    glBufferData(GL_ARRAY_BUFFER, buffer_size, &vertices, GL_STATIC_DRAW);

    // Create normal buffer
    glGenBuffers(1, &normal_buffer_id);
    glBindBuffer(GL_ARRAY_BUFFER, normal_buffer_id);
    // glBufferData(GL_ARRAY_BUFFER, buffer_size, normals, GL_STATIC_DRAW);
    glBufferData(GL_ARRAY_BUFFER, buffer_size, &normals, GL_STATIC_DRAW);

    // Create texture coordinate buffer
    buffer_size = tex_coords_length * BYTES_PER_FLOAT;
    glGenBuffers(1, &tex_coord_buffer_id);
    glBindBuffer(GL_ARRAY_BUFFER, tex_coord_buffer_id);
    glBufferData(GL_ARRAY_BUFFER, buffer_size, &tex_coords, GL_STATIC_DRAW);

    // enable depth testing
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    std::cerr << "______Model______            ____Data____" << std::endl;
    std::cerr << "vBuffID, nBuffID, tcBuffID: "<< vertex_buffer_id << ", " 
	      << normal_buffer_id << ", " << tex_coord_buffer_id 
	      << std::endl;
    std::cerr << "numverts:                   " << vertices_length
	      << std::endl;
    std::cerr << "x_rot, y_rot, delta_rot:    " << x_rot << ", " 
	      << y_rot << ", " << delta_rot << std::endl;
    std::cerr << "______Static Vars_____:               ___Data___" 
	      << std::endl;
    std::cerr << "diffuse_id, ambient_id:               " 
	      << diffuse_id << ", " << ambient_id << std::endl;
    std::cerr << "specular_id, specular_coefficient_id: " 
	      << specular_id << ", " << specular_coefficient_id 
	      << std::endl;
    std::cerr << "vertex_id, normal_id:                 " 
	      << vertex_id << ", " << normal_id << std::endl;
    std::cerr << "tex_coord_id, texture_id:             " 
	      << tex_coord_id << ", " << texture_id << std::endl;
    std::cerr << "texture_sampler_id:                   " 
	      << texture_sampler_id << std::endl;
    std::cerr << "_________________________________________________"
	      << std::endl;

    do {
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

        // Get window size (may be different than the requested size)
        glfwGetWindowSize(&width, &height);

        // Set the rendering viewport location and dimenstions
        height = height > 0 ? height : 1;
        glViewport(0, 0, width, height);

	// Clear color buffer
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

        // Select and setup the projection matrix
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        ratio = width / (float) height;
	glOrtho(-ratio, ratio, -1.0f, 1.0f, -1.0f, 1.0f);

        // Select and setup the modelview matrix
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

	// Rotate view
        glRotatef(x_rot, 1.0f, 0.0f, 0.0f);
	glRotatef(y_rot, 0.0f, 1.0f, 0.0f);

	glActiveTexture(GL_TEXTURE0);

	// Set shader attribute variables to vbo's
	glUniform4f(ambient_id, 0.1f, 0.1f, 0.1f, 1.0f);
	glUniform4f(diffuse_id, 1.0f, 1.0f, 1.0f, 1.0f);
	glUniform4f(specular_id, 1.0f, 1.0f, 1.0f, 1.0f);
	glUniform1f(specular_coefficient_id, 100.0f);

	glUniform3f(light_position_id, 2.0f, 2.0f, 2.0f);
	glUniform4f(light_color_id, 1.0f, 1.0f, 1.0f, 0.0);
	glUniform1f(attenuation_factor_id, 0.5f);

	glUniform1i(texture_sampler_id, 0);

	// Set shader attribute variables to vbo's
	glEnableVertexAttribArray(vertex_id);
	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_id);
	glVertexAttribPointer(vertex_id, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	glEnableVertexAttribArray(normal_id);
	glBindBuffer(GL_ARRAY_BUFFER, normal_buffer_id);
	glVertexAttribPointer(normal_id, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	glEnableVertexAttribArray(tex_coord_id);
	glBindBuffer(GL_ARRAY_BUFFER, tex_coord_buffer_id);
	glVertexAttribPointer(tex_coord_id, 2, GL_FLOAT, GL_FALSE, 0, NULL);

	// Draw
	glDrawArrays(GL_TRIANGLES, 0, vertices_length / FLOATS_PER_VERTEX);

	// Disable attribute arrays
	glDisableVertexAttribArray(vertex_id);
	glDisableVertexAttribArray(normal_id);
	glDisableVertexAttribArray(tex_coord_id);

        // Swap buffers
        glfwSwapBuffers();

    } // Check if the ESC key was pressed or the window was closed
    while(glfwGetKey(GLFW_KEY_ESC) != GLFW_PRESS &&
           glfwGetWindowParam(GLFW_OPENED));

    // Deallocate buffer memory
    glDeleteBuffers(1, &vertex_buffer_id);
    glDeleteBuffers(1, &normal_buffer_id);
    glDeleteBuffers(1, &tex_coord_buffer_id);
    glDeleteTextures(1, &texture_id);
    glDeleteProgram(program_id);
    
    // Close OpenGL window and terminate GLFW
    glfwTerminate();
    exit(EXIT_SUCCESS);
}
