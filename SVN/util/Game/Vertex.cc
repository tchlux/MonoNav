#include "iostream"
#include "Vertex.h"
#include "Matrix.h"

#define SQRT_PRECISION .001 // The minimal accuracy of the square root
#define INITIAL_GUESS 1.0   // The initial guess for the square root

// Pre:  0 < num, 0 < precision
// Post: The approximate square root of num to a set digit accuracy
float sqrt(float num, float precision){
  bool flipped = num < 1.0; // if less than one, needs to be flipped
  if (flipped) num = 1 / num; // Make the number > 1
  float last = 1.0;  float guess = 2.0;
  float diff = (num-guess*guess);
  while ( diff*diff > precision){
    if (guess*guess < num){
      last = guess;
      guess = (guess+num)/2;
    }
    else
      guess = (guess+last)/2;
    diff = (num-guess*guess);
  }
  if (flipped) guess = 1 / guess; // flip back if necessary
  return(guess);
}

// Pre:  a and b are well defined
// Post: The squared distance between two vertices
float distS(const Vertex & a, const Vertex & b){
  float x = a.X-b.X;  float y = a.Y-b.Y;  float z = a.Z-b.Z;
  return( x*x + y*y + z*z );
};

// Pre:  a and b are defined
// Post: The distance between these two vertices
float distance(const Vertex & a, const Vertex & b){
  float squaredDist = distS(a,b); // Squared distance between two
  return(sqrt(squaredDist, SQRT_PRECISION));
};

// Pre:  a and b are defined
// Post: The distance between these two vertices
float dist(const Vertex & a, const Vertex & b){
  return(distance(a,b));
}

// Pre:  array is some array of information that is of length size
// Post: All the elemtns of array are printed to the terminal
void printArray(Vertex * array, int size){
  std::cerr << "[";
  for (int i=0; i<size; i++){
    std::cerr << array[i];
    if (i < size-1){
      std::cerr << ", ";
    }
  }
  std::cerr << "]" << std::endl;
}

// Pre:  Valid floats
// Post: The min of the two
float & min(float & a, float & b){
  return(a > b ? b : a);
};

// Pre:  Valid floats
// Post: The max of the two
float & max(float & a, float & b){
  return(a < b ? b : a);
};

// Pre:  mn1 <= mx1, mn2 <= mx2
// Post: If the two overlap
bool overlap(const float & mn1, const float & mx1,
	     const float & mn2, const float & mx2){
  return((mn2 <= mx1)&&(mn1 <= mx2)); // If there is overlap
};

// Does overlap but also records amount
bool overlap(const float & mn1, const float & mx1,
	     const float & mn2, const float & mx2, float & amount){
  if (mn1 < mn2)
    amount = mx1 - mn2;
  else
    amount = mx2 - mn1;
}

// Post: Coords set correspondingly
Vertex::Vertex(float x, float y, float z){ X = x; Y = y; Z = z; };

// Copy constructor
Vertex::Vertex(const Vertex & v){ X = v.X; Y = v.Y; Z = v.Z; };

// Multiplier for a float value
Vertex & Vertex::operator*=(const float & f){
  X *= f; Y *= f; Z *= f;
  return(*this);
}

// Divide operator for a floating point value
Vertex & Vertex::operator/=(const float & f){
  X /= f; Y /= f; Z /= f;
  return(*this);
}

// Equals operator
Vertex & Vertex::operator=(const Vertex & v){
  X = v.X;  Y = v.Y;  Z = v.Z; 
  return(*this);
}

// Subtraction operator for vertices
Vertex & Vertex::operator-=(const Vertex & v){
  X -= v.X; Y -= v.Y; Z -= v.Z;
  return(*this);
}

// Multiplier for a matrix
Vertex & Vertex::operator*=(const Matrix<float> & m){
  float x = X; float y = Y; float z = Z;
  X = m.get(0,0)*x + m.get(0,1)*y + m.get(0,2)*z + m.get(0,3);
  Y = m.get(1,0)*x + m.get(1,1)*y + m.get(1,2)*z + m.get(1,3);
  Z = m.get(2,0)*x + m.get(2,1)*y + m.get(2,2)*z + m.get(2,3);
  return(*this);
}

// x,y,z defined; this data set to given data
void Vertex::set(float x, float y, float z){X=x;Y=y;Z=z;};

// The squared magnitude of this vertex
float Vertex::magS() const{ 
  return(X*X + Y*Y + Z*Z); 
}

// The magnitude of this vertex
float Vertex::mag() const{ 
  return(sqrt(magS(), SQRT_PRECISION)); 
}

// Normalizes the values for this vertex
void Vertex::normalize(){ 
  float tude = mag();  
  X /= tude;   Y /= tude;   Z /= tude;
}

// Pre:  a and b are defined fully
// Post: The dot product of the two vertices is returned
float Vertex::dot(const Vertex & a, const Vertex & b){
  return( a.X*b.X + a.Y*b.Y + a.Z*b.Z );
};

// Pre:  a and b are defined fully, r stores the result
// Post: The cross product of the two vertices is returned
void Vertex::cross(const Vertex & a, const Vertex & b, Vertex & r){
  r.X = a.Y*b.Z-a.Z*b.Y;
  r.Y = a.Z*b.X-a.X*b.Z;
  r.Z = a.X*b.Y-a.Y*b.X;
};

// The data from v is sent to the outstream provided
std::ostream & operator<<(std::ostream & out, const Vertex & v){
  out << "(" << v.X << ", " << v.Y << ", " << v.Z << ")";
  return(out);
};
