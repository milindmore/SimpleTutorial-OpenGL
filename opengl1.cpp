/***************************************************************************/
/* This is a simple demo program written for training at Rolocule Studios  */
/*														                   */
/*                                                                         */
/* Successive training sessions/iterations make this program more complex. */
/* This is the first simple program to draw a ground plane allowing zooming*/  
/* The intent is to show how to draw a simple scene.                       */
/***************************************************************************/


#include <GL/glut.h>
#include <stdlib.h>

int mouseoldx, mouseoldy ; // For mouse motions
GLdouble eyeloc = 5.0 ; // Where to look from; initially 0 -2, 2

void display(void)
{
/* clear all pixels  */
   glClear (GL_COLOR_BUFFER_BIT);

   // draw polygon (square) of unit length centered at the origin
   // Note that vertices must generally go counterclockwise
   // This code draws each vertex in a different color.  
   // The hardware will blend between them.  
   // This is a useful debugging trick.  I can make sure that each vertex 
   // appears exactly where I expect it to appear.
   // It also illustrates setting attributes inside glBegin... glEnd

  /* glBegin(GL_POLYGON);
      glColor3f (1.0, 1.0, 0.0);
      glVertex3f (0.5, 0.5, 0.0);
      glColor3f (0.0, 1.0, 0.0);
      glVertex3f (-0.5, 0.5, 0.0);
      glColor3f (0.0, 0.0, 1.0);
      glVertex3f (-0.5, -0.5, 0.0);
      glColor3f (1.0, 1.0, 1.0);
      glVertex3f (0.5, -0.5, 0.0);
   glEnd();
   */

 glBegin(GL_QUADS);            // Draw A Quad
       glColor3f(0.0f, 1.0f, 0.0f);     // Set The Color To Green
       glVertex3f(1.0f, 1.0f, -1.0f);   // Top Right Of The Quad (Top)
       glVertex3f(-1.0f, 1.0f, -1.0f);  // Top Left Of The Quad (Top)
       glVertex3f(-1.0f, 1.0f, 1.0f);   // Bottom Left Of The Quad (Top)
       glVertex3f(1.0f, 1.0f, 1.0f);    // Bottom Right Of The Quad (Top)

    /*   glColor3f(1.0f, 0.5f, 0.0f);     // Set The Color To Orange
       glVertex3f(1.0f, -1.0f, 1.0f);   // Top Right Of The Quad (Bottom)
       glVertex3f(-1.0f, -1.0f, 1.0f);  // Top Left Of The Quad (Bottom)
       glVertex3f(-1.0f, -1.0f, -1.0f); // Bottom Left Of The Quad (Bottom)
       glVertex3f(1.0f, -1.0f, -1.0f);  // Bottom Right Of The Quad (Bottom)

       glColor3f(1.0f, 0.0f, 0.0f);     // Set The Color To Red
       glVertex3f(1.0f, 1.0f, 1.0f);    // Top Right Of The Quad (Front)
       glVertex3f(-1.0f, 1.0f, 1.0f);   // Top Left Of The Quad (Front)
       glVertex3f(-1.0f, -1.0f, 1.0f);  // Bottom Left Of The Quad (Front)
       glVertex3f(1.0f, -1.0f, 1.0f);   // Bottom Right Of The Quad (Front)

       glColor3f(1.0f, 1.0f, 0.0f);     // Set The Color To Yellow
       glVertex3f(1.0f, -1.0f, -1.0f);  // Bottom Left Of The Quad (Back)
       glVertex3f(-1.0f, -1.0f, -1.0f); // Bottom Right Of The Quad (Back)
       glVertex3f(-1.0f, 1.0f, -1.0f);  // Top Right Of The Quad (Back)
       glVertex3f(1.0f, 1.0f, -1.0f);   // Top Left Of The Quad (Back)

       glColor3f(0.0f, 0.0f, 1.0f);     // Set The Color To Blue
       glVertex3f(-1.0f, 1.0f, 1.0f);   // Top Right Of The Quad (Left)
       glVertex3f(-1.0f, 1.0f, -1.0f);  // Top Left Of The Quad (Left)
       glVertex3f(-1.0f, -1.0f, -1.0f); // Bottom Left Of The Quad (Left)
       glVertex3f(-1.0f, -1.0f, 1.0f);  // Bottom Right Of The Quad (Left)

       glColor3f(1.0f, 0.0f, 1.0f);     // Set The Color To Violet
       glVertex3f(1.0f, 1.0f, -1.0f);   // Top Right Of The Quad (Right)
       glVertex3f(1.0f, 1.0f, 1.0f);    // Top Left Of The Quad (Right)
       glVertex3f(1.0f, -1.0f, 1.0f);   // Bottom Left Of The Quad (Right)
       glVertex3f(1.0f, -1.0f, -1.0f);  // Bottom Right Of The Quad (Right)*/
       glEnd();                         // Done Drawing The Quad
     

/* don't wait!  
 * start processing buffered OpenGL routines 
 */
   glFlush ();
}

