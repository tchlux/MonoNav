#include <GL/glut.h>
#include <stdlib.h>

static GLfloat spin = 0.0; //changing variable for current spin state
static GLfloat speed_change = .2; //represents the change in spin
				  //amount over time
static GLfloat SS = 10.0; //Square size
static GLint WINDOW_SIZE = 600;
static GLint WINDOW_POS = 300;
static GLfloat RED = .7;
static GLfloat GREEN = .3;
static GLfloat BLUE = .6;
static GLfloat RATIO = .5;
static GLfloat STEP = .06;

#define X .525731112119133606
#define Z .850650808352039932

static GLfloat vdata[12][3] = {    
  {-X, 0.0, Z}, {X, 0.0, Z}, {-X, 0.0, -Z}, {X, 0.0, -Z},    
  {0.0, Z, X}, {0.0, Z, -X}, {0.0, -Z, X}, {0.0, -Z, -X},    
  {Z, X, 0.0}, {-Z, X, 0.0}, {Z, -X, 0.0}, {-Z, -X, 0.0} 
};
static GLuint tindices[20][3] = { 
  {0,4,1}, {0,9,4}, {9,5,4}, {4,5,8}, {4,8,1},    
  {8,10,1}, {8,3,10}, {5,3,8}, {5,2,3}, {2,7,3},    
  {7,10,3}, {7,6,10}, {7,11,6}, {11,0,6}, {0,1,6}, 
  {6,1,10}, {9,0,11}, {9,11,2}, {9,2,5}, {7,2,11} };

void init(void) 
{
  glClearColor (1.0-RED, 1.0-BLUE, 1.0-GREEN, 0.0);
  glShadeModel (GL_FLAT);
}

void display(void)
{
  glClear(GL_COLOR_BUFFER_BIT);
  glPushMatrix();
  glBegin(GL_TRIANGLES);    
  int i = 0;
  for (i = 0; i < 20; i++) {    
    /* color information here */ 
    float ratio = i/20.0;
    glColor3f(RED*ratio,GREEN*ratio,BLUE*ratio);
    glVertex3fv(&vdata[tindices[i][0]][0]); 
    glVertex3fv(&vdata[tindices[i][1]][0]); 
    glVertex3fv(&vdata[tindices[i][2]][0]); 
  }
  glEnd();
  glPopMatrix();
  glutSwapBuffers();
}

void reshape(int w, int h)
{
  glViewport (0, 0, (GLsizei) w, (GLsizei) h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-50.0, 50.0, -50.0, 50.0, -1.0, 1.0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

/* 
 *  Request double buffer display mode.
 *  Register mouse input callback functions
 */
int main(int argc, char** argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowSize (WINDOW_SIZE,WINDOW_SIZE); 
  glutInitWindowPosition (WINDOW_POS,WINDOW_POS);
  glutCreateWindow (argv[0]);
  init ();
  glutDisplayFunc(display); 
  glutReshapeFunc(reshape); 
  glutMainLoop();
  return 0;
}
