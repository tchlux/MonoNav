#include <iostream>
#include <stdio.h>
#include <GL/glew.h>
#include <GL/glfw.h>
#include <cmath>

#include "glfwKeys.h"
#include "viewGL.h"
#include "Link.h" // For the "Link" class
#include "Model.h"
#include "Light.h"
#include "Clone.h"
#include "PlayerClone.h"
#include "Vertex.h"

#define CEILING 8
#define MOVEMENT_SPEED .005       // Block float speed
#define PLAYER_MOVE_SPEED .07    // Player movement speed
#define PLAYER_ROTATE_SPEED 2.0f // Player rotate speed
#define PLAYER_BULLET_SPEED -.1f  // Player bullet travel
#define JUMP_SPEED -.1   // Jump velocity
#define GRAVITY -.003    // Gravity effect rate
#define WORLDS_END 40    // Distance that is the edge of the world

#define GRAVUS_FLOAT_DISTANCE 1.0 // The distance the gravus floats
//in front of the player
#define GRAVITY_WELL_DISTANCE 20 // The effective range of gravi
#define GRAVI_ATTRACTION_RATIO .01 // The ratio of attraction for gravi
#define MAX_GRAVI 1     // Max # of gravi at one point in time
#define GRAVI_SCALE .3  // The scale of the gravus
#define GRAVI_ROTATION 0.5f // Degree speed of gravi rotation

#define NUM_CUBES 10
#define CUBE_SPACING 1
#define TILE_SIZE 20      // Size of one floor tile
#define FLOOR_TILES 2   // Number of tiles on the floor in each direction
#define FLOOR_VALUE 2.0  // Location of the most bottom floor
#define BOUNDARY_MOMENTUM INFINITY // Momentum for walls and floors

#define ATTENUATION 0.2f // Attenuation of light
#define ROTATE_SPEED 2.0f// Degree speed of rotation
#define EJECT_ON_COLLISION true // If player should be ejected on collision

float player_y_velocity = 0.0; // User y velocity

// Pre:  x,y,z all defined
// Post: The three values are normalized
void normalize(float & x, float & y, float & z){
  float max = x*x > y*y ?  (x*x > z*z ? x : z) : (y*y > z*z ? y : z);
  x = x / max; y = y / max; z = z / max;
}

// Pre:  objs is a list of clones that should be checked for collision
//       player is a clone that is the player to check collision agains
// Post: A pointer to a clone that collides with player
bool playerCollides(Link<Clone*> & objs, PlayerClone * player){
  bool collision = false;
  for (int c=0; ((c<objs.size())&&(!collision)); c++){
    collision = player->Collides((*objs[0]), EJECT_ON_COLLISION);
    objs.spin();
  }
  return(collision);
}

// Pre:  list has a bunch of cubes in it that should be rotated
// Post: All of the cubes in the list are rotated by rotAmount
void rotateClones(Link<Clone*> & list, float rotAmount){
  for (int c=0; c<list.size(); c++){
    //    list[0]->rotate(rotAmount, 0.0, 0.0, 1.0);
    list[0]->rotate(rotAmount, 0.0, 1.0, 0.0);
    list.spin();
  }
}

// Pre:  list has a bunch of cubes in it that should be rotated
// Post: All of the cubes in the list are rotated by rotAmount
void moveClones(Link<Clone*> & list, float x, float y, float z){
  for (int c=0; c<list.size(); c++){
    //    list[0]->rotate(rotAmount, 0.0, 0.0, 1.0);
    list[0]->translate(x,y,z);
    list.spin();
  }
}

// Pre:  list is defined and filled with properly initialized clones
//       view and projection came from camera
// Post: Each of the elements in list is drawn
void drawList(Link<Clone*> & list){
  for (int draw=0; draw<list.size(); draw++){
    (list[0])->draw();  
    list.spin();
  }
}

// Pre:  
// Post: 
void buildCubes(Link<Clone*> & cubes, Model * Cube, Camera * cam){
  for (int x=-NUM_CUBES; x<NUM_CUBES; x+=CUBE_SPACING){
    for (int y=-NUM_CUBES; y<NUM_CUBES; y+=CUBE_SPACING){
      cubes.add(new Clone(Cube, cam));
      cubes[-1]->translate(x,0.0,y);
    }
  }
}

// Pre:  room is for holding all boundary objects, wall is a defined
//       model class that has loaded a file, cam is the player camera
// Post: The four walls are added for a given coordinate
void addWalls(Link<Clone*> & room, Model * wall, Camera * cam,
	     int x, int range){
  room.add(new Clone(wall, cam));       
  room[-1]->Momentum = BOUNDARY_MOMENTUM;
  room[-1]->translate(x,0.0,-range-TILE_SIZE);
  room[-1]->rotate(180,0,1,0);

  room.add(new Clone(wall, cam));       
  room[-1]->Momentum = BOUNDARY_MOMENTUM;
  room[-1]->translate(x,0.0,range);

  room.add(new Clone(wall, cam));       
  room[-1]->Momentum = BOUNDARY_MOMENTUM;
  room[-1]->translate(-range,0.0,x);
  room[-1]->rotate(90,0,1,0);

  room.add(new Clone(wall, cam));       
  room[-1]->Momentum = BOUNDARY_MOMENTUM;
  room[-1]->translate(range-TILE_SIZE,0.0,x);
  room[-1]->rotate(270,0,1,0);  
}

