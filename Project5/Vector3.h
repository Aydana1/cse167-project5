#pragma once
#include "GLee.h"
#include <string>
#include <math.h>

using namespace std;

class Vector3 {
protected:
	double vec[3]; // (x, y, z) position of the vector

public:
	/* Constructor */
	Vector3(double x = 0.0, double y = 0.0, double z = 0.0);
	Vector3(const Vector3&);

	/* Destructor*/
	virtual ~Vector3() {}

	/* Overloaded Operators */
	Vector3& operator=(const Vector3&);
	Vector3 operator+(const Vector3&); // overload operator '+' for addition
	Vector3 operator-(const Vector3&); // overload operator '-' for subtraction
	double operator[](const int i);
	Vector3 operator*(const double);

	void set(double x0, double y0, double z0);
	double get(int index);
	double get(char c);

	double getX() const { return vec[0]; }
	double getY() const { return vec[1]; }
	double getZ() const { return vec[2]; }

	void negate(); // negation
	void scale(double s); // scale (multiplication with scalar value)
	double dot(const Vector3& b);
	double dot(const Vector3& a, const Vector3& b); // dot product, returns result
	Vector3 cross(const Vector3& a, const Vector3& b); // cross product, returns result and puts it in calling vector
	double length(); // length of the vector
	void normalize(); // normalize the vector (make it so that its length is equal to one)
	void print(std::string comment = ""); // print x, y, and z components of the vector after a comment string
	double angleFrom(Vector3& b);
};
