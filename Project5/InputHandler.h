#ifndef _INPUTHANDLER_H_
#define _INPUTHANDLER_H_

#include "Shader.h"
#include "Camera.h"
#include "ObjModel.h"
#include "Light.h"
#include <ostream>

namespace Globals {
	extern Camera *camera;
	extern ObjModel *bunny;
	extern ObjModel *dragon;
	extern ObjModel *bear;
	extern ObjModel *currentModel;
	extern PointLight *pointLight;
	extern SpotLight *spotLight;
	extern bool usingShader;
	extern Shader *shader;
};



class InputHandler {
private:
	
public:
	InputHandler();
	~InputHandler();

	// Keyboard input
	static void processNormalKeys(unsigned char key, int x, int y);
	static void processSpecialKeys(int key, int x, int y);

	// Mouse input
	static void mouseMotionCallback(int x, int y);
	static void mouseClickCallback(int button, int state, int x, int y);
	static void rotateTrackball(int w, int h, int startX, int startY, int endX, int endY);

	static void rotateLight(int w, int h, int startX, int startY, int endX, int endY);

};

#endif