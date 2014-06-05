//========================================================================
// This is a small test application for GLFW.
// The program opens a window (640x480),
// and renders a flat shaded sphere.
//========================================================================

#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>
#include <GL/glfw.h>

#include <cmath> //Math library for trig functions
#include <iostream> //used for cerr

#define PI 3.14159265358979 //approximation of pi
#define NUMVERTS 4  //Vertices per slice, squared for total
#define REPEAT_VERT 6 //how many times each vertex is used
#define TRIANGLE_VERTS NUMVERTS*NUMVERTS * REPEAT_VERT //total length
                                   //of the array for the GLtriangles
#define MAXTHETA 2.0*PI //Max theta used
#define RADIUS 1.0 //radius of circle
#define Y_OFFSET 1 //y_offset from x_vertex location in array
#define Z_OFFSET 2 //z_offset from x_vertex location in array
#define COORDS_PER_VERT 3 //Number of coordinates per vertex
#define CIRCLE NUMVERTS*COORDS_PER_VERT //Indices per circle

const int BYTES_PER_VERTEX = 4*3;

  // std::cerr << "sphere.cc Line 36:" << std::endl;
  // std::cout << "thetaInc"<<thetaInc << std::endl;
  // std::cout << "MAXTHETA"<<MAXTHETA << std::endl;
  // std::cout << "NUMVERTS"<<NUMVERTS << std::endl;
  //   std::cout << "z_theta"<<z_theta << std::endl;
  //   std::cout << "z_radius"<<z_radius << std::endl;


// Pre:  vertices is an initialized array of size NUMVERTS**2
// Post: All unique vertices are placed into the array linearly
void createVerts(GLfloat * vertices){
  float thetaInc = MAXTHETA / NUMVERTS; //increment for theta
  GLfloat z_radius; //storage for radius of z-slice
  GLfloat x, y, z; //x,y,z coordinates
  int vertex = 0; //current vertex
  for (float z_theta=0.0; z_theta<PI; z_theta+=(PI/NUMVERTS)){
    z_radius = RADIUS * sin(z_theta); // the radius of this slice
    z = RADIUS * cos(z_theta); //the z coordinate of this slice
    for (float x_theta=0.0; x_theta<MAXTHETA; x_theta+=thetaInc){
      x = z_radius * sin(x_theta); //x coord
      y = z_radius * cos(x_theta); //y coord
      vertices[vertex] = x;
      vertices[vertex+Y_OFFSET] = y;
      vertices[vertex+Z_OFFSET] = z;
      vertex += COORDS_PER_VERT;
    }    
  }  
}

// Pre:  sVerts -> # unique vertices * COORDS_PER_VERT
//       length of verts == length of sVerts*COORDS_PER_VERT
//       length of colors == length of sVerts*COORDS_PER_VERT
// Post: The arrays 'verts' and 'colors' are filled with vertices and
//       varying colors for telling them apart
void createTriangles(GLfloat * sVerts, GLfloat * verts, GLfloat * colors){
  int slice1Start; //The start of the slice
  int slice2Start; //The start of the adjacent slice
  int vert1Start;  //The start of the current vertex
  int vert2Start;  //The start of the adjacent vertex
  int vert3Start;  //The start of the final vertex
  int ind = 0;     //Current index in sVerts
  for (int slice=0; slice<=(NUMVERTS+1); slice++){
    slice1Start = slice * CIRCLE; //The starting
    //index of this slice
    slice2Start = ((slice+1)%NUMVERTS) * CIRCLE;
    //and the next 
    for (int circ=0; circ<=NUMVERTS; circ+=2){ //increment by two,
      //       because two triangles have been made on this run
      vert1Start = slice1Start+(circ%NUMVERTS)*COORDS_PER_VERT; //The
      //starting index of current vertex
      vert2Start = slice2Start+(circ%NUMVERTS)*COORDS_PER_VERT;
	//and the adjacent
      vert3Start = slice1Start+((circ+1)%NUMVERTS)*COORDS_PER_VERT;

      // Get the first vertex
      verts[vert1Start] = sVerts[ind];
      colors[vert1Start] = ((float) ind) / TRIANGLE_VERTS;

      verts[vert1Start+Y_OFFSET] = sVerts[ind+Y_OFFSET];
      colors[vert1Start+Y_OFFSET] = ((float) ind) / TRIANGLE_VERTS;

      verts[vert1Start+Z_OFFSET] = sVerts[ind+Z_OFFSET];
      colors[vert1Start+Z_OFFSET] = ((float) ind) / TRIANGLE_VERTS;

      ind++; //increment to next vertex
      verts[vert2Start] = sVerts[ind];
      colors[vert2Start] = ((float) ind) / TRIANGLE_VERTS;
      verts[vert2Start+Y_OFFSET] = sVerts[ind+Y_OFFSET];
      colors[vert2Start+Y_OFFSET] = ((float) ind) / TRIANGLE_VERTS;
      verts[vert2Start+Z_OFFSET] = sVerts[ind+Z_OFFSET];
      colors[vert2Start+Z_OFFSET] = ((float) ind) / TRIANGLE_VERTS;
      ind++; //increment to final vertex
      verts[vert3Start] = sVerts[ind];
      colors[vert3Start] = ((float) ind) / TRIANGLE_VERTS;
      verts[vert3Start+Y_OFFSET] = sVerts[ind+Y_OFFSET];
      colors[vert3Start+Y_OFFSET] = ((float) ind) / TRIANGLE_VERTS;
      verts[vert3Start+Z_OFFSET] = sVerts[ind+Z_OFFSET];
      colors[vert3Start+Z_OFFSET] = ((float) ind) / TRIANGLE_VERTS;
      ind--; //decrement back to first vertex of next triangle

      // Shift the vertices, and get the next one to complete a square
      vert1Start = vert2Start;
      vert2Start = vert3Start;
      vert3Start = slice2Start+((circ+1)%NUMVERTS)*COORDS_PER_VERT;

      // Get the first vertex
      verts[vert1Start] = sVerts[ind];
      verts[vert1Start+Y_OFFSET] = sVerts[ind+Y_OFFSET];
      verts[vert1Start+Z_OFFSET] = sVerts[ind+Z_OFFSET];
      ind++; //increment to next vertex
      verts[vert2Start] = sVerts[ind];
      verts[vert2Start+Y_OFFSET] = sVerts[ind+Y_OFFSET];
      verts[vert2Start+Z_OFFSET] = sVerts[ind+Z_OFFSET];
      ind++; //increment to final vertex
      verts[vert3Start] = sVerts[ind];
      colors[vert3Start] = ((float) ind) / TRIANGLE_VERTS;
      verts[vert3Start+Y_OFFSET] = sVerts[ind+Y_OFFSET];
      colors[vert3Start+Y_OFFSET] = ((float) ind) / TRIANGLE_VERTS;
      verts[vert3Start+Z_OFFSET] = sVerts[ind+Z_OFFSET];
      colors[vert3Start+Z_OFFSET] = ((float) ind) / TRIANGLE_VERTS;
      ind--; //decrement back to first vertex of next triangle

    }
  }
}