/* Defines a Mouse callback to zoom in and out */
/* This is done by modifying gluLookAt         */
/* The actual motion is in mousedrag           */
/* mouse simply sets state for mousedrag       */
void mouse(int button, int state, int x, int y) 
{
  if (button == GLUT_LEFT_BUTTON) {
    if (state == GLUT_UP) {
      // Do Nothing ;
    }
    else if (state == GLUT_DOWN) {
      mouseoldx = x ; mouseoldy = y ; // so we can move wrt x , y 
    }
  }
  else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) 
    { // Reset gluLookAt
      eyeloc = 2.0 ; 
      glMatrixMode(GL_MODELVIEW) ;
      glLoadIdentity() ;
      gluLookAt(0,-eyeloc,eyeloc,0,0,0,0,1,1) ;
      glutPostRedisplay() ;
    }
}

void mousedrag(int x, int y) {
  int yloc = y - mouseoldy  ;    // We will use the y coord to zoom in/out
  eyeloc  += 0.005*yloc ;         // Where do we look from
  if (eyeloc < 0) eyeloc = 0.0 ;
  mouseoldy = y ;

  /* Set the eye location */
  glMatrixMode(GL_MODELVIEW) ;
  glLoadIdentity() ;
  gluLookAt(0,-eyeloc,eyeloc,0,0,0,0,1,1) ;
  
  glutPostRedisplay() ;
}

/* Defines what to do when various keys are pressed */
void keyboard (unsigned char key, int x, int y) 
{
  switch (key) {
  case 27:  // Escape to quit
    exit(0) ;
    break ;
  default:
    break ;
  }
}

/* Reshapes the window appropriately */
void reshape(int w, int h)
{
   glViewport (0, 0, (GLsizei) w, (GLsizei) h);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();

   // Think about the rationale for this choice for gluPerspective 
   // What would happen if you changed near and far planes? 
   gluPerspective(30.0, (GLdouble)w/(GLdouble)h, 1.0, 10.0) ;

}


void init (void) 
{
/* select clearing color 	*/
   glClearColor (0.0, 0.0, 0.0, 0.0);

/* initialize viewing values  */
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();

   // Think about this.  Why is the up vector not normalized?
   glMatrixMode(GL_MODELVIEW) ;
   glLoadIdentity() ;
   gluLookAt(0,-eyeloc,eyeloc,0,0,0,0,1,1) ;
}

int main(int argc, char** argv)
{
   glutInit(&argc, argv);

   // Requests the type of buffers (Single, RGB).
   // Think about what buffers you would need...

   glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);

   glutInitWindowSize (500, 500); 
   glutInitWindowPosition (100, 100);
   glutCreateWindow ("Simple Demo");
   init (); // Always initialize first

   // Now, we define callbacks and functions for various tasks.
   glutDisplayFunc(display); 
   glutReshapeFunc(reshape) ;
   glutKeyboardFunc(keyboard);
   glutMouseFunc(mouse) ;
   glutMotionFunc(mousedrag) ;

   glutMainLoop(); // Start the main code
   return 0;   /* ANSI C requires main to return int. */
}
