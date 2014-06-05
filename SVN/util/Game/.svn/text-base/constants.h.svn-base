#ifndef INCLUDED_CONSTANTS
#define INCLUDED_CONSTANTS

// ===================
//      viewGL.cc     
// ===================

#define WINDOW_TITLE "Game" // Title of the GL window

#define CLEAR 0.001f  // Clearl color for the window

#define NUM_TEXTURES 1 // How many textures will be used
#define SWAP_INTERVAL 1 // How many times the monitor must vertically
                        // sync before the buffer is swapped
#define STRINGS_IN_SHADER 1 // Number of strings in the shader file
#define LENGTH_SHADER_STRINGS NULL // Null if all strings in shader
                                   // file are terminated
#define VERTEX_SHADER "vertex"
#define FRAGMENT_SHADER "fragment"

// ==================
//      Model.cc     
// ==================

#define MIDPOINT 2.0	    // The midpoint between two halves
#define AV_OF_THREE 3.0	    // Average of 3 numbers
#define BOUNDING_BOX_SIZE 8 // Number of elements in the bBox
#define NORMAL_BOX_SIZE 3   // Number of normals for bBox
#define NUM_MATRICES 1      // Number of matrices to be sent to the
                            //graphics card
#define NEEDS_TRANSPOSE false // Whether or not the matrix needs to be
			      // transposed before used on graphics
#define STRIDE 0	    // The stride between vertices in the
			    // vertex array given to openGL
#define START_IND 0         // Starting index of vertices
#define DEFAULT_ID -1       // The default id for vbo's
#define ONE_VBO_ID 1        // To make code more explicit
#define COORDS_PER_TEXT 2   // The number of coordinates per texture
#define FACE_DATA_SET 3     //Set size in face data
#define BYTES_PER_FLOAT 4   //Number of bytes in one float
#define FLOATS_PER_VERTEX 3 //How many floats are in a vertex
#define FLOATS_PER_NORMAL 3 // How many floats are in a normal
#define NUM_AXIS 3          //Number of axis, or coordinates, used
#define SPACE ' '           //Used for retrieving numbers from lines
#define SLASH '/'           //Used for splitting face and normal data
#define MAT_NOT_FOUND NULL  //Signals that a material was not found

#define VERTEX_SYMBOL "v"   //Symbol in obj file for a vertex
#define VERTEX_NORMAL_SYMBOL "vn" // Symbol for a vertex normal
#define VERTEX_TEXTURE_SYMBOL "vt" // Symbol for a vertex texture
#define FACE_SYMBOL "f"     //Symbol in obj file for a face line
#define MAT_FILE_SYMBOL "mtllib" //symbol for material file
#define USE_MAT_SYMBOL "usemtl"  //symbol for material usage
#define NEW_MAT_SYMBOL "newmtl" // New material

#define DRAW_WITH_COLOR true //Whether or not to use color in drawing


// ====================
//      Material.h     
// ====================

#define CHANNELS 4 // The number of color feeds in the ka,kd,ks
#define BYTES_PER_PIXEL 4 // Number of bytes per pixel information in
                          // file 
#define DEFAULT_ALPHA 255 // Default alpha value for textures

// =====================
//      Material.cc     
// =====================

#define MAX_LINE_LENGTH 100	// Max characters in a mat/obj file line
#define MATERIAL_NAME 1         // Index loaction of mat name in split
#define PPM_HEADER_SIZE 4	// Lines in a ppm header
#define WH_HEADER_LINE 2	// The line with width height info
#define WIDTH_INDEX 0		// Index of width in WH_HEADER_LINE
#define HEIGHT_INDEX 1		// Index of height in WH_HEADER_LINE
#define SPACE ' '		// Used for splitting lines
#define KA_SYMBOL "Ka"		// Ka values
#define KD_SYMBOL "Kd"		// Kd values
#define KS_SYMBOL "Ks"		// Ks values
#define NS_SYMBOL "Ns"		// Ns value
#define MAP_KD_SYMBOL "map_Kd"  // Symbol for declaring a texture .ppm
#define IMAGE_LEVEL 0		// Image level-of-detail, 0 is base
#define IMAGE_BORDER 0		// Image border used
#define DEFAULT_MATERIAL_NAME "Default"  // Default mat identifier
#define DEFAULT_FOURTH_CH 1.0   // Default for fourth channels
#define DEFAULT_MAT_KA 0.1      // Default for ka's
#define DEFAULT_MAT_KD 1.0	// Default for kd's
#define DEFAULT_MAT_KS 1.0	// Default for ks's
#define DEFAULT_MAT_NS 100.0	// Default ns value


