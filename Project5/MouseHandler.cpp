#include "MouseHandler.h"
#include "Matrix4.h"
#include "GL\glut.h"
#include "window.h"
#include "main.h"


static double mouseX, mouseY;
static bool lmbDown, rmbDown;

namespace Globals {
	extern ObjModel *currentModel;
}

using namespace std;

MouseHandler::MouseHandler() {
}


MouseHandler::~MouseHandler() {
}

void MouseHandler::mouseMotionCallback(int x, int y) {
	if (lmbDown) {
		// rotation
		rotateTrackball(Window::width, Window::height, mouseX, mouseY, x, y);
		mouseX = x;
		mouseY = y;
	} else if (rmbDown) {
		// zoom
		float endY = -(y - Window::height / 2.0);
		float scale = (endY - mouseY) / (Window::height / 2.0) + 1;
		Globals::currentModel->makeScale(scale);
		mouseY = endY;
	}
}

void MouseHandler::mouseClickCallback(int button, int state, int x, int y) {
	switch (button) {
		// LMB - Rotation
	case GLUT_LEFT_BUTTON:
		switch (state) {
		case GLUT_DOWN:
			lmbDown = true;
			mouseX = x;
			mouseY = y;
			break;
		case GLUT_UP:
			lmbDown = false;
			break;
		}
		break;
		// RMB - Zoom
	case GLUT_RIGHT_BUTTON:
		switch (state) {
		case GLUT_DOWN:
			rmbDown = true;
			mouseY = -(y - Window::height / 2.0f);
			break;
		case GLUT_UP:
			rmbDown = false;
		}
		break;
	}
}

void MouseHandler::rotateTrackball(int w, int h, int startX, int startY, int endX, int endY) {
	float trackballSize = 1.3;
	Matrix4 mInv;
	Vector3 v1, v2; // mouse drag positions
	float halfW = (float)w / 2.0;
	float halfH = (float)h / 2.0;
	float length;
	float size = halfW < halfH ? halfW : halfH;

	//float v1x = ((float)startX - halfW) / size;
	float v1x = (float)(2.0 * startX - w) / (float)w;
	//float v1y = ((float)(h - startY) - halfH) / size;
	float v1y = (float)(h - 2.0 * startY) / (float)h;
	length = sqrt(v1x*v1x + v1y*v1y);
	length = length < 1.0 ? length : 1.0;
	//float v1z = exp(length * length * -trackballSize);
	float v1z = sqrtf(1.001 - length * length);
	v1.set(v1x, v1y, v1z);
	v1.normalize();


	//float v2x = ((float)endX - halfW) / size;
	float v2x = (float)(2.0 * endX - w) / (float)w;
	//float v2y = ((float)(h - endY) - halfH) / size;
	float v2y = (float)(h - 2.0 * endY) / (float)h;
	length = sqrt(v2x*v2x + v2y*v2y);
	length = length < 1.0 ? length : 1.0;
	//float v2z = exp(length * length * -trackballSize);
	float v2z = sqrtf(1.001 - length * length);
	v2.set(v2x, v2y, v2z);
	v2.normalize();

	// rotation angle (in degrees)
	double rotationAngle = v1.angleFrom(v2);

	// rotation axis
	Vector3 axis;
	axis.cross(v2, v1);

	// convert axis from world to object
	mInv.identity();
	/*for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			mInv.set(i, j, Globals::currentModel->getMatrix().get(i, j));
		}
	}*/

	mInv = Globals::currentModel->getMatrix().Inverse();
	
	Vector4 v3 = mInv * Vector4(axis[0], axis[1], axis[2], 0.0);
	axis = Vector3(v3[0], v3[1], v3[2]);
	axis.normalize();

	// Rotate model view matrix
	//Globals::currentModel->getMatrix().makeRotate(rotationAngle, axis);

	//glPushMatrix();
	//glLoadIdentity();
	glRotatef(rotationAngle, axis.getX(), axis.getY(), axis.getZ());
	//glPopMatrix();
}