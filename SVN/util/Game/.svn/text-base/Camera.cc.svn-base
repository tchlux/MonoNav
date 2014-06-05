#include <iostream>
#include <math.h>

#include "constants.h"
#include "Camera.h"
#include "PlayerClone.h"

// Post: Default constructor
Camera::Camera(){
  Projection = new Matrix<float>(MAT_INIT, MAT_SIZE, MAT_SIZE);
  View = new Matrix<float>(MAT_INIT, MAT_SIZE, MAT_SIZE);
  View->setDiagonal(1.0);  Link = NULL;
}

// Pre:  N/a
// Post: if view has been initialized then it will be deleted
Camera::~Camera(){
  if (View != NULL){
    delete(View);
  }
  if (Projection != NULL){
    delete(Projection);
  }
}

// Pre:  link is well defined
// Post: link is saved so that all operations on this apply to link
void Camera::setLink(PlayerClone * link){ Link = link; }

// The pointer to Link is returned
PlayerClone * Camera::getLink() const { return(Link); }

// Pre:  setMem has been used to set all the member data
// Post: The view matrix is set to orthographic mode
void Camera::ortho(){
  float tx = -((Right+Left)/(Right-Left));
  float ty = -((Top+Bottom)/(Top-Bottom));
  float tz = -((FarVal+NearVal)/(FarVal-NearVal));
  (*Projection)[0][0] = 2.0 / (Right-Left);  (*Projection)[1][1] = 2.0 / (Top-Bottom);
  (*Projection)[2][2] = 2.0 / (FarVal-NearVal); (*Projection)[3][3] = 1.0f;
  (*Projection)[0][3] = tx; (*Projection)[1][3] = ty; (*Projection)[2][3] = tz;
}

// Pre:  setMem has been used to set all the member data
// Post: The view matrix is set to perspective mode
void Camera::persp(){
  float col2Data[MAT_SIZE] = {(Right+Left)/(Right-Left), 
			      (Top+Bottom)/(Top-Bottom),
			      -((FarVal+NearVal)/(FarVal-NearVal)),
			      -1.0f};
  Projection->setCol(2, col2Data); // Set the column of data to (*Projection)
  (*Projection)[0][0] = (2.0*NearVal)/(Right-Left); // Set the diagonal Projection
  (*Projection)[1][1] = (2.0*NearVal)/(Top-Bottom);
  (*Projection)[2][3] = (-2.0*FarVal*NearVal)/(FarVal-NearVal);
}

// Pre:  l<r, b<t, nv<fv
// Post: The member data is set for this camera
void Camera::setMem(float l, float r, float b, 
		    float t, float nv, float fv){
  Left = l; Right = r; Bottom = b; Top = t; NearVal = nv; FarVal = fv;
}

// Pre:  x, y, and z are defined
// Post: The current matrix for 
void Camera::translate(float x, float y, float z){
  Matrix<float> trans(MAT_INIT, MAT_SIZE, MAT_SIZE);
  trans.setDiagonal(VECTOR_INIT); // Make the diagonal 1.0
  float values[MAT_SIZE] = {x,y,z,1.0}; // To set the values in trans
  trans.setCol(MAT_SIZE-1, values); // Push the values to trans
  View = &(trans * (*View)); // Multiply in these values
  if (Link != NULL)
    Link->translate(-x,-y,-z);
}

// Pre:  amount is defined, (x,y,z) == 0 or 1
// Post: The current view is rotated appropriately by degrees
void Camera::rotate(float amount, float x, float y, float z){      
  //// HACK ////
  translate(0.0f, 0.0f, -1.0f);
  if (Link != NULL)
    Link->translate(0.0f, 0.0f, -1.0f);
  //// HACK ////

  Matrix<float> rot(MAT_INIT, MAT_SIZE, MAT_SIZE);
  rot.setDiagonal(VECTOR_INIT);
  float cosa = cos(amount*RADIANS_CONVERT);
  float sina = sin(amount*RADIANS_CONVERT);
  if (x != 0){
    rot[1][1] = rot[2][2] = cosa;
    rot[1][2] = -(rot[2][1] = sina);
  }
  if (y != 0){
    rot[0][0] = rot[2][2] = cosa;
    rot[2][0] = -(rot[0][2] = sina);
  }
  if (z != 0){
    rot[0][0] = rot[1][1] = cosa;
    rot[0][1] = -(rot[1][0] = sina);
  }
  View = &( rot * (*View));
  //  View = &( (*View) * rot);
  if (Link != NULL)
    Link->rotate(-amount,x,y,z);

  //// HACK ////
  translate(0.0f, 0.0f, 1.0f);
  if (Link != NULL)
    Link->translate(0.0f, 0.0f, 1.0f);
  //// HACK ////
}

  // float zValue[MAT_SIZE] = {0.0,0.0,1.0,1.0};
  // trans.setCol(MAT_SIZE-1, zValue); // Push the values to trans
  // View = &(trans * (*View)); // Multiply in these values

