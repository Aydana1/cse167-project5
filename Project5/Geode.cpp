#include "Geode.h"
#include "main.h"


Geode::Geode(char* n) {
	name = n;
}


Geode::~Geode() {
}

void Geode::draw(Matrix4 C) {
	/*if (Globals::cullingEnabled && isInBounds(C, boundingSphere)) {
		glMatrixMode(GL_MODELVIEW);
		Matrix4 cnew = C;
		cnew.transpose();
		glLoadMatrixd(cnew.getPointer());
		render();
		boundingSphere->draw(C);
	} else if (!Globals::cullingEnabled) {
		glMatrixMode(GL_MODELVIEW);
		Matrix4 cnew = C;
		cnew.transpose();
		glLoadMatrixd(cnew.getPointer());
		render();
		boundingSphere->draw(cnew);
	}*/
}

bool Geode::isInBounds(Matrix4 c, BoundingSphere* bs) {
	return false;
	/*for (int i = 0; i < 6; ++i) {
		if (!bs->isInBounds(Globals::planes[i].getPoint(), Globals::planes[i].getNormal())) {
			return false;
		}
	}
	return true;*/
}
