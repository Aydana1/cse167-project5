#include "BoundingSphere.h"
#include "GL\glut.h"


BoundingSphere::BoundingSphere() {
	center.set(0.0, 0.0, 0.0);
	radius = 0.0;
	visible = true;
}

BoundingSphere::BoundingSphere(Vector3& center, float radius) {
	this->center = center;
	this->radius = radius;
	visible = true;
}

BoundingSphere::BoundingSphere(double x, double y, double z, float radius) {
	center.set(x, y, z);
	this->radius = radius;
	visible = true;
}


BoundingSphere::~BoundingSphere() {
}


/* Check to determine if any part of bounding sphere is in bounds.
* ( dist > 0 && |r| < |dist| ) = sphere compeletely inside bounds -> return TRUE
* ( dist > 0 && |r| > |dist| ) = sphere colliding with plane, center inside bounds -> return TRUE
* ( dist < 0 && |r| > |dist| ) = sphere colliding with plane, center outside bounds -> return TRUE
* ( dist < 0 && |r| < |dist| ) = sphere completely outside bounds -> return FALSE
*/
bool BoundingSphere::isInBounds(Vector3& p, Vector3& n) {
	// calculate distance between center of sphere and plane p lies on
	double dist = (center - p).dot(n);

	if (dist >= 0.0 && radius <= fabs(dist)) return true;
	if (dist >= 0.0 && radius >= fabs(dist)) return true;
	if (dist <= 0.0 && radius >= fabs(dist)) return true;
	return false;
}

void BoundingSphere::draw(Matrix4 C) {
	
	glMatrixMode(GL_MODELVIEW);
	Matrix4 cnew = C;
	cnew.transpose();
	glLoadMatrixd(cnew.getPointer());
	glColor3f(1.0, 0.0, 0.0);
	glutWireSphere(radius, 20, 20);
	
}