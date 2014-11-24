#include "Group.h"

Group::Group(char* n) {
	name = n;
	children = new std::list<Node*>();
}

Group::Group(const Group& other) {

}

Group::~Group() {
	for (std::list<Node*>::iterator it = children->begin(); it != children->end(); it++) {
		delete *it;
	}
	delete children;
}

void Group::addChild(Node* child) {
	children->push_back(child);
}

bool Group::removeChild(Node* child) {
	for (std::list<Node*>::iterator it = children->begin(); it != children->end(); it++) {
		if (*it == child) {
			children->erase(it);
			return true;
		}
	}
	return false;
}

bool Group::removeChild(char* childName) {
	for (Node* child : *children) {
		if (strcmp(childName, child->getName())) {
			children->remove(child);
			return true;
		}
	}
	return false;
}

bool Group::removeChild(int index) {
	std::list<Node*>::iterator it = children->begin();
	std::advance(it, index);
	children->erase(it);
	return true;
}

void Group::draw(Matrix4 C) {
	for (Node* child : *children) {
		child->draw(C);
		// draw(C);
	}
}
