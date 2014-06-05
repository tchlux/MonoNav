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

#define PI 3.141592653589793238463
#define BYTES_PER_FLOAT 4
#define FLOATS_PER_QUAD 18
#define FLOATS_PER_VERTEX 3

#include <fstream>

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

  unsigned char * texture_data;
    GLfloat tex_coords[];

    int vertices_length = 9;    // number of floats in vertex array
    int tex_coords_length = 6;  // number of floats in texture coord array
    int buffer_size;            // number of bytes in vbo
    GLuint vertex_buffer_id;    // vertex buffer handle
    GLuint normal_buffer_id;    // normal buffer handle
    GLuint tex_coord_buffer_id; // texture coordinate buffer handle

    // Load texture
    glGenTextures(1, &texture_id);
    glBindTexture(GL_TEXTURE_2D, texture_id);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 4, 2, 0, GL_RGB, GL_UNSIGNED_BYTE, &texture_data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
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


    do {
	// Bind texture to texture unit 0
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture_id;

	// Set shader attribute variables to vbo's
	glUniform4f(ambient_id, 0.1f, 0.1f, 0.1f, 1.0f);
	glUniform4f(diffuse_id, 1.0f, 1.0f, 1.0f, 1.0f);
	glUniform4f(specular_id, 1.0f, 1.0f, 1.0f, 1.0f);
	glUniform1f(specular_coefficient_id, 100.0f);

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
