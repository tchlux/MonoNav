#ifndef INCLUDED_VERTEX
#define INCLUDED_VERTEX

#include "iostream"
#include "constants.h"
#include "Matrix.h"

// Pre:  a and b are well defined
// Post: The squared distance between two vertices
float distS(const Vertex & a, const Vertex & b);

// Pre:  0 < num, 0 < precision
// Post: The approximate square root of num to a set digit accuracy
float sqrt(float num, float precision);

// Pre:  a and b are defined
// Post: The distance between these two vertices
float distance(const Vertex & a, const Vertex & b);

// Pre:  a and b are well defined
// Post: The approximate distance between two vertices
float dist(const Vertex & a, const Vertex & b);

// Pre:  array is some array of information that is of length size
// Post: All the elemtns of array are printed to the terminal
void printArray(Vertex * array, int size);

// Pre:  Valid floats
// Post: The min of the two
float & min(float & a, float & b);

// Pre:  Valid floats
// Post: The max of the two
float & max(float & a, float & b);

// Pre:  mn1 <= mx1, mn2 <= mx2, amount is initialized
// Post: If the two overlap, the amount they overlap is stored
bool overlap(const float & mn1, const float & mx1,
	     const float & mn2, const float & mx2);

// Does overlap but also records amount
bool overlap(const float & mn1, const float & mx1,
	     const float & mn2, const float & mx2, float & amount);

class Vertex{
  // This will be used by clone to test collisions, provides simple
  //  storage and vector operations
public:
  float X, Y, Z;
    
  // Post: All coords set to default value
  Vertex(){ X = Y = Z = DEFAULT_COORD; };

  // Copy constructor
  Vertex(const Vertex & v);

  // Multiplier for a float value
  Vertex & operator*=(const float & f);

  // Divide operator for a floating point value
  Vertex & operator/=(const float & f);

  // Equals operator
  Vertex & operator=(const Vertex & v);

  // Subtraction operator for vertices
  Vertex & operator-=(const Vertex & v);

  // Multiplier for a matrix
  Vertex & operator*=(const Matrix<float> & other);

  // Post: Coords set correspondingly
  Vertex(float x, float y, float z);

  // x,y,z defined; this data set to given data
  void set(float x, float y, float z);

  // array is at least of length 3, These coords are saved to array
  void array(float * array) const {array[0]=X;array[1]=Y;array[2]=Z;}

  // The squared magnitude of this vertex
  float magS() const;

  // The magnitude of this vertex
  float mag() const;

  // Normalizes the values for this vertex
  void normalize();

  // Pre:  a and b are defined fully
  // Post: The dot product of the two vertices is returned
  static float dot(const Vertex & a, const Vertex & b);

  // Pre:  a and b are defined fully, r stores the result
  // Post: The cross product of the two vertices is returned
  static void cross(const Vertex & a, const Vertex & b, Vertex & r);


  // The data from v is sent to the outstream provided
  friend std::ostream & operator<<(std::ostream & out, const Vertex & v);
};

#endif
