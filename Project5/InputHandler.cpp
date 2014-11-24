#include "InputHandler.h"

#include "window.h"

using namespace std;

static double mouseX, mouseY;
static bool lmbDown, rmbDown;

static bool controllingModel = true;
static bool controllingPointLight = false;
static bool controllingSpotLight = false;

//static Shader shader = Shader("../shaders/silhouette.vert", "../shaders/silhouette.frag", true);

InputHandler::InputHandler() {}

InputHandler::~InputHandler() {}

void InputHandler::processNormalKeys(unsigned char key, int x, int y) {
	
	Globals::currentModel = Globals::bunny->isVisible() ? Globals::bunny : Globals::dragon->isVisible() ? Globals::dragon : Globals::bear;


	switch (key) {

	case 'z':
		Globals::currentModel->getMatrix().makeRotateZ(-10);
		break;
	case 'Z':
		Globals::currentModel->getMatrix().makeRotateZ(10);
		break;
	case 'x':
		Globals::currentModel->getMatrix().makeRotateX(-10);
		break;
	case 'X':
		Globals::currentModel->getMatrix().makeRotateX(10);
		break;
	case 'y':
		Globals::currentModel->getMatrix().makeRotateY(-10);
		break;
	case 'Y':
		Globals::currentModel->getMatrix().makeRotateY(10);
		break;
	case 's':
		// scale model down (about its center, not the center of the screen)
		Globals::currentModel->makeScale(.9);
		break;
	case 'S':
		// scale model up (about its center, not the center of the screen)
		Globals::currentModel->makeScale(1.1);
		break;
	case 'r':
	case 'R':
		Globals::currentModel->reset();
		break;
	case '1':
		controllingModel = true;
		controllingPointLight = false;
		controllingSpotLight = false;
		printf("Controlling Model\n");
		break;
	case '2':
		controllingModel = false;
		controllingPointLight = true;
		controllingSpotLight = false;
		printf("Controlling PointLight\n");
		break;
	case '3':
		controllingModel = false;
		controllingPointLight = false;
		controllingSpotLight = true;
		printf("Controlling SpotLight\n");
		break;
	case 'p':
		Globals::usingShader = !Globals::usingShader;
		if (Globals::usingShader) {
			//Globals::shader->bind();
			Globals::pointLight->disable();
			//Globals::spotLight->enable();
		} else {
			//Globals::shader->unbind();
			Globals::pointLight->enable();
			//Globals::spotLight->enable();
		}
		break;
	case 27:
		exit(0);
		break;
	default: return;
	}

}

void InputHandler::processSpecialKeys(int key, int x, int y) {
	switch (key) {
	case GLUT_KEY_F1:
		Globals::currentModel = Globals::bunny;
		Globals::bunny->setVisible(true);
		Globals::dragon->setVisible(false);
		Globals::bear->setVisible(false);
		break;
	case GLUT_KEY_F2:
		Globals::currentModel = Globals::dragon;
		Globals::bunny->setVisible(false);
		Globals::dragon->setVisible(true);
		Globals::bear->setVisible(false);
		break;
	case GLUT_KEY_F3:
		Globals::currentModel = Globals::bear;
		Globals::bunny->setVisible(false);
		Globals::dragon->setVisible(false);
		Globals::bear->setVisible(true);
		break;
	default:
		break;
	}
}

void InputHandler::mouseMotionCallback(int x, int y) {
	if (lmbDown) {
		// rotation
		if (controllingModel) {
			rotateTrackball(Window::width, Window::height, mouseX, mouseY, x, y);
			mouseX = x;
			mouseY = y;
		} else {
			rotateLight(Window::width, Window::height, mouseX, mouseY, x, y);
		}
	} else if (rmbDown) {
		// zoom
		float endY = -(y - Window::height / 2.0);
		float scale = (endY - mouseY) / (Window::height / 2.0) + 1;
		Globals::currentModel->makeScale(scale);
		mouseY = endY;
	}
}

void InputHandler::mouseClickCallback(int button, int state, int x, int y) {
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

void InputHandler::rotateTrackball(int w, int h, int startX, int startY, int endX, int endY) {
	float trackballSize = 1.3;
	Matrix4 mInv;
	Vector3 v1, v2; // mouse drag positions
	float halfW = (float)w / 2.0;
	float halfH = (float)h / 2.0;
	float length;
	float size = halfW < halfH ? halfW : halfH;

	float v1x = (float)(2.0 * startX - w) / (float)w;
	float v1y = (float)(h - 2.0 * startY) / (float)h;
	length = sqrt(v1x*v1x + v1y*v1y);
	length = length < 1.0 ? length : 1.0;
	float v1z = sqrtf(1.001 - length * length);
	v1.set(v1x, v1y, v1z);
	v1.normalize();


	float v2x = (float)(2.0 * endX - w) / (float)w;
	float v2y = (float)(h - 2.0 * endY) / (float)h;
	length = sqrt(v2x*v2x + v2y*v2y);
	length = length < 1.0 ? length : 1.0;
	float v2z = sqrtf(1.001 - length * length);
	v2.set(v2x, v2y, v2z);
	v2.normalize();

	// rotation angle (in degrees)
	double rotationAngle = v2.angleFrom(v1);

	// rotation axis
	Vector3 axis;
	axis.cross(v1, v2);

	mInv = Globals::currentModel->getMatrix();

	Vector4 v3 = mInv * Vector4(axis[0], axis[1], axis[2], 0.0);
	axis = Vector3(v3[0], v3[1], v3[2]);
	axis.normalize();

	// Rotate model view matrix
	if (controllingModel) {
		Globals::currentModel->getMatrix().makeRotate(rotationAngle, axis);
	}

}

void InputHandler::rotateLight(int w, int h, int startX, int startY, int endX, int endY) {
	float theta = 0.0f;
	if (endY < startY) {
		theta -= 100 * acos((endX*startX + endY*startY) / (sqrtf(endX*endX + endY*endY) * sqrtf(startX*startX + startY*startY)));
	} else if (endY > startY) {
		theta += 100 * acos((endX*startX + endY*startY) / (sqrtf(endX*endX + endY*endY) * sqrtf(startX*startX + startY*startY)));
	}

	if (theta > 360.0) theta = 0.0;
	if (theta < 0.0) theta = 360.0;

	if (controllingPointLight) {
		glPushMatrix();
		glRotatef(theta, 0, 0, 1);
		Globals::pointLight->setAngle(theta);
		Globals::pointLight->setPos(Globals::pointLight->getPosition());
		Globals::pointLight->draw();
		glPopMatrix();
	} else if (controllingSpotLight) {
		glPushMatrix();
		glRotatef(theta, 0, 1, 0);
		Globals::spotLight->setAngle(theta);
		Globals::spotLight->setPos(Globals::spotLight->getPosition());
		Globals::spotLight->setDir(Globals::spotLight->getDirection());
		Globals::spotLight->draw();
		glPopMatrix();
	}
}