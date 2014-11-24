#pragma once
#include "Vector3.h"
#include "Matrix4.h"

class BoundingSphere {
private:
	Vector3 center;
	float radius;
	bool visible;
public:
	BoundingSphere();
	BoundingSphere(Vector3& center, float radius);
	BoundingSphere(double x, double y, double z, float radius);
	~BoundingSphere();

	void set(Vector3& c, float r) { center = c; radius = r; }

	Vector3& getCenter() { return center; }
	void setCenter(double x, double y, double z) { center.set(x, y, z); }

	float getRadius() { return radius; }
	void setRadius(float r) { radius = r; }

	bool isVisible() { return visible; }
	void setVisible(bool v) { visible = v; }

	bool isInBounds(Vector3& p, Vector3& n);

	void draw(Matrix4 C);
};

