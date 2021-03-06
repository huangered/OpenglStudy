// study.cpp : 定义控制台应用程序的入口点。
#include "stdafx.h"	
//#pragma comment( linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"" )

#include <GL/glew.h>
#include <GL/glut.h>
#include "glCamera.h"
#include "glObject.h"
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
glCamera camera;
glObject obj;

unsigned int interval=500;
void RenderScene(void);
void SpecialKeys(int key, int x, int y);
void SetupRC();
void TimerFunction(int value);
void ChangeSize(int w, int h);
void KeyFunction(unsigned char key, int x, int y);
int _tmain(int argc, _TCHAR* argv[])
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
	glutInitWindowSize(400,400);
	glutCreateWindow("simple");
	glutDisplayFunc(RenderScene);
	glutReshapeFunc(ChangeSize);
	glutKeyboardFunc(KeyFunction);
	glutTimerFunc(interval,TimerFunction,1);
	glutSpecialFunc(SpecialKeys);

	SetupRC();

	glutMainLoop();

	return 0;
}
void KeyFunction(unsigned char key, int x, int y)
{			
	printf("%c\n",key);
	switch (tolower(key))
	{
	case 'w':
		camera.MoveForward(1.0f);
		glutPostRedisplay();
		break;
	case 's':
		camera.MoveForward(-1.0f);
		glutPostRedisplay();
		break;
	case 'a':
		camera.MoveRight(1.0f);
		glutPostRedisplay();
		break;
	case 'd':
		camera.MoveRight(-1.0f);
		glutPostRedisplay();
		break;
	case 'x':
		camera.MoveUp(-1.0f);
		glutPostRedisplay();
		break;
	case ' ':
		camera.MoveUp(1.0f);
		glutPostRedisplay();
		break;
	case 'q':
		camera.RotateLocalY(3.14/180);
		glutPostRedisplay();
		break;
	case 'e':
		camera.RotateLocalY(-3.14/180);
		glutPostRedisplay();
		break;
	default:
		break;
	}
}

// Called to draw scene
void RenderScene(void)
{									          
    // Clear the window with current clearing color
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
    glPushMatrix();
        camera.ApplyCameraTransform();
		//camera.show();
		glPushMatrix();
			obj.RotateLocalZ(3.14/180);
			obj.show();
			obj.ApplyActorTransform();
			obj.draw();
		glPopMatrix();
		glBegin(GL_LINES);
			glVertex3f(-100,0,0);
			glVertex3f(100,0,0);

			glVertex3f(0,-100,0);
			glVertex3f(0,100,0);

			glVertex3f(0,0,-100);
			glVertex3f(0,0,100);
		glEnd();

    glPopMatrix();
        
    // Do the buffer Swap
    glutSwapBuffers();
}
 // Respond to arrow keys by moving the camera frame of reference
void SpecialKeys(int key, int x, int y)
{
	printf("%d",key);
    if(key == GLUT_KEY_UP)
		camera.MoveUp(1.0f);
        
    if(key == GLUT_KEY_DOWN)
		camera.MoveUp(-1.f);

    if(key == GLUT_KEY_LEFT)
	{
		camera.MoveRight(1.0f);
	}
        
    if(key == GLUT_KEY_RIGHT)
		camera.MoveRight(-1.0f);
	
    // Refresh the Window
    glutPostRedisplay();
}		
//////////////////////////////////////////////////////////////////
// This function does any needed initialization on the rendering
// context. 
void SetupRC()
{	    
    // Bluish background
    glClearColor(0.0f, 0.0f, .50f, 1.0f );
         
    // Draw everything as wire frame
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    
}
///////////////////////////////////////////////////////////
// Called by GLUT library when idle (window not being
// resized or moved)
void TimerFunction(int value)
{
    // Redraw the scene with new coordinates
    glutPostRedisplay();
    glutTimerFunc(interval,TimerFunction, 1);
}
void ChangeSize(int w, int h)
{
    GLfloat fAspect;

    // Prevent a divide by zero, when window is too short
    // (you cant make a window of zero width).
    if(h == 0)
        h = 1;

    glViewport(0, 0, w, h);
        
    fAspect = (GLfloat)w / (GLfloat)h;

    // Reset the coordinate system before modifying
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
	
    // Set the clipping volume
    gluPerspective(35.0f, fAspect, 1.0f, 500.0f);
        
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}