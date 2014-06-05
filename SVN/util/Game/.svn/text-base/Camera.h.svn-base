#ifndef DEFINED_CAMERA
#define DEFINED_CAMERA

#include <iostream>
#include "Matrix.h"
#include "PlayerClone.h"

class Camera{
  // CI: This class will hold the view matrix for the final projectshns
private:
  float Left;  float Right;
  float Bottom;  float Top;
  float NearVal;  float FarVal;
  Matrix<float> * View; // This holds the view matrix for the camera
  Matrix<float> * Projection; // Holds the projection matrix for draw
  PlayerClone * Link; // A clone that is linked to this camera
  
public:

  // Post: Default constructor
  Camera();

  // Destroys persp if it was initialized
  ~Camera();

  float left(){return(Left);};
  float right(){return(Right);};

  // Pre:  link is well defined
  // Post: link is saved so that all operations on this apply to link
  void setLink(PlayerClone * link);

  // The pointer to Link is returned
  PlayerClone * getLink() const;

  // Pre:  l<r, b<t, nv<fv
  // Post: Sets the view matrix to an orthographic view
  void ortho();

  // Post: Sets the view matrix to an perspsective view
  void persp();

  // Pre:  l<r, b<t, nv<fv
  // Post: The member data is set for this camera
  void setMem(float l, float r, float b, float t, float nv, float fv);

  // Pre:  x, y, and z are defined
  // Post: The current matrix for 
  void translate(float x, float y, float z);

  // Pre:  amount is defined, (x,y,z) == 0 or 1
  // Post: The current persp is rotated appropriately by degrees
  void rotate(float amount, float x, float y, float z);

  // This will return the view matrix array
  Matrix<float> * view(){ return(View); };

  // This will return the projection matrix array
  Matrix<float> * projection(){ return(Projection); };

};

#endif