int main(void) {
    int width, height;          // Window width and height
    float ratio;                // Window aspect ratio
    float x_rot = 0.0f;         // X rotation scaling factor
    float y_rot = 0.0f;         // Y rotation scaling factor
    float delta_rot = 1.0f;     // Ammount rotation changes on key press
    int number_of_vertices = TRIANGLE_VERTS; // Number of vertices in buffer
    int buffer_size = number_of_vertices * BYTES_PER_VERTEX;

    GLfloat singleVertices[NUMVERTS*NUMVERTS*COORDS_PER_VERT]; //get the vertices
    createVerts(singleVertices); //fill the array w/ all unique verts

    GLfloat vertices[TRIANGLE_VERTS]; // Initialize vertex array 
    GLfloat colors[TRIANGLE_VERTS];   // Initialize color array

    createTriangles(singleVertices, vertices, colors); //fill the
    
    // for(int i=0; i<(NUMVERTS*NUMVERTS*COORDS_PER_VERT); i++){
    //   std::cerr << singleVertices[i] << std::endl;      
    // }
    
    // delete(singleVertices); //delete the now useless array of vertices
    //    that made up the sphere

    //    final arrays for OpenGL to use during rendering
    GLuint vertex_buffer_id, color_buffer_id; // vertex buffer id's
    // Initialize GLFW

    if(!glfwInit()) {
        fprintf(stderr, "Failed to initialize GLFW\n");
        exit(EXIT_FAILURE);
    }
    std::cerr << "sphere.cc Line 156: " << std::endl;
    // Open a window and create its OpenGL context
    if(!glfwOpenWindow(640, 480, 0, 0, 0, 0, 16, 0, GLFW_WINDOW)) {
        fprintf(stderr, "Failed to open GLFW window\n");
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    glfwSetWindowTitle("Sphere");
    if(glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to initialize OpenGL Extensions\n");
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    std::cerr << "sphere.cc Line 163: " << std::endl;
    // Ensure we can capture the escape key being pressed below
    glfwEnable( GLFW_STICKY_KEYS );

    // Enable vertical sync (on cards that support it)
    glfwSwapInterval(1);

    // Create vertex buffer
    glGenBuffers(1, &vertex_buffer_id);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_id);
    std::cerr << "sphere.cc Line 174: " << std::endl;
    std::cout << "" << std::endl;
    glBufferData(GL_ARRAY_BUFFER, buffer_size, vertices, GL_STATIC_DRAW);
    std::cerr << "sphere.cc Line 179: " << std::endl;
    // Create color buffer
    glGenBuffers(1, &color_buffer_id);
    glBindBuffer(GL_ARRAY_BUFFER, color_buffer_id);
    glBufferData(GL_ARRAY_BUFFER, buffer_size, colors, GL_STATIC_DRAW);

    // enable depth testing
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);


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

	//	std::cerr << "sphere.cc Line: DEATH" << std::endl;

	// Draw sphere using vertex buffer object
	glEnableClientState(GL_VERTEX_ARRAY);
	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_id);
	glVertexPointer(3, GL_FLOAT, 0, NULL);
	glEnableClientState(GL_COLOR_ARRAY);
	glBindBuffer(GL_ARRAY_BUFFER, color_buffer_id);
	glColorPointer(3, GL_FLOAT, 0, NULL);
	glDrawArrays(GL_TRIANGLES, 0, number_of_vertices);


        // Swap buffers
        glfwSwapBuffers();

    } // Check if the ESC key was pressed or the window was closed
    while(glfwGetKey(GLFW_KEY_ESC) != GLFW_PRESS &&
           glfwGetWindowParam(GLFW_OPENED));

    // Deallocate buffer memory
    glDeleteBuffers(1, &vertex_buffer_id);
    glDeleteBuffers(1, &color_buffer_id);
    
    // Close OpenGL window and terminate GLFW
    glfwTerminate();
    exit(EXIT_SUCCESS);
}
