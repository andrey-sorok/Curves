
#include <GL\glew.h>
#include <GL\freeglut.h>

#include <time.h> // íóæåí äëÿ âûçîâà ôóíêöèè time()

#define TIMER 5.6          // 60 frame per second

//std
#include <memory>

#include "BaseCurve.h"
#include "Render.h"
#include "Condition.h"
#include "Generator.h"

 //for test

/* Global variables */
char title[] = "Curves";

float cX = -10;
float cY = 0;

auto g_pRender = std::make_unique<Render>();
auto g_pGenerator = std::make_shared<CGenerator>();
auto g_pConditions = std::make_shared<CCondition>();


void KeyStroke(unsigned char key, int x, int y)
{
	switch (key)
	{
		case 13: //Enter
		{
			int i = 0;
			++i;
			break;
		}

		case 61: //+
		{
			float Depth = 4;
			g_pConditions->ChangeTranslateValues(0, 0, Depth);
			break;
		}

		case 45: //-
		{
			float Depth = -4;
			g_pConditions->ChangeTranslateValues(0, 0, Depth);
			break;
		}
	
		case 119: //w
		{
			int Up = 4;
			g_pConditions->ChangeTranslateValues(0, Up, 0);
			printf("GLUT_KEY_UP %d\n", key);	
			break;
		}
	
		case 115: //s
		{
			int Down = -4;
			g_pConditions->ChangeTranslateValues(0, Down, 0);
			printf("GLUT_KEY_DOWN %d\n", key);
			break;
		}
	
		case 100: //d
		{
			int Right = 4;
			g_pConditions->ChangeTranslateValues(Right, 0, 0);
			printf("GLUT_KEY_RIGHT %d\n", key);
			break;
		}
	
		case 97: //a
		{
			int Left = -4;
			g_pConditions->ChangeTranslateValues(Left, 0, 0);
			printf("GLUT_KEY_RIGHT %d\n", key);
			break;
		}
	
		case 'q': //113
		{
			float Angel = -10;
			g_pConditions->ChangeRotateValues(Angel, 0, 0, 1);
			break;
		}

		case 'e':
		{
			float Angel = 10;
			g_pConditions->ChangeRotateValues(Angel, 0, 0, 1);
			break;
		}

		case 'n': 
			break;
		case 'h':
			break;
	
		case 27:
		{
			printf("GLUT_KEY_UP %d\n", key);
			break;
		}
	
		case 127: // Delete button
		{
			printf("GLUT_KEY_UP %d\n", key);
			break;
		}
		default:
			break;
	}
}

void KeyProcess(int key, int x, int y)
{
	switch (key)
	{
		case 27:
		{
			
			break;
		}
		case 100:
		{   
			float Angel = 10;
			g_pConditions->ChangeRotateValues(Angel, 0, 1, 0);
			break;
		}
		case 102:
		{
						
			float Angel = -10;
			g_pConditions->ChangeRotateValues(Angel, 0, 1, 0);
			break;
		}
		case 101:
		{
			float Angel = 10;
			g_pConditions->ChangeRotateValues(Angel, 1, 0, 0);
			break;
		}
		case 103:
		{
			float Angel = -10;
			g_pConditions->ChangeRotateValues(Angel, 1, 0, 0);
			break;
		}
	}
}


void initGL() 
{
	//glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque

	glClearColor(static_cast<GLclampf>(0.0), static_cast<GLclampf>(0.2), static_cast<GLclampf>(0.5), static_cast<GLclampf>(0.00));
	glClearDepth(1.0f);                   // Set background depth to farthest
	glEnable(GL_DEPTH_TEST);   // Enable depth testing for z-culling
	glDepthFunc(GL_LEQUAL);    // Set the type of depth-test
	glShadeModel(GL_SMOOTH);   // Enable smooth shading
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);  // Nice perspective corrections
}

/* Handler for window-repaint event. Called back when the window first appears and
whenever the window needs to be re-painted. */

void recomputeFrame(int value)
{
	glutPostRedisplay();
}

void display(void) 
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear color and depth buffers
	glMatrixMode(GL_MODELVIEW);     // To operate on model-view matrix

									// Render a color-cube consisting of 6 quads with different colors
	glLoadIdentity();                 // Reset the model-view matrix


	std::vector<float> vTranslate = g_pConditions->GetTranslateValues();
	glTranslatef(vTranslate[0], vTranslate[1], vTranslate[2]);  // Move right and into the screen

	std::vector<float> & vRotate = g_pConditions->GetRotateValues();

	glRotatef(vRotate[0], vRotate[1], vRotate[2], vRotate[3]);

	g_pRender->Draw();

	auto pCurves = g_pGenerator->GetVecCurves();
	pCurves[0]->GetPointOnÑueve(0.5);
	pCurves[0]->GetPointOnÑueve(0.9);


	glutSwapBuffers();
	glutTimerFunc(static_cast<unsigned int>(TIMER), recomputeFrame, 1);
}

void reshape(GLsizei width, GLsizei height) 
{  
	srand(static_cast<unsigned int>(time(NULL)));

	// GLsizei for non-negative integer
	// Compute aspect ratio of the new window

	g_pConditions->SetWINHEIGHT(width);
	g_pConditions->SetWINHEIGHT(height);

	if (height == 0)
	{
		height = 1;                // To prevent divide by 0
	}

	GLfloat aspect = (GLfloat)width / (GLfloat)height;

	// Set the viewport to cover the new window
	glViewport(0, 0, width, height);

	// Set the aspect ratio of the clipping volume to match the viewport
	glMatrixMode(GL_PROJECTION);  // To operate on the Projection matrix
	glLoadIdentity();             // Reset
								  // Enable perspective projection with fovy, aspect, zNear and zFar
	gluPerspective(65.0f, aspect, -100.1f, 10.0f);
}


int main(int argc, char** argv) 
{
	g_pGenerator->SetConditions(g_pConditions);
	g_pRender->SetGenerator(g_pGenerator);
	

	glutInit(&argc, argv);            // Initialize GLUT

	glutInitDisplayMode(GLUT_DOUBLE); // Enable double buffered mode
	glutInitWindowSize(900, 900);   // Set the window's initial width & height
	glutInitWindowPosition(50, 50); // Position the window's initial top-left corner
	glutCreateWindow(title);          // Create window with the given title
	
	glutDisplayFunc(display);       // Register callback handler for window re-paint event
	glutReshapeFunc(reshape);       // Register callback handler for window re-size event
	
	glutSpecialFunc(KeyProcess);
	glutKeyboardFunc(KeyStroke);
	g_pRender->InitGL();
	//initGL();                       // Our own OpenGL initialization
	
	glutMainLoop();                 // Enter the infinite event-processing loop
	return 0;
}