

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <windows.h>
#include <GL/glut.h>
#endif

#include <stdlib.h>

static int shoulderAngle = 0, elbowAngle = 0,wristAngle=0;

//six different keys to move three parts of the arm to both directions
void special(int key, int, int) {
  switch (key) {

    case GLUT_KEY_LEFT:
        (elbowAngle += 5);
    break;

    case GLUT_KEY_RIGHT:
        (elbowAngle -= 5);
    break;

    case GLUT_KEY_UP:
        (shoulderAngle += 5) ;
    break;

    case GLUT_KEY_DOWN:
        (shoulderAngle -= 5);
    break;

    case GLUT_KEY_PAGE_UP:
        (wristAngle += 5) ;
    break;

    case GLUT_KEY_PAGE_DOWN:
        (wristAngle -= 5);
    break;

    default:
        return;
  }
  glutPostRedisplay();
}

//this is glut wire cube function and ,it makes a wire frame box with given width,height and a depth
void wireBox(GLdouble width, GLdouble height, GLdouble depth) {
  glPushMatrix();
  glScalef(width, height, depth);
  glutWireCube(1.0);
  glPopMatrix();
}

//displays the arm
void display() {

  glClear(GL_COLOR_BUFFER_BIT); //cleans the screen
  glMatrixMode(GL_MODELVIEW);

  glPushMatrix();

  glRotatef((GLfloat)shoulderAngle, 0.0, 0.0, 1.0);
  glTranslatef(1.0, 0.0, 0.0);
  glColor3f(1.0,0.0,0.0); //the upper part of the arm is red in color
  wireBox(2.0, 0.4, 1.0);

  glPushMatrix();
  glTranslatef(1.0, 0.0, 0.0); //the  cube is shifting towards given position
  glRotatef((GLfloat)elbowAngle, 0.0, 0.0, 1.0); //elbow is rotating around z axis
  glColor3f(0.0,1.0,0.0); //elbow is given color green
  glTranslatef(1.0, 0.0, 0.0);
  wireBox(2.0, 0.35, 0.5);

   glTranslatef(1.0,0.0,0.0);
    glRotatef((GLfloat)wristAngle,0.0,0.0,1.0);
    glTranslatef(0.5,0.0,0.0);
    glColor3f(0.0,0.0,1.0); //wrist is given color blue
    wireBox(1.0,0.25,0.35);


  glPopMatrix();

  glPopMatrix();
  glFlush();
}

void reshape(GLint w, GLint h) {
  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-8.0,8.0,-8.0,8.0,8.0,40.0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(4.0,8.0,30.0, //eyepoint
            2.0,0.0,0.0,    //center point
            0.0,4.0,0.0);   //up axis

}

int main(int argc, char** argv) {

  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowPosition(50, 50); //starting position for the window
  glutInitWindowSize(800, 800); //window size
  glutCreateWindow("Robot Arm"); //creates window and sets the title
  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  glutSpecialFunc(special);
  glutMainLoop();
}
