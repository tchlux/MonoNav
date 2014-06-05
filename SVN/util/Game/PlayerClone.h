#ifndef DEFINED_PLAYERCLONE

#define DEFINED_PLAYERCLONE
#include "Clone.h"
#include "Camera.h"

class PlayerClone : public Clone {

protected:
  Camera * Link; // The camera that this clone is linked to

public:
  float Xvel;  float Yvel;  float Zvel; // Velocities
  float Bounce; // Factor multiplied by velocities upon collisions

  // Pre:  Maker is a well defined Model object, similare of camera
  // Post: This clone is initialized
  PlayerClone(Model * model, Camera * cam);

  // Pre:  Xvel,Yvel,Zvel all initialized
  // Post: This camera:clone pair is translated by the member data
  //       velocities stored
  void move();

  // Pre:  ind is the index out of total to be drawn on a circular path
  //       total is the divisor when translating ind to 2pi orbital path
  // Post: The x and z position of "pos" are translated to that point
  void NumRadToDot(int ind, int total, Vertex & pos);

  // Pre:  dot is s clone that should be drawn at each vertex of bBox
  // Post: All of the bBox corners of this clone are
  //       highlighted with the 'dot' clone
  void drawBBox(Clone & dot);

  // Pre:  This clone should be using a bounding cyllinder, other
  //       clone has a bounding box, shouldE is true if should eject,
  //       camera is the camera bounded to this clone
  // Post: Box - cyllinder collision detection.
  bool Collides(Clone & c, bool shouldE);
 
};

#endif
