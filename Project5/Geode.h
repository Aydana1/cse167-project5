#pragma once
#include "Node.h"
#include "Camera.h"


class Geode : public Node {
public:
	Geode(char* n = "");
	virtual ~Geode();

	void draw(Matrix4);

	virtual void render() = 0;

	// frustum culling test function
	bool isInBounds(Matrix4, BoundingSphere*);
};

