#pragma once
#include "Group.h"

class MatrixTransform : public Group {
protected:
	Matrix4 M; // Transformation matrix
public:
	MatrixTransform();
	MatrixTransform(Matrix4 M);
	~MatrixTransform();

	void draw(Matrix4);

	void setM(Matrix4 M) { this->M = M; }
	Matrix4 getM() { return M; }

};

