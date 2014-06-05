#include <iostream>
#include <cmath>
#include "constants.h"
#include "Vertex.h"
#include "Matrix.h"
#include "Model.h"
#include "Clone.h"

// Pre:  Maker is a well defined Model object, similare of camera
// Post: This clone is initialized
Clone::Clone(Model * model, Camera * cam){
  modelMatrix = new Matrix<float>(MAT_INIT,MAT_SIZE,MAT_SIZE); 
  modelMatrix->setDiagonal(1.0);
  Maker = model; Cam = cam;
  Center = Maker->Center;
  Radius = Maker->Radius;
  Momentum = model->Momentum; // The momentum of this clone
}

// Pre:  N/a
// Post: if modelMatrix has been initialized then it will be deleted
Clone::~Clone(){
  if (modelMatrix != NULL){
    delete(modelMatrix);
  }
}

// Post: Returns the vertex that represents this clone's position
Vertex & Clone::pos(){ return(Center); }

// Post: Returns the vertex that represents this clone's position
Vertex & Clone::position(){ return(Center); }

// Pre:  x,y,z are defined valid coordinates
// Post: The model matrix is set to this location
void Clone::move(float x, float y, float z){
  float pos[MAT_SIZE] = {x,y,z,VECTOR_INIT};
  modelMatrix->setCol(MAT_SIZE-1, pos);
  Center.set(x,y,z); // Move the center accordingly
}

// Pre:  x, y, and z are defined
// Post: The current matrix for 
void Clone::translate(float x, float y, float z){
  Matrix<float> trans(MAT_INIT, MAT_SIZE, MAT_SIZE);
  trans.setDiagonal(VECTOR_INIT); // Make the diagonal 1.0
  float values[MAT_SIZE] = {x,y,z,1.0}; // To set the values in trans
  trans.setCol(MAT_SIZE-1, values); // Push the values to trans
  modelMatrix = &((*modelMatrix) * trans); // Multiply in these values

  Center.set((*modelMatrix)[0][3],
	     (*modelMatrix)[1][3],
	     (*modelMatrix)[2][3]);// Move center along with
}

// Pre:  amount is defined in degrees, (x,y,z) == 0 or 1
// Post: The current modelMatrix is rotated appropriately by degrees
void Clone::rotate(float amount, float x, float y, float z){      
  Matrix<float> rotat(MAT_INIT, MAT_SIZE, MAT_SIZE);
  rotat.setDiagonal(VECTOR_INIT);
  float cosa = cos(amount*RADIANS_CONVERT);
  float sina = sin(amount*RADIANS_CONVERT);
  if (x != 0){
    rotat[1][1] = rotat[2][2] = cosa;
    rotat[1][2] = -(rotat[2][1] = sina);
  }
  if (y != 0){
    rotat[0][0] = rotat[2][2] = cosa;
    rotat[2][0] = -(rotat[0][2] = sina);
  }
  if (z != 0){
    rotat[0][0] = rotat[1][1] = cosa;
    rotat[0][1] = -(rotat[1][0] = sina);
  }
  modelMatrix = &((*modelMatrix) * rotat);
}

// Pre:  x,y,z are all positive scalar factors
// Post: The model is scaled by the amount given
void Clone::scale(float x, float y, float z){
  float scalar[MAT_SIZE] = {x,y,z,VECTOR_INIT};
  Matrix<float> scale(MAT_INIT, MAT_SIZE, MAT_SIZE);
  scale.setDiagonal(scalar);
  modelMatrix = &((*modelMatrix) * scale);
  Radius *= (x+y+z)/3; // Scale the radius appropriately
  Momentum /= (x*y*z); // Scale the momentum appropriately
}

// Pre:  The modelMatrix is initialized, cam is stored in this
// Post: This model instance is drawn
void Clone::draw(){
  draw(Cam->view(), Cam->projection());
}

// Pre:  The modelMatrix is initilaized
// Post: The model is drawn to this location
void Clone::draw(const Matrix<float> * view, 
		 const Matrix<float> * projection){
  Matrix<float> * mv = &((*view) * (*modelMatrix)); // new
  Matrix<float> * mvp = &((*projection) * (*mv));   // new
  Matrix<float> normal(*mv);   normal.inverse(); normal.transpose();
  // Create another matrix for the normal that is the inverse of the
  // model-view 
  float * mvArray = mv->array();   // new
  float * mvpArray = mvp->array(); // new
  float * nArray = normal.array(); // new
  Maker->draw(mvArray, mvpArray, nArray);  // Draw with that modelMatrix
  delete(mv);  delete(mvp); // Delete the matrices
  delete(mvArray); delete(mvpArray); delete(nArray);
  //glUniformMatrix4fv(matrix_id (attribute name in shader),
  //                   1, GL_TRUE (Row major order), 1-D array data)
}

