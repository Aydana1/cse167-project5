#include "window.h"
#include "main.h"
#include "GL\glut.h"
#include "Matrix4.h"
#include "InputHandler.h"
#include "TimeManager.h"

int Window::width = 512;
int Window::height = 512;

Matrix4 model, camera, modelview;
Matrix4 translation, scale;


void Window::idleCallback() {
	displayCallback();
}

void Window::reshapeCallback(int w, int h) {
	width = w;
	height = h;
	glViewport(0, 0, w, h);  // set new viewport size
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, (double)width/(double)height, 1.0, 1000.0); // set perspective projection viewing frustum
	glTranslatef(0, 0, -20);    // move camera back 20 units so that it looks at the origin (or else it's in the origin)
	glMatrixMode(GL_MODELVIEW);
}

void Window::displayCallback() {
	// display fps in console
	TimeManager::Instance().CalculateFrameRate(true);

	glEnable(GL_LIGHTING);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // clear color and depth buffers
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(modelview.getGLMatrix());

	if (Globals::usingShader) {
		Globals::shader->bind();
	}

	glPushMatrix();
	glLoadIdentity();
	glRotatef(Globals::pointLight->getAngle(), 0, 0, 1);
	Globals::pointLight->draw();
	glPopMatrix();

	glPushMatrix();
	glLoadIdentity();
	glRotatef(Globals::spotLight->getAngle(), 0, 1, 0);
	Globals::spotLight->draw();
	glPopMatrix();

	if (Globals::bunny->isVisible()) {
		Globals::bunny->render();
	}
	else if (Globals::dragon->isVisible()) {
		Globals::dragon->render();
	}
	else if (Globals::bear->isVisible()) {
		Globals::bear->render();
	}
	
	Globals::shader->unbind();

	glFlush();
	glutSwapBuffers();
}
