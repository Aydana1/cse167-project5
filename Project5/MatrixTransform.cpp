#include "MatrixTransform.h"
//#include "Plane.h"
//
//namespace Globals {
//	extern Plane* planes;
//}


MatrixTransform::MatrixTransform() {
	M.identity();
}

MatrixTransform::MatrixTransform(Matrix4 M) {
	this->M = M;

}


MatrixTransform::~MatrixTransform() {
}

void MatrixTransform::draw(Matrix4 C) {
	Matrix4 tm = C * M;
	/*for (int i = 0; i < 6; ++i)
	if (!boundingSphere->isInBounds(Globals::planes[i].getPoint(), Globals::planes[i].getNormal()))
	return;*/
	for (Node* child : *children) {
		child->draw(tm);
	}
}