// Pre:  out and clone are defined properly
// Post: The information in clone is sent to this ostream
std::ostream & operator<<(std::ostream & out, Clone & clone){
  out << "CLONE:: MEMBER __ DATA: " << std::endl;
  out << *(clone.Maker) << std::endl;
  out << *(clone.modelMatrix);
  return(out);
}

// Pre:  dot is s clone that should be drawn at each vertex of bBox
// Post: All of the bBox corners of this clone are
//       highlighted with the 'dot' clone
void Clone::drawBBox(Clone & dot){
  Vertex pos;
  for (int b=0; b<BOUNDING_BOX_SIZE; b++){      
    pos = Maker->bBox[b];          pos *= *(modelMatrix);
    dot.move(pos.X,pos.Y,pos.Z);   dot.draw();
  }
}

// " marhi pas paise nehi he "

// Pre:  bBox is defined
// Post: bBox is filled with Vertices transformed by mat
void Clone::genBox(Vertex * bBox) const{
  Vertex * p = Maker->bBox; // Get the parent bounding box
  for (int b=0; b<BOUNDING_BOX_SIZE; b++)
    (bBox[b] = p[b]) *= *(modelMatrix);
  // Get the orginal bBox and Multiply the point by the model mat
  // Bounding box has been built
}

// Pre:  nBox is empty and ready to be initialized, bBox has been
//       constructed with the "genBox" static method
// Post: The normals for this bounding box are generated
void Clone::genNorm(Vertex * nBox, Vertex * bBox){
  for (int n=0; n<NORMAL_BOX_SIZE; n++){
    (nBox[n] = bBox[n+1]) -= bBox[0];
    if (nBox[n].X == nBox[n].Y == nBox[n].Z == 0){ // If this is 0
      if (n == 0)
	nBox[n].Z = 1.0;
      else if (n == 1)
	nBox[n].Y = 1.0;
      else if (n == 2)
	nBox[n].X = 1.0;
    }
  }
}

// Pre:  nBox1 and nBox2 are of length NORMAL_BOX_SIZE and initialized
// Post: All of the extra normals are generated for the special case
void Clone::genExtraNorm(Vertex * extraN, Vertex * nBox1, 
			 Vertex * nBox2){
  for (int n1=0; n1<NORMAL_BOX_SIZE; n1++){
    for (int n2=0; n2<NORMAL_BOX_SIZE; n2++){
      Vertex::cross(nBox1[n1], nBox2[n2], 
		    extraN[n1*NORMAL_BOX_SIZE+n2]);
      // ^^ Store the result of the cross product in extraN
    }
  }
}

// Pre:  c1 and c2 are well defined, eject is either true or false
// Post: Handles collision, true if there was a collision, if eject
//       is true then the clones are ejected according to their
//       momentum values
bool Clone::Collides(Clone & c1, Clone & c2, bool shouldE){
  Vertex eject; // The normal to eject on if there is overlap
  float c1Min, c2Min;  // The min values for rounds that have ejection
  float ejectAmount = INFINITY; // large so the first will be kept
  bool doesCollide = Clone::standardCollision(eject, ejectAmount, 
					      c1Min, c2Min, c1, c2);
  if ((doesCollide)&&(shouldE)){
    eject.normalize(); 
    eject *= ejectAmount;
    if (c1Min < c2Min) eject *= -1;
    float eRatio = c1.Momentum / (c1.Momentum + c2.Momentum);
    c1.translate(eject.X*eRatio, eject.Y*eRatio, eject.Z*eRatio);
    eRatio = 1 - eRatio;
    c2.translate(-eject.X*eRatio, -eject.Y*eRatio, -eject.Z*eRatio);
  }
  return(doesCollide);
}

