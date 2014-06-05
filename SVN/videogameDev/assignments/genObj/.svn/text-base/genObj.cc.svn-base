#include <iostream>
#include <fstream>
#include <vector>
#include <cmath> //Math library for trig functions

#define NUMVERTS 9  //Vertices per slice, squared for total
#define RADIUS 0.8 //radius of circle
//5,.4

#define PI 3.14159265358979 //approximation of pi
#define REPEAT_VERT 6 //how many times each vertex is used
#define TRIANGLE_VERTS NUMVERTS*NUMVERTS * REPEAT_VERT //total length
                                   //of the array for the GLtriangles
#define MAXTHETA 2.0*PI //Max theta used
#define Y_OFFSET 1 //y_offset from x_vertex location in array
#define Z_OFFSET 2 //z_offset from x_vertex location in array
#define COORDS_PER_VERT 3 //Number of coordinates per vertex
#define CIRCLE NUMVERTS*COORDS_PER_VERT //Indices per circle

#define FILENAME "temp.obj"

using namespace std;

// Pre:  vertices is an initialized array of size NUMVERTS**2
// Post: All unique vertices are placed into the array linearly
void createVerts(vector<float> & vertices, float numverts){
  float thetaInc = MAXTHETA / numverts; //increment for theta
  float z_radius; //storage for radius of z-slice
  float x, y, z; //x,y,z coordinates
  int vertex = 0; //current vertex
  for (float z_theta=0.0; z_theta<=PI; z_theta+=(PI/numverts)){
    z_radius = RADIUS * sin(z_theta); // the radius of this slice
    z = RADIUS * cos(z_theta); //the z coordinate of this slice
    for (float x_theta=0.0; x_theta<=MAXTHETA; x_theta+=thetaInc){
      x = z_radius * sin(x_theta); //x coord
      y = z_radius * cos(x_theta); //y coord
      vertices.push_back(x);
      vertices.push_back(y);
      vertices.push_back(z);
    }    
  }  
}

// Pre:  faces is defined, numverts > 0
// Post: The face vector is filled
void createFaces(vector<int> & faces, int numVerts){
  vector<int> level;
  level.push_back(0);
  for(int i=0; i<numVerts; i+=NUMVERTS){
    for (int n=1; n<=NUMVERTS; n++){
      faces.push_back(level[(n-1)%level.size()]);
      faces.push_back(level[(n-1)%level.size()]+NUMVERTS);
      faces.push_back(level[(n-1)%level.size()]+NUMVERTS+1);
    }
    for (int n=1; n<=NUMVERTS; n++){
      faces.push_back(level[(n-1)%level.size()]);
      faces.push_back(level[(n-1)%level.size()]+NUMVERTS+1);
      faces.push_back(level[(n)%level.size()]);
    }
    level.clear();
    for (int n=1; ((n<=NUMVERTS)&&(n+i<numVerts)); n++){
      level.push_back(n+i);
    }
  }
}

//r,g,b;
//b,g,r;

//1,1,0;
//0,1,1;


// Pre:  verts is defined, verts.size() > 0, outFile is terminated
// Post: The elements of verts are written to a file named 'outName'
void writeVerts(ofstream & outFile, vector<float> & verts){
  for (int i=1; i<=verts.size(); i++){
    outFile << verts[i-1] << " ";
    if (i % 3  ==  0){
      outFile << endl << "v ";
    }
  }
}

// Pre:  norms is defined, norms.size() > 0, outFile is terminated
// Post: The elements of norms are written to a file named 'outName'
void writeNorms(ofstream & outFile, vector<float> & norms){
  for (int i=1; i<=norms.size(); i++){
    outFile << norms[i-1] << " ";
    if (i % 3  ==  0){
      outFile << endl << "vn ";
    }
  }
}

// Pre:  faces is defined, faces.size() > 0, outFile is terminated
// Post: The elements of faces are written to a file named 'outName'
void writeFaces(ofstream & outFile, vector<int> & faces){
  for (int i=1; i<=faces.size(); i++){
    outFile << faces[i-1]+1 << "//" << faces[i-1]+1 << " ";
    if (i % 3  ==  0){
      outFile << endl << "f ";
    }
  }
}

void writeVertsFaces(vector<float> & verts, vector<int> & faces, 
		     const char * outName){
  ofstream outFile(outName);
  outFile << "v ";
  writeVerts(outFile, verts);
  outFile << endl;
  writeNorms(outFile, verts);
  writeFaces(outFile, faces);
  outFile.close();
}



// Pre:  
// Post: used for generating obj files
int main(int argc, char * argv[]){
  vector<float> vertices;
  vector<int> faces;
  createVerts(vertices, NUMVERTS);
  createFaces(faces, NUMVERTS*NUMVERTS - (NUMVERTS-2));
  writeVertsFaces(vertices, faces, FILENAME);
  return(0);
};
