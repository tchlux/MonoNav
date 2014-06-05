#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>

static GLfloat spin = 0.0; //changing variable for current spin state
static GLfloat speed_change = .2; //represents the change in spin
				  //amount over time
static GLfloat SS = 10.0; //Square size
static GLint WINDOW_SIZE = 800;
static GLint WINDOW_POS = 200;
static GLfloat RED = .2;
static GLfloat GREEN = .2;
static GLfloat BLUE = .4;
static GLfloat RATIO = .5;
static GLfloat STEP = .06;


void init(void) 
{
  glClearColor (1.0-RED, 1.0-BLUE, 1.0-GREEN, 0.0);
  glShadeModel (GL_FLAT);
}

void draw_square(int x, int y)
{
  float i;
  for (i=1.0; i>=0.0; i-=STEP) {
    glRotatef(spin*(1-i), 0.0, 0.0, 1.0);
    glColor3f(RED*i,GREEN*i,BLUE*i);
    glRectf(x-SS*i,y-SS*i,x+SS*i,y+SS*i);
  }
} 

void display(void)
{
  glClear(GL_COLOR_BUFFER_BIT);
  glPushMatrix();
  //  glCullFace(GL_FRONT_AND_BACK);
  //  glEnable(GL_CULL_FACE);
  //Those lines show how to hide a side of a polygon
  draw_square(0,0);
  glPopMatrix();
  glutSwapBuffers();
}

void spinDisplay(void)
{
  spin = spin + speed_change;
  if (spin > 1500)
    spin = 0;
  glutPostRedisplay();
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

void mouse(int button, int state, int x, int y) 
{
  switch (button) {
  case GLUT_LEFT_BUTTON:
    if (state == GLUT_DOWN)
      glutIdleFunc(spinDisplay);
    break;
  case GLUT_RIGHT_BUTTON:
    if (state == GLUT_DOWN)
      glutIdleFunc(NULL);
    break;
  default:
    break;
  }
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
  glutMouseFunc(mouse);
  glutMainLoop();
  return 0;
}
