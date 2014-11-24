#pragma once
#include "Node.h"
#include <list>

class Group : public Node {
protected:
	std::list<Node*> *children;

public:
	Group(char* n = "");
	Group(const Group&);
	virtual ~Group();

	void addChild(Node*); // Add child
	bool removeChild(Node*); // Remove child
	bool removeChild(char* nodeName); // Remove child by name
	bool removeChild(int i); // Remove child by index

	void setParent(Node& p) { *this->parent = p; }

	void draw(Matrix4 C);
};

