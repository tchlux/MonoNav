#include "BlocksFunctions.cc"

int main(int argc, char * argv[]){
  int status = 0; 
  // Camera and initialization
  Camera cam;             viewGL gl(&cam);   gl.Window(); 
  Model BigCube;          BigCube.load("bigcube.obj");
  PlayerClone camBox(&BigCube, &cam);  // Bounding box for camera
  // Light initialization
  Light lig;            lig.set_position(0.0f, 0.0f, 1.0f);
  lig.set_attenuation(ATTENUATION); lig.set_color(1.0f, 1.0f, 1.0f); 
  // Game models
  Model bBoxDot;          bBoxDot.load("bboxdot.obj");
  Model Wall;             Wall.load("wall.obj");
  Model Floor;            Floor.load("floor.obj");
  Model Cube;             Cube.load("testVN.obj");
  Model Sphere;           Sphere.load("sphere.obj");
  Model SGravus;          SGravus.load("sgravus.obj"); 
  // Game object lists
  Link<Clone*> room;      buildRoom(room, &Floor, &Wall, &cam);
  Link<Clone*> cubes;     buildCubes(cubes, &Cube, &cam);
  Link<Clone*> gravi;     
  Link<Clone*> collides;  // All the objects that can be collided with
  cam.translate(0,-1,20); camBox.Bounce = -1.0;
  camBox.Momentum = 20.0;
  collides += room;       collides += cubes;
  // Any extra stuff?
  Clone bbDot(&bBoxDot, &cam);    Clone cube(&Cube, &cam);
  // Main game loop
  while(glfwGetKey(GLFW_KEY_ESC) != GLFW_PRESS &&
	glfwGetWindowParam(GLFW_OPENED)){
    gl.beginLoop();     lig.activate();
    moveCamera(&cam); // User input controls for player
    //    camBox.Yvel -= GRAVITY; camBox.move(); // Gravity movement
    createGravi(gravi, &SGravus, &cam);
    playerCollides(collides, &camBox);
    drawList(room);
    drawList(gravi);
    drawList(cubes);

    //    drawBBox(room, cube);
    rotateClones(cubes, ROTATE_SPEED);
    rotateClones(gravi, GRAVI_ROTATION);
    gravusEffect(gravi, cubes);
    
    gl.endLoop();
  }
  clearLink(room);
  clearLink(cubes);
  clearLink(gravi);

  gl.close();
  return(status); // Return exectution state
}
