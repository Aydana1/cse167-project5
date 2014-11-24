#pragma once

#include "Matrix4.h"
#include "BoundingSphere.h"
#include <math.h>

class Node {
protected:
	char* name;
	Node* parent;
	BoundingSphere* boundingSphere;
public:
	Node() {}
	virtual ~Node() {}

	char* getName() { return name; }
	void setName(char* n) { name = n; }

	virtual void draw(Matrix4 C) = 0;

	bool operator==(Node& n) const { return strcmp(name, n.name) == 0; }

	BoundingSphere* getBoundingSphere() { return boundingSphere; }
	bool isInBounds();
};

