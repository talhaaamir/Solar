
#include <iostream>
#include <glut.h>
using namespace std;

static float year = 0, day = 0, marsYear = 0;
GLfloat rotX = 0.0f; //rotate x
GLfloat rotY = 0.0f; //rotate y
GLfloat rotZ = 0.0f; //rotate z
GLfloat zoomZ = 0.0f; //zoom
GLfloat zoomX = 0.0f;
GLfloat zoomY = 0.0;

void init(void) 
{
   glClearColor (0.0, 0.0, 0.0, 0.0);
   glShadeModel (GL_FLAT);
}

void display(void)
{
   glClear (GL_COLOR_BUFFER_BIT);
   glColor3f (1.0, 1.0, 1.0);

   glPushMatrix();
       glRotatef(rotX,1.0,0.0,0.0); //rotate x
	   glRotatef(rotY,0.0,1.0,0.0); //rotate y
       glRotatef(rotZ,0.0,0.0,1.0); //rotate z

	   //sun
	   glPushMatrix();
		   glColor3f(1.0, 1.0, 0.0); //yellow
		   glutWireSphere(.75, 15, 10);   
	   glPopMatrix();

	   //mars
	   glPushMatrix();
		   glColor3f(1.0, 0.0, 0.0); //red
		   glRotatef ((GLfloat) marsYear, 0.0, 1.0, 0.0);
		   glTranslatef (1.0, 0.0, 0.0);
		   glRotatef ((GLfloat) day, 0.0, 1.0, 0.0);
		   glutWireSphere(0.2, 10, 5); 
	   glPopMatrix();

	   //earth
	   glPushMatrix();
		   glColor3f(0.0, 1.0, 0.0); //green
		   glRotatef ((GLfloat) year, 0.0, 1.0, 0.0);
		   glTranslatef (2.0, 0.0, 0.0);
		   glRotatef ((GLfloat) day, 0.0, 1.0, 0.0);
		   glutWireSphere(0.2, 10, 5);    
	  //glPopMatrix();
	  //glPushMatrix();
	       //moon
		   glColor3f(.3, .3, .3); //gray
		   glRotatef ((GLfloat) year, 0.0, 1.0, 0.0);
		   glTranslatef (.5, 0.0, 0.0);
		   glRotatef ((GLfloat) day, 0.0, 1.0, 0.0);
		   glutWireSphere(0.05, 5, 3);
	   glPopMatrix();

	   //year = (year + 1) % 360; //360
	   marsYear = marsYear + .08;
	   year = year + .1;
	   day = day + .5;
	   glutPostRedisplay();
   glPopMatrix();
   glutSwapBuffers();
}

void reshape (int w, int h)
{
   glViewport (0, 0, (GLsizei) w, (GLsizei) h); 
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity ();
   gluPerspective(60.0, (GLfloat) w/(GLfloat) h, 1.0, 20.0);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   gluLookAt (0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0); //0 0 40 0 0 0 0 1 0?
}

void keyboard (unsigned char key, int x, int y)
{
switch (key) {   
    case 'x': //x rotate 
		rotX -= 1.0f;
    break;

    case 'X': //other way
	    rotX += 1.0f;
    break;

    case 'y': //y rotate
	    rotY -= 1.0f;
    break;

    case 'Y': //other way
	    rotY += 1.0f; 
    break; 

    case 'z': //z rotate
	    rotZ -= 1.0;
    break;

    case 'Z': //other way
	    rotZ += 1.0f;
    break;

    case 'a': 	
	    zoomZ -= 0.3f;           
	    glMatrixMode(GL_MODELVIEW);    
	    glLoadIdentity();  
	    gluLookAt (zoomX, zoomY, zoomZ + 10, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0); //have to figure out starting zoom position
    break;

	case 'A':
	    zoomZ += 0.3f;
	    glMatrixMode(GL_MODELVIEW);
	    glLoadIdentity();
	    gluLookAt (zoomX, zoomY, zoomZ + 10, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    break;
	}
    glutPostRedisplay();
}

int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
   glutInitWindowSize (500, 500); 
   glutInitWindowPosition (100, 100);
   glutCreateWindow (argv[0]);
   init ();
   glutDisplayFunc(display); 
   glutReshapeFunc(reshape);
   glutKeyboardFunc(keyboard);
   glutMainLoop();
   return 0;
}