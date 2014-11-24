#pragma once
#include <string>

using namespace std;

class Vector4 {
protected:
	double vec[4];

public:
	/* Constructor */
	Vector4(double x = 0.0, double y = 0.0, double z = 0.0, double w = 1.0);

	/* Destructor */
	virtual ~Vector4() {}

	/* Overloaded Operators */
	Vector4 operator+(const Vector4&);
	Vector4 operator-(const Vector4&);
	double operator[](const int index);

	void set(double x0, double y0, double z0, double w0);
	double get(int index) const;

	void setX(double x) { this->vec[0] = x; }
	void setY(double y) { this->vec[1] = y; }
	void setZ(double z) { this->vec[2] = z; }
	void setW(double w) { this->vec[3] = w; }

	double getX() const { return vec[0]; }
	double getY() const { return vec[1]; }
	double getZ() const { return vec[2]; }
	double getW() const { return vec[3]; }


	double length();

	void dehomogenize(); // dehomogenize the vector (scale it so that its fourth component is equal to one)
	void print(std::string comment = ""); // print x, y, z, and w components of the vector after a comment string
};

