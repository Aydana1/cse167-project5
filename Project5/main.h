#pragma once

#include "Shader.h"
#include "Camera.h"
#include "ObjModel.h"
#include "Light.h"

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