// Pre:  room is empty and initialized, floor and wall have been
//       loaded, cam is the player camera
// Post: A bunch of floor tiles are made based off of defined vars
void buildRoom(Link<Clone*> & room, Model * floor, Model * wall,
	       Camera * cam){
  int range = FLOOR_TILES*TILE_SIZE; // The range of values
  for (int x=-range; x<range; x+=TILE_SIZE){
    addWalls(room, wall, cam, x, range);
    for (int y=-range; y<range; y+=TILE_SIZE){
      room.add(new Clone(floor, cam));
      room[-1]->translate(x,0.0,y);
      room[-1]->Momentum = BOUNDARY_MOMENTUM;
    }
  }
}

// Pre:  Cam is defined
// Post: All key press operations are handled
void moveCamera(Camera * cam){
  // Handle user input
  if (glfwGetKey(GLFW_KEY_LEFT) == GLFW_PRESS) {
    cam->rotate(-PLAYER_ROTATE_SPEED, 0, 1, 0);
  }
  if (glfwGetKey(GLFW_KEY_RIGHT) == GLFW_PRESS) {
    cam->rotate(PLAYER_ROTATE_SPEED, 0, 1, 0);
  }      
  if (glfwGetKey(GLFW_KEY_W) == GLFW_PRESS) {
    cam->translate(0.0, 0.0, PLAYER_MOVE_SPEED);
  }
  if (glfwGetKey(GLFW_KEY_S) == GLFW_PRESS) {
    cam->translate(0.0, 0.0, -PLAYER_MOVE_SPEED);
  }
  if (glfwGetKey(GLFW_KEY_A) == GLFW_PRESS) {
    cam->translate(PLAYER_MOVE_SPEED, 0.0, 0.0);
  }
  if (glfwGetKey(GLFW_KEY_D) == GLFW_PRESS) {
    cam->translate(-PLAYER_MOVE_SPEED, 0.0, 0.0);
  }      
  if (glfwGetKey(GLFW_KEY_SPACE) == GLFW_PRESS){
    if (player_y_velocity == 0.0){
//      cam->translate(0.0,JUMP_SPEED,0.0);
//      player_y_velocity = JUMP_SPEED;
      cam->getLink()->Yvel = JUMP_SPEED;
   }
  }
}

// Pre:  list is full of clones with bounding boxes defined, view and 
//       projection are defined, dot is a defined clone
// Post: All of the bBox corners of the clones in list are highlighted
//       with the 'dot' clone
void drawBBox(Link<Clone*> & list, Clone & dot){
  for (int draw=0; draw<list.size(); draw++){
    list[0]->drawBBox(dot);    list.spin();
  }
}

// Pre:  gravi is defined list for holdin gravi, Gravus the model to
//       use for creatin this gravus and has been defined.  Cam is the
//       player camera
// Post: a gravus is created at the player's position
void createGravi(Link<Clone*> & gravi, Model *Gravus, Camera * cam){
  if (glfwGetKey(GLFW_KEY_UP) == GLFW_PRESS){
    if (gravi.size() >= MAX_GRAVI){
      delete(gravi[0]); // Delete the oldest one
      gravi.remove(0);  // remove that pointer from the linked list
    }
    gravi.add(new Clone(Gravus, cam));
    cam->translate(0.0,0.0,GRAVUS_FLOAT_DISTANCE);
    Vertex pos = cam->getLink()->pos(); // Get the cam position
    cam->translate(0.0,0.0,-GRAVUS_FLOAT_DISTANCE);
    gravi[-1]->move(pos.X,pos.Y,pos.Z);
    gravi[-1]->scale(GRAVI_SCALE,GRAVI_SCALE,GRAVI_SCALE);
  }  
}

// Pre:  gravi is a list of gravi, effected are the objects that
//       should be affected by the gravity well
// Post: All the clones in effected are moved towards gravus
void gravusEffect(Link<Clone*> & gravi, Link<Clone*> & effected){
  for (int g=0; g<gravi.size(); g++){
    Vertex gravus = gravi[0]->pos();
    for (int e=0; e<effected.size(); e++){
      Vertex other = effected[0]->pos();
      if (distS(gravus, other) < GRAVITY_WELL_DISTANCE){
	other -= gravus; other *= GRAVI_ATTRACTION_RATIO;
	effected[0]->translate(-other.X,-other.Y,-other.Z);
      }
      effected.spin(); // Spin the linked list
    }
    gravi.spin(); // Spin the linked list
  }
}

// Pre:  link is defined, all elements in link were allocated with new
// Post: all elements are deleted
void clearLink(Link<Clone*> & link){
  int size = link.size(); // Get the size of the list
  for (int n=0; n<size; n++){
    delete(link[0]); // Delete the clone in front
    link.remove(0);  // remove that pointer from the linked list
  }
}

bool aboveCeiling(Link<Clone*> & link){
  bool above = false;
  int size = link.size();
  for (int n=0; n<size; n++){
    if (link[0]->pos().Y > CEILING){
      above = true;
    }
  }
  return(above);
 }