// ==================
//      Clone.cc     
// ==================

#define PI 3.14159265359 // Used for mathematical approximations
#define RADIANS_CONVERT PI/180.0 // Converts degrees to radians
#define MAT_INIT 0.0f
#define MAT_SIZE 4
#define VECTOR_INIT 1.0
#define X_IND 0
#define Y_IND 1
#define Z_IND 2
#define CLONE_SPEED .03 // The speed that clones travel at for now
#define DEFAULT_COORD 0.0
#define X_VALUE 0][3     // Where the x coord is in a matrix
#define Y_VALUE 1][3     // Where the y coord is in a matrix
#define Z_VALUE 2][3     // Where the z coord is in a matrix
#define REMAINING_NORMALS_SIZE 9
#define DEFAULT_BOUNCE_DEGRADATION 0.0 // no bounce

// =======================
//      Quaternion.cc    
// =======================

#define QUATERNION_SIZE 4 // The size of a quaternion

// =================
//      Shaders     
// =================

#define MATRIX_SIZE 16 // Element in matrix
#define NUMPROGS 4 // Number of shader programs to be made

#define V_SHADER 0    // Index of vertex shader
#define VT_SHADER 1   // Index of vertex-texture shader
#define VN_SHADER 2   // Index of vertex-normal shader
#define VTN_SHADER 3  // Index of vertex-texture-normal shader
// ^ These variables are also used as increments for data extraction


#define V_VSHADER_FILE "v.vert"
#define VT_VSHADER_FILE "vt.vert"
#define VN_VSHADER_FILE "vn.vert"
#define VTN_VSHADER_FILE "vtn.vert"

#define V_FSHADER_FILE "v.frag"
#define VT_FSHADER_FILE "vt.frag"
#define VN_FSHADER_FILE "vn.frag"
#define VTN_FSHADER_FILE "vtn.frag"

//===========================
//     Shaders' Attributes     
//===========================

#define VERTEX_3F "vertex_3f"
#define NORMAL_3F "normal_3f"
#define TEX_COORD_2F "tex_coord_2f"

#define MODEL_VIEW_PROJECTION_MATRIX4F "model_view_projection_matrix4f"
#define MODEL_VIEW_MATRIX4F "model_view_matrix4f"
#define NORMAL_MATRIX4F "normal_matrix4f"

#define TEXTURE_SAMPLER "textureSampler"

#define AMBIENT_COLOR_4F "ambient_color_4f"
#define DIFFUSE_COLOR_4F "diffuse_color_4f"
#define SPECULAR_COLOR_4F "specular_color_4f"
#define SPECULAR_COEFFICIENT_1F "specular_coefficient_1f"
#define LIGHT_POSITION_3F "light_position_3f"
#define LIGHT_COLOR_4F "light_color_4f"
#define ATTENUATION_FACTOR_1F "attenuation_factor_1f"

#define MAXATTS 17 // The number of attributes in the largest shader

#define pID 0     // The program id's
#define vShadID 1 // The vertex shader ID's
#define fShadID 2 // The fragment shader ID's
#define mvpID 3 // Model view projection matrix id's
#define mvID  4 // Model view matrix id's
#define nmID  5 // Normal matrix id's
#define aID   6 // Ambient color id's	      
#define dID   7 // Diffuse color id's	      
#define sID   8 // Specular color id's	      
#define scID  9 // Specular coefficient id's  
#define lpID  10 // Light position id's	       
#define lcID  11 // Light color id's	       
#define afID  12 // Attenuation factor id's    
#define tsID  13 // Texture sampler id's       

#define vID   14 // Vertex (individual set in obj) id
#define nID   15 // Normal (individual set in obj) id
#define tcID  16 // Text coord (individual set in obj) id

class Clone;
class PlayerClone;
class Camera;
class viewGL;
class Model;
class Material;
class Vertex;
class Shaders;

#endif
