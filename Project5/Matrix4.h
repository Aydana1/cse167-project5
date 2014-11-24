#pragma once
#include <iostream>
#include "Vector3.h"
#include "Vector4.h"
#include "GL\glut.h"

using namespace std;

#define M_PI 3.14159265358979323846

#include <math.h>

class Matrix4 {
protected:
	double m[4][4];   // matrix elements; first index is for rows, second for columns (row-major)

public:
	/* Constructors*/
	Matrix4();
	Matrix4(double, double, double, double,
		double, double, double, double,
		double, double, double, double,
		double, double, double, double);
	Matrix4(const Matrix4& other);
	Matrix4(Vector3&, Vector3&, Vector3&, Vector3&, double, double, double, double);


	/* Destructor */
	virtual ~Matrix4() {}

	/* Overloaded Operators */
	Matrix4& operator=(const Matrix4&);
	Matrix4 operator*(const Matrix4& m2); // multiply matrix with matrix
	Vector4 operator*(const Vector4& v); // multiply matrix with vector
	Vector3 operator*(const Vector3& v); // multiply matrix with vector
	Matrix4 operator*=(const Matrix4& m2);

	double operator() (const int i, const int j) { return get(i, j); }

	Matrix4* multiply(Matrix4& m2);

	double* getPointer();
	GLfloat* getGLMatrix();

	void set(int pos, double val);
	void set(int row, int col, double val);

	double get(int pos) const;
	double get(int row, int col) const;

	void identity(); // make identity matrix
	void transpose(); // transpose the matrix

	void setViewport(double w, double h); // initialize viewport matrix
	void setProjection(double left, double right, double top, double bottom, double near, double far);
	void setProjection(double fov, double aspect, double near, double far);

	void makeRotateX(double angle); // make rotation matrix about X axis with angle in degrees 
	// (note that the sin/cos functions in C++ expect radians so you need to convert to radians within the function)
	void makeRotateY(double angle); // make rotation matrix about Y axis with angle in degrees
	void makeRotateZ(double angle); // make rotation matrix about Z axis with angle in degrees
	void makeOrbitZ(double angle);

	void makeRotate(double angle, const Vector3& axis); // make a rotation about an arbitrary axis
	void makePivot(double angle, const Vector3& axis); // make a pivot about an arbitrary axis


	void makeScale(double sx, double sy, double sz); // make a non-uniform scaling matrix

	void makeTranslate(double tx, double ty, double tz); // make a translation matrix

	void print(std::string comment = ""); // print the matrix (display all 16 matrix components numerically on the screen in a 4x4 array)

	Matrix4 Inverse() const;
};
