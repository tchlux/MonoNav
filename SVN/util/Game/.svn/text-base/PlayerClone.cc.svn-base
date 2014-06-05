#include "iostream"
#include "cmath"
#include "PlayerClone.h"
#include "Clone.h"
#include "Camera.h"

#define TO_RADIANS * (PI/180)	// Converts a degree amount to radians
#define NUM_CIRCLE_DOTS 10	// Number of dots on cyllinder
#define DEGREES_IN_CIRCLE 360	// Number of degrees in a circle

// Pre:  Maker is a well defined Model object, similare of camera
// Post: This clone is initialized
PlayerClone::PlayerClone(Model * model, Camera * cam) : 
  Clone::Clone(model,cam){
  Link = cam;
  cam->setLink(this);
  Clone::translate(0,0,1);
  Xvel = Yvel = Zvel = 0.0;
  Bounce = DEFAULT_BOUNCE_DEGRADATION;
}

// Pre:  The modelMatrix is initialized, cam is stored in this
// Post: This model instance is drawn
void PlayerClone::move(){
  Link->translate(Xvel, Yvel, Zvel);
};

// Pre:  ind is the index out of total to be drawn on a circular path
//       total is the divisor when translating ind to 2pi orbital path
// Post: The x and z position of "pos" are translated to that point
void PlayerClone::NumRadToDot(int ind, int total, Vertex & pos){
  float degrees = ((float) ind / (float) total) * DEGREES_IN_CIRCLE;
  pos.Y += (sin(degrees TO_RADIANS)*Radius);
  pos.X += (cos(degrees TO_RADIANS)*Radius);
};

// Pre:  dot is s clone that should be drawn at each vertex of bBox
// Post: All of the bBox corners of this clone are
//       highlighted with the 'dot' clone
void PlayerClone::drawBBox(Clone & dot){
  Vertex pos = Center; // Get the current center of this clone
  float height = Maker->bBox[BOUNDING_BOX_SIZE-1].Y - Maker->bBox[0].Y;
  // ^^ Knowing this cyllinder hasn't been rotated on x or z, get the
  // y height for drawing the box
  pos.Y -= height/2; // Place at the bottom of the cyllinder
  dot.move(pos.X,pos.Y,pos.Z); dot.draw();
  for (int b=0; b<NUM_CIRCLE_DOTS; b++){      
    NumRadToDot(b, NUM_CIRCLE_DOTS, pos); // Move to a pt on circle
    dot.move(pos.X,pos.Y,pos.Z);   dot.draw(); // draw the marker
    pos.X = Center.X; pos.Z = Center.Z; // Reset to center for next draw
  }
  pos.Y += height;   dot.move(pos.X,pos.Y,pos.Z); dot.draw();
  for (int b=0; b<NUM_CIRCLE_DOTS; b++){      
    NumRadToDot(b, NUM_CIRCLE_DOTS, pos); // Move to a pt on circle
    dot.move(pos.X,pos.Y,pos.Z);   dot.draw(); // draw the marker
    pos.X = Center.X; pos.Z = Center.Z; // Reset to center for next draw
  }
};


// Pre:  This clone should be using a bounding cyllinder, other
//       clone has a bounding box, shouldE is true if should eject,
//       camera is the camera bounded to this clone
// Post: Box - cyllinder collision detection.
bool PlayerClone::Collides(Clone & c, bool shouldE){
  Vertex eject; // The normal to eject on if there is overlap
  float c1Min, c2Min;  // The min values for rounds that have ejection
  float ejectAmount = INFINITY; // large so the first will be kept
  Vertex bBox[BOUNDING_BOX_SIZE]; // The bounding box coordinates
  Vertex nBox[NORMAL_BOX_SIZE]; // The bounding box coordinates
  c.genBox(bBox); // Generate the bounding box for the other clone
  Clone::genNorm(nBox, bBox); // Generate the normals for the cube
  Vertex n; // normal holder
  float min1, min2, max1, max2; // Initialize storage for vars
  float olap;
  (n = Maker->bBox[0]) *= *(modelMatrix);  min1 = n.Y;
  (n = Maker->bBox[BOUNDING_BOX_SIZE-1]) *= *(modelMatrix);  
  max1 = n.Y; // Get the max and min y of this cyllinder knowing that
  //  it has not been rotated, these are guarenteed max and min
  n.set(0,1,0); // Set the normal to be updwards
  boxToLine(bBox, n, min2, max2); // Cast the bBox of other to this
                                // vertical line and check for overlap
  overlap(min1, max1, min2, max2, olap); // Calculate overlap
  if (olap > 0){ // If there is overlap
    eject = n;      ejectAmount = olap;
    c1Min = min1;   c2Min = min2;
    (n = Center) -= c.Center; n.Y = 0; // Discard y difference
    Vertex vertical(0,1,0);
    Vertex cross; Vertex::cross(vertical, n, cross); // The normal
                              //       perpindicular to the center
    boxToLine(bBox, n, min2, max2);
    min1 = max1 = Vertex::dot(Center, n);
    min1 < min2 ? max1 += Radius : min1 -= Radius;
    overlap(min1, max1, min2, max2, olap); // calculate overlap again
    if ((olap > 0) && (olap < ejectAmount)){
      eject = n;      ejectAmount = olap;
      c1Min = min1;   c2Min = min2;
    }
  }
  if ((olap > 0)&&(shouldE)){ // If there is still overlap then eject
    eject.normalize();     eject *= ejectAmount;
    if (c1Min < c2Min) eject *= -1;
    float eRatio = Momentum / (Momentum + c.Momentum);
    c.translate(-eject.X*eRatio, -eject.Y*eRatio, -eject.Z*eRatio);
    eRatio = 1 - eRatio;
    Link->translate(eject.X*eRatio, eject.Y*eRatio, eject.Z*eRatio);
  }
  Xvel *= Bounce; Yvel *= Bounce; Zvel *= Bounce;
  return(olap > 0);
}