// Pre:  (eject, ejectAmount, c1Min, c2Min) need to be initialized
//       c1 and c2 should be constructed and in use with valid
//       bounding boxes and Model's as "Maker"s
// Post: The default collision on the 6 normals of the two clones is
//       performed, if that collisions produces true, then the extra
//       special case for collision on the all of the cross products
//       of the normal pairs is run (9 extra normals).  true if the
//       two bounding boxes for these clones are colliding
bool Clone::standardCollision(Vertex & eject, float & ejectAmount,
			      float & c1Min, float & c2Min, 
			      Clone & c1, Clone & c2){
  Vertex bBox1[BOUNDING_BOX_SIZE]; // The bounding box coordinates
  Vertex bBox2[BOUNDING_BOX_SIZE]; // The bounding box coordinates
  Vertex nBox1[NORMAL_BOX_SIZE]; // The bounding box coordinates
  Vertex nBox2[NORMAL_BOX_SIZE]; // The bounding box coordinates
  c1.genBox(bBox1);              c2.genBox(bBox2);
  Clone::genNorm(nBox1, bBox1);  Clone::genNorm(nBox2, bBox2);
  float olap = 1; // The overlap amount for current round (initialize
                                                // to having overlap)
  for (int normal=0; ((normal<NORMAL_BOX_SIZE)&&(olap>0)); normal++){
    Clone::CheckBoxesAndNormal(bBox1, bBox2, nBox1[normal], olap,
			       eject, ejectAmount, c1Min, c2Min);
    if (olap < 0)
      Clone::CheckBoxesAndNormal(bBox1, bBox2, nBox2[normal], olap,
				 eject, ejectAmount, c1Min, c2Min);
  }
  if (olap > 0){ // If there is still collision
    Vertex extraN[REMAINING_NORMALS_SIZE]; // Holder for remaining norms
    Clone::genExtraNorm(extraN, nBox1, nBox2); // Generate norms
    for (int normal=0;  ((normal<REMAINING_NORMALS_SIZE)&&(olap>0)); 
  	 normal++){      
      if (!(extraN[normal].X == extraN[normal].Y == extraN[normal].Z 
  	    == 0))
  	Clone::CheckBoxesAndNormal(bBox1, bBox2, extraN[normal], olap,
  				   eject, ejectAmount, c1Min, c2Min);
    }
  }
  return(olap > 0);
}

// Pre:  bBox1 & bBox2 are both initialized by Clone::genBox,
//       (eject, ejectAmount, c1Min, c2Min) need to be initialized
// Post: The two boxes given are projected to norm and then tested for
//       oeverlap, if there is overlap and it is the smallest overlap
//       that has been seen (smaller ejectAmount) then the information
//       about this check is recored in c1Min, c2Min, eject, and
//       ejectAmount 
void Clone::CheckBoxesAndNormal(Vertex * bBox1, Vertex * bBox2,
				Vertex & norm, float & olap,
				Vertex & eject, float & ejectAmount,
				float & c1Min, float & c2Min){
  float min1, min2, max1, max2; // Initialize storage for vars
  boxToLine(bBox1, norm, min1, max1);
  boxToLine(bBox2, norm, min2, max2);
  overlap(min1, max1, min2, max2, olap);
  if ((olap > 0) && (olap < ejectAmount)){
    eject = norm;   ejectAmount = olap;
    c1Min = min1;   c2Min = min2;
  }
}

// Pre:  bBox is a bounding box for an object to test overlap on. 
//       n (normal) is the normal that bBox will be projected onto
// Post: min and max are set for this bBox being projected onto normal
void boxToLine(Vertex * bBox, Vertex & n, float &min1, float &max1){
  min1 = INFINITY; // Set the min's to be very large
  max1 = -INFINITY; // Set the max's to be very small  
  float v; // Holder for the value of the current dot product
  for (int vertex=0; vertex<BOUNDING_BOX_SIZE; vertex++){
    v = Vertex::dot(n,bBox[vertex]);
    min1 = min(min1, v);    max1 = max(max1, v);
  }
}


  // if (olap){ // If there was vertical level overlap
  //   for (int normal=0; ((normal<NORMAL_BOX_SIZE)&&(olap)); normal++){      
  //     n = nBox[normal];
  //     if (n.Y == 0){
  // 	if (n.X == n.Y == n.Z == 0)
  // 	  (n = c.Center) -= Center;
  // 	boxToLine(bBox, n, min2, max2);
  // 	min1 = max1 = Vertex::dot(Center, n);
  // 	min1 < min2 ? max1 += Radius/2 : min1 -= Radius/2;
  // 	olap = overlap(min1, max1, min2, max2);
  //     }
  //   }
  // }
