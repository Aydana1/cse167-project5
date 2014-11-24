#include "main.h"

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <time.h>


#include "Window.h"
#include "Matrix4.h"

#include "InputHandler.h"
#include "Light.h"

using namespace std;

GLfloat emptyMat[] = { 0.0, 0.0, 0.0, 1.0 };
GLfloat ambientMat[] = { 0.7, 0.7, 0.7, 1.0 };
GLfloat specularMat[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat diffuseMat[] = { 0.1, 0.5, 0.8, 1.0 };
GLfloat red[] = { 1.0, 0.0, 0.0 };
GLfloat green[] = { 0.0, 1.0, 0.0 };
GLfloat blue[] = { 0.0, 0.0, 1.0 };

namespace Globals {
	Camera* camera;
	ObjModel *bunny;
	ObjModel *dragon;
	ObjModel *bear;
	ObjModel *currentModel;
	PointLight *pointLight;
	SpotLight *spotLight;
	bool usingShader;
	Shader *shader;
};


int main(int argc, char *argv[]) {
	Globals::usingShader = false;
	srand(time(NULL));

	float specular[] = { 1.0, 1.0, 1.0, 1.0 };
	float shininess[] = { 100.0 };
	float position[] = { 0.0, 10.0, 1.0, 0.0 };	// lightsource position

	glutInit(&argc, argv);      	      	      // initialize GLUT
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);   // open an OpenGL context with double buffering, RGB colors, and depth buffering
	glutInitWindowSize(Window::width, Window::height);      // set initial window size
	glutCreateWindow("CSE167 - Evan Carey");    	      // open window and set window title

	glDisable(GL_LIGHTING);

	glEnable(GL_DEPTH_TEST);            	      // enable depth buffering
	glClear(GL_DEPTH_BUFFER_BIT);       	      // clear depth buffer
	glClearColor(0.0, 0.0, 0.0, 0.0);   	      // set clear color to black
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);  // set polygon drawing mode to fill front and back of each polygon
	glDisable(GL_CULL_FACE);     // disable backface culling to render both sides of polygons
	glShadeModel(GL_SMOOTH);             	      // set shading to smooth
	glMatrixMode(GL_PROJECTION);

	// Generate material properties:
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_TEXTURE_2D);

	// Materials
	Material shinyBunny = Material(emptyMat, specularMat, emptyMat, 40.0, GL_FRONT_AND_BACK, red);
	Material diffuseDragon = Material(diffuseMat, emptyMat, emptyMat, 5.0, GL_FRONT_AND_BACK, blue);
	Material ambientBear = Material(emptyMat, emptyMat, ambientMat, 30.0, GL_FRONT_AND_BACK, green);
	// Initialize bunny
	Globals::bunny = new ObjModel("bunny.obj", true);
	Globals::bunny->setVisible(true);
	Globals::bunny->setMaterial(shinyBunny);
	Globals::currentModel = Globals::bunny;
	//Globals::bunny->makeScaleToFitWindow();

	// Initialize dragon
	Globals::dragon = new ObjModel("dragon.obj", false);
	Globals::dragon->setVisible(false);
	Globals::dragon->setMaterial(diffuseDragon);
	//Globals::dragon->makeScaleToFitWindow();

	// Initialize bear
	Globals::bear = new ObjModel("bear.obj", false);
	Globals::bear->setVisible(false);
	Globals::bear->setMaterial(ambientBear);
	//Globals::bear->makeScaleToFitWindow();

	glEnable(GL_COLOR_MATERIAL);

	// Generate light source:
	glEnable(GL_LIGHTING);
	GLfloat ambient[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat pointSpecular[] = { 0.0, 1.0, 0.0, 1.0 };
	GLfloat pointDiffuse[] = { 0.0, 1.0, 0.0, 1.0 };
	GLfloat pointPos[] = { -5.0, 10.0, 1.0, 1.0 };

	GLfloat spotSpecular[] = { 1.0, 0.0, 0.0, 1.0 };
	GLfloat spotDiffuse[] = { 1.0, 0.5, 0.5, 1.0 };
	GLfloat spotPos[] = { 0.0, 5.0, 5.0, 1.0 };
	GLfloat spotDir[] = { 0.0, -1.0, -1.0 };

	// Lights
	Globals::spotLight = new SpotLight(0, spotDiffuse, spotSpecular, ambient, spotPos, spotDir, 0.0, 30.0);
	Globals::pointLight = new PointLight(1, pointDiffuse, pointSpecular, ambient, pointPos);
	
	//glLightfv(GL_LIGHT0, GL_POSITION, position);
	//glEnable(GL_LIGHTING);
	//glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
	glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);

	// Install callback functions:
	glutDisplayFunc(Window::displayCallback);
	glutReshapeFunc(Window::reshapeCallback);
	glutIdleFunc(Window::idleCallback);

	// Initialize mouse handler
	glutMouseFunc(InputHandler::mouseClickCallback);
	glutMotionFunc(InputHandler::mouseMotionCallback);

	// Initialize input handler
	glutKeyboardFunc(InputHandler::processNormalKeys);
	glutSpecialFunc(InputHandler::processSpecialKeys);

	// Initialize cube matrix:
	//Globals::cube.getMatrix().identity();

	// Initialize sphere matrix
	//Globals::sphere.getMatrix().identity();

	Globals::shader = new Shader("../shaders/spotlight_shading.vert", "../shaders/spotlight_shading.frag", true);
	

	// Print position
	//Globals::cube.getMatrix().print("Initial Matrix: ");

	//// Initialize camera
	Globals::camera = new Camera();


	glutMainLoop();
	return 0;
}