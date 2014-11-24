#include <math.h>

#include "Matrix4.h"

using namespace std;

/**
* Constructors
*/
Matrix4::Matrix4() {
	for (int i = 0; i<4; ++i) {
		for (int j = 0; j<4; ++j) {
			//m[i][j] = i == j ? 1.0 : 0.0;
			m[i][j] = 0.0;
		}
	}
}

Matrix4::Matrix4(double m0, double m1, double m2, double m3,
	double m4, double m5, double m6, double m7,
	double m8, double m9, double m10, double m11,
	double m12, double m13, double m14, double m15) {

	m[0][0] = m0;	m[0][1] = m1;	m[0][2] = m2;	m[0][3] = m3;
	m[1][0] = m4;	m[1][1] = m5;	m[1][2] = m6;	m[1][3] = m7;
	m[2][0] = m8;	m[2][1] = m9;	m[2][2] = m10;	m[2][3] = m11;
	m[3][0] = m12;	m[3][1] = m13;	m[3][2] = m14;	m[3][3] = m15;
}

Matrix4::Matrix4(const Matrix4& other) {
	m[0][0] = other.m[0][0];	m[0][1] = other.m[0][1];	m[0][2] = other.m[0][2];	m[0][3] = other.m[0][3];
	m[1][0] = other.m[1][0];	m[1][1] = other.m[1][1];	m[1][2] = other.m[1][2];	m[1][3] = other.m[1][3];
	m[2][0] = other.m[2][0];	m[2][1] = other.m[2][1];	m[2][2] = other.m[2][2];	m[2][3] = other.m[2][3];
	m[3][0] = other.m[3][0];	m[3][1] = other.m[3][1];	m[3][2] = other.m[3][2];	m[3][3] = other.m[3][3];
}

Matrix4::Matrix4(Vector3 &a, Vector3 &b, Vector3 &c, Vector3 &d, double w, double x, double y, double z) {
	m[0][0] = a.getX();
	m[0][1] = a.getY();
	m[0][2] = a.getZ();

	m[1][0] = b.getX();
	m[1][1] = b.getY();
	m[1][2] = b.getZ();

	m[2][0] = c.getX();
	m[2][1] = c.getY();
	m[2][2] = c.getZ();

	m[3][0] = d.getX();
	m[3][1] = d.getY();
	m[3][2] = d.getZ();

	m[0][3] = w;
	m[1][3] = x;
	m[2][3] = y;
	m[3][3] = z;

	//transpose();
}

/**
* Overloaded operators
*/
Matrix4& Matrix4::operator=(const Matrix4& m2) {
	if (this != &m2) {
		for (int i = 0; i<4; ++i) {
			for (int j = 0; j<4; ++j) {
				m[i][j] = m2.m[i][j];
			}
		}
	}
	return *this;
}

Matrix4 Matrix4::operator*(const Matrix4& m2) {

	/*for (int i = 0; i < 4; i++) {
	for (int j = 0; j < 4; j++) {
	double sum = 0.0;
	for (int k = 0; k < 4; k++) {
	sum += (m[i][k] * m2.get(k, j));
	}
	m[i][j] = sum;
	}
	}
	return *this;*/

	double n[4][4];
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			n[i][j] = 0.0;
			for (int k = 0; k < 4; k++) {
				n[i][j] += m[i][k] * m2.get(k, j);
			}
		}
	}
	return Matrix4(n[0][0], n[0][1], n[0][2], n[0][3],
		n[1][0], n[1][1], n[1][2], n[1][3],
		n[2][0], n[2][1], n[2][2], n[2][3],
		n[3][0], n[3][1], n[3][2], 1.0);
}

Matrix4 Matrix4::operator*=(const Matrix4& m2) {
	*this = *this * m2;
	return *this;
}

Matrix4* Matrix4::multiply(Matrix4& m2) {
	double n[4][4];
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			n[i][j] = 0.0;
			for (int k = 0; k < 4; k++) {
				n[i][j] += m[i][k] * m2.get(k, j);
			}
		}
	}
	return &Matrix4(n[0][0], n[0][1], n[0][2], n[0][3],
		n[1][0], n[1][1], n[1][2], n[1][3],
		n[2][0], n[2][1], n[2][2], n[2][3],
		n[3][0], n[3][1], n[3][2], 1.0);
}

Vector4 Matrix4::operator*(const Vector4& v) {

	double x = m[0][0] * v.getX() + m[0][1] * v.getY() + m[0][2] * v.getZ() + m[0][3] * v.getW();
	double y = m[1][0] * v.getX() + m[1][1] * v.getY() + m[1][2] * v.getZ() + m[1][3] * v.getW();
	double z = m[2][0] * v.getX() + m[2][1] * v.getY() + m[2][2] * v.getZ() + m[2][3] * v.getW();
	double w = m[3][0] * v.getX() + m[3][1] * v.getY() + m[3][2] * v.getZ() + m[3][3] * v.getW();

	return Vector4(x, y, z, w);
}

Vector3 Matrix4::operator*(const Vector3& v) {

	double x = m[0][0] * v.getX() + m[0][1] * v.getY() + m[0][2] * v.getZ();
	double y = m[1][0] * v.getX() + m[1][1] * v.getY() + m[1][2] * v.getZ();
	double z = m[2][0] * v.getX() + m[2][1] * v.getY() + m[2][2] * v.getZ();
	//double w = m[3][0] * v.getX() + m[3][1] * v.getY() + m[3][2] * v.getZ() + m[3][3] * v.getW();

	return Vector3(x, y, z);
}


/**
* Getters & Setters
*/

// return pointer to matrix elements
double* Matrix4::getPointer() {
	return &m[0][0];
}


void Matrix4::set(int pos, double val) {
	if (pos < 0 || pos > 15) return;
	int i = pos << 2;
	int j = pos % 4;
	m[i][j] = val;
}

void Matrix4::set(int row, int col, double val) {
	if (row < 0 || row > 3 || col < 0 || col > 3) return;
	m[row][col] = val;
}

double Matrix4::get(int pos) const {
	if (pos < 0 || pos > 15) return 0.0;
	int i = pos << 2;
	int j = pos % 4;
	return m[i][j];
}

double Matrix4::get(int row, int col) const {
	if (row < 0 || row > 3 || col < 0 || col > 3) return 0.0;
	return m[row][col];
}

// set matrix to identity matrix
void Matrix4::identity() {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (i == j) m[i][j] = 1.0;
			else		m[i][j] = 0.0;
		}
	}
}

// transpose the matrix (mirror at diagonal)
void Matrix4::transpose() {
	Matrix4 temp;
	for (int i = 0; i<4; ++i) {
		for (int j = 0; j<4; ++j) {
			temp.m[j][i] = m[i][j];
		}
	}
	*this = temp;  // copy temporary values to this matrix
}

// Initialize viewport matrix (D)
void Matrix4::setViewport(double w, double h) {

	m[0][0] = w / 2;	m[0][1] = 0.0;		m[0][2] = 0.0;	m[0][3] = w / 2;
	m[1][0] = 0.0;		m[1][1] = h / 2;	m[1][2] = 0.0;	m[1][3] = h / 2;
	m[2][0] = 0.0;		m[2][1] = 0.0;		m[2][2] = 0.5;	m[2][3] = 0.5;
	m[3][0] = 0.0;		m[3][2] = 0.0;		m[3][2] = 0.0;	m[3][3] = 1.0;
}

// Initialize projection matrix (P)
void Matrix4::setProjection(double left, double right, double top, double bottom, double nearp, double farp) {
	m[0][0] = 2 * nearp / (right - left);	m[0][1] = 0.0;		m[0][2] = (right + left) / (right - left);	m[0][3] = 0.0;
	m[1][0] = 0.0;		m[1][1] = 2 * nearp / (right - left);	m[1][2] = (top + bottom) / (top - bottom);	m[1][3] = 0.0;
	m[2][0] = 0.0;		m[2][1] = 0.0;		m[2][2] = (nearp + farp) / (nearp - farp);	m[2][3] = -(2 * nearp * farp) / (nearp - farp);
	m[3][0] = 0.0;		m[3][2] = 0.0;		m[3][2] = -1.0;	m[3][3] = 0.0;
}

void Matrix4::setProjection(double fov, double aspect, double nearp, double farp) {
	double fovRad = (fov / 180.0) * M_PI; // convert fov to radians
	double tangent = tan(fovRad / 2.0); // tangent of half of fov

	m[0][0] = 1 / (aspect*tangent);	m[0][1] = 0.0;		m[0][2] = 0.0;	m[0][3] = 0.0;
	m[1][0] = 0.0;		m[1][1] = 1 / tangent;	m[1][2] = 0.0;	m[1][3] = 0.0;
	m[2][0] = 0.0;		m[2][1] = 0.0;		m[2][2] = (nearp + farp) / (nearp - farp);	m[2][3] = (2 * nearp * farp) / (nearp - farp);
	m[3][0] = 0.0;		m[3][2] = 0.0;		m[3][2] = -1.0;	m[3][3] = 0.0;
}

// Creates a rotation matrix which rotates about the x axis.
// angle is expected in degrees
void Matrix4::makeRotateX(double angle) {
	angle = (angle / 180.0) * M_PI;

	Matrix4 rm = Matrix4(1.0, 0.0, 0.0, 0.0,
		0.0, cos(angle), -sin(angle), 0.0,
		0.0, sin(angle), cos(angle), 0.0,
		0.0, 0.0, 0.0, 1.0);

	*this *= rm;
}

// Creates a rotation matrix which rotates about the y axis.
// angle is expected in degrees
void Matrix4::makeRotateY(double angle) {
	angle = (angle / 180.0) * M_PI;  // convert from degrees to radians

	Matrix4 rm = Matrix4(cos(angle), 0.0, sin(angle), 0.0,
		0.0, 1.0, 0.0, 0.0,
		-sin(angle), 0.0, cos(angle), 0.0,
		0.0, 0.0, 0.0, 1.0);

	/*Matrix4 *res = this->multiply(rm);
	for (int i = 0; i < 4; i++) {
	for (int j = 0; j < 4; j++) {
	m[i][j] = res->get(i, j);
	}
	}*/

	*this *= rm;
}

// Creates a rotation matrix which rotates about the z axis.
// angle is expected in degrees
void Matrix4::makeRotateZ(double angle) {
	angle = angle / 180.0 * M_PI;

	Matrix4 rm = Matrix4(cos(angle), -sin(angle), 0.0, 0.0,
		sin(angle), cos(angle), 0.0, 0.0,
		0.0, 0.0, 1.0, 0.0,
		0.0, 0.0, 0.0, 1.0);
	*this *= rm;
}

// Creates a rotation matrix which orbits around the z axis of OpenGL's window.
// Angle is expected in degrees.
void Matrix4::makeOrbitZ(double angle) {
	angle = angle / 180.0 * M_PI;

	Matrix4 rm = Matrix4(cos(angle), -sin(angle), 0.0, 0.0,
		sin(angle), cos(angle), 0.0, 0.0,
		0.0, 0.0, 1.0, 0.0,
		0.0, 0.0, 0.0, 1.0);

	Matrix4 *res = rm.multiply(*this);
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			m[i][j] = res->get(i, j);
		}
	}
}

// Creates a rotation matrix which rotates arount an arbitrary axis, given as a 3D vector
void Matrix4::makeRotate(double angle, const Vector3& axis) {
	Vector3 a = axis;
	a.normalize();
	double x = a.getX();
	double y = a.getY();
	double z = a.getZ();

	angle = angle / 180.0 * M_PI;
	double c = cos(angle);
	double s = sin(angle);

	// rotation matrix
	Matrix4 rm = Matrix4(
		(x*x)*(1 - c) + c, (x*y)*(1 - c) - (z*s), (x*z)*(1 - c) + (y*s), 0.0,
		(x*y)*(1 - c) + (z*s), (y*y)*(1 - c) + c, (y*z)*(1 - c) - (x*s), 0.0,
		(x*z)*(1 - c) - (y*s), (y*z)*(1 - c) + (x*s), (z*z)*(1 - c) + c, 0.0,
		0.0, 0.0, 0.0, 1.0);

	*this *= rm;
}

void Matrix4::makePivot(double angle, const Vector3& axis) {
	Vector3 a;
	double ax = axis.getX();
	double ay = axis.getY();
	double az = axis.getZ();
	a.set(ax, ay, az);
	a.normalize();

	angle = angle / 180.0 * M_PI;
	double c = cos(angle);
	double s = sin(angle);

	// rotation matrix
	/*
	m[0][0] = c + ax*ax*(1 - c);	m[0][1] = ax*ay*(1 - c) - az*s;	m[0][2] = ax*az*(1 - c) + ay*s;	m[0][3] = 0.0;
	m[1][0] = ay*ax*(1 - c) + az*s;	m[1][1] = c + ax*ax*(1 - c);	m[1][2] = ay*az*(1 - c) - ax*s;	m[1][3] = 0.0;
	m[2][0] = az*ax*(1 - c) + ay*s;	m[2][1] = az*ay*(1 - c) + ax*s;	m[2][2] = c + az*az*(1 - c);	m[2][3] = 0.0;
	m[3][0] = 0.0;					m[3][1] = 0.0;					m[3][2] = 0.0;					m[3][3] = 1.0;
	*/

	Matrix4 rm = Matrix4(c + ax*ax*(1 - c), ax*ay*(1 - c) - az*s, ax*az*(1 - c) + ay*s, 0.0,
		ay*ax*(1 - c) + az*s, c + ay*ay*(1 - c), ay*az*(1 - c) - ax*s, 0.0,
		az*ax*(1 - c) + ay*s, az*ay*(1 - c) + ax*s, c + az*az*(1 - c), 0.0,
		0.0, 0.0, 0.0, 1.0);

	Matrix4 *res = rm.multiply(*this);
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			m[i][j] = res->get(i, j);
		}
	}
}

// Scales the matrix.
// Values < 1.0 scale the matrix down, > 1.0 scale it up.
void Matrix4::makeScale(double sx, double sy, double sz) {

	Matrix4 sm = Matrix4(sx, 0.0, 0.0, 0.0,
		0.0, sy, 0.0, 0.0,
		0.0, 0.0, sz, 0.0,
		0.0, 0.0, 0.0, 1.0);
	*this *= sm;

	/*identity();
	m[0][0] = sx;
	m[1][1] = sy;
	m[2][2] = sz;
	m[3][3] = 1.0;*/
}

// Creates a translation matrix
void Matrix4::makeTranslate(double tx, double ty, double tz) {

	Matrix4 tm(1.0, 0.0, 0.0, tx,
		0.0, 1.0, 0.0, ty,
		0.0, 0.0, 1.0, tz,
		0.0, 0.0, 0.0, 1.0);


	/*Matrix4 *res = tm.multiply(*this);
	for (int i = 0; i < 4; i++) {
	for (int j = 0; j < 4; j++) {
	m[i][j] = res->get(i, j);
	}
	}*/

	*this *= tm;

	/*identity();
	m[0][3] = tx;
	m[1][3] = ty;
	m[2][3] = tz;
	m[3][3] = 1.0;*/
}

void Matrix4::print(std::string comment) {
	std::cout << comment << "\n";
	for (int i = 0; i < 4; i++) {
		std::cout << "[ ";
		for (int j = 0; j < 4; j++) {
			if (j < 3) printf("%.2f,\t", m[i][j]);
			else	   printf("%.2f ]\n", m[i][j]);
		}
	}
	std::cout << "\n";
}

/* Matrix inverstion function by Matthew Fisher. Found at:
* https://graphics.stanford.edu/~mdfisher/Code/Engine/Matrix4.cpp.html
*/
Matrix4 Matrix4::Inverse() const {
	//
	// Inversion by Cramer's rule.  Code taken from an Intel publication
	//
	double Result[4][4];
	double tmp[12]; /* temp array for pairs */
	double src[16]; /* array of transpose source matrix */
	double det; /* determinant */
	/* transpose matrix */
	for (int i = 0; i < 4; i++) {
		src[i + 0] = (*this).get(i, 0);
		src[i + 4] = (*this).get(i, 1);
		src[i + 8] = (*this).get(i, 2);
		src[i + 12] = (*this).get(i, 3);
	}
	/* calculate pairs for first 8 elements (cofactors) */
	tmp[0] = src[10] * src[15];
	tmp[1] = src[11] * src[14];
	tmp[2] = src[9] * src[15];
	tmp[3] = src[11] * src[13];
	tmp[4] = src[9] * src[14];
	tmp[5] = src[10] * src[13];
	tmp[6] = src[8] * src[15];
	tmp[7] = src[11] * src[12];
	tmp[8] = src[8] * src[14];
	tmp[9] = src[10] * src[12];
	tmp[10] = src[8] * src[13];
	tmp[11] = src[9] * src[12];
	/* calculate first 8 elements (cofactors) */
	Result[0][0] = tmp[0] * src[5] + tmp[3] * src[6] + tmp[4] * src[7];
	Result[0][0] -= tmp[1] * src[5] + tmp[2] * src[6] + tmp[5] * src[7];
	Result[0][1] = tmp[1] * src[4] + tmp[6] * src[6] + tmp[9] * src[7];
	Result[0][1] -= tmp[0] * src[4] + tmp[7] * src[6] + tmp[8] * src[7];
	Result[0][2] = tmp[2] * src[4] + tmp[7] * src[5] + tmp[10] * src[7];
	Result[0][2] -= tmp[3] * src[4] + tmp[6] * src[5] + tmp[11] * src[7];
	Result[0][3] = tmp[5] * src[4] + tmp[8] * src[5] + tmp[11] * src[6];
	Result[0][3] -= tmp[4] * src[4] + tmp[9] * src[5] + tmp[10] * src[6];
	Result[1][0] = tmp[1] * src[1] + tmp[2] * src[2] + tmp[5] * src[3];
	Result[1][0] -= tmp[0] * src[1] + tmp[3] * src[2] + tmp[4] * src[3];
	Result[1][1] = tmp[0] * src[0] + tmp[7] * src[2] + tmp[8] * src[3];
	Result[1][1] -= tmp[1] * src[0] + tmp[6] * src[2] + tmp[9] * src[3];
	Result[1][2] = tmp[3] * src[0] + tmp[6] * src[1] + tmp[11] * src[3];
	Result[1][2] -= tmp[2] * src[0] + tmp[7] * src[1] + tmp[10] * src[3];
	Result[1][3] = tmp[4] * src[0] + tmp[9] * src[1] + tmp[10] * src[2];
	Result[1][3] -= tmp[5] * src[0] + tmp[8] * src[1] + tmp[11] * src[2];
	/* calculate pairs for second 8 elements (cofactors) */
	tmp[0] = src[2] * src[7];
	tmp[1] = src[3] * src[6];
	tmp[2] = src[1] * src[7];
	tmp[3] = src[3] * src[5];
	tmp[4] = src[1] * src[6];
	tmp[5] = src[2] * src[5];

	tmp[6] = src[0] * src[7];
	tmp[7] = src[3] * src[4];
	tmp[8] = src[0] * src[6];
	tmp[9] = src[2] * src[4];
	tmp[10] = src[0] * src[5];
	tmp[11] = src[1] * src[4];
	/* calculate second 8 elements (cofactors) */
	Result[2][0] = tmp[0] * src[13] + tmp[3] * src[14] + tmp[4] * src[15];
	Result[2][0] -= tmp[1] * src[13] + tmp[2] * src[14] + tmp[5] * src[15];
	Result[2][1] = tmp[1] * src[12] + tmp[6] * src[14] + tmp[9] * src[15];
	Result[2][1] -= tmp[0] * src[12] + tmp[7] * src[14] + tmp[8] * src[15];
	Result[2][2] = tmp[2] * src[12] + tmp[7] * src[13] + tmp[10] * src[15];
	Result[2][2] -= tmp[3] * src[12] + tmp[6] * src[13] + tmp[11] * src[15];
	Result[2][3] = tmp[5] * src[12] + tmp[8] * src[13] + tmp[11] * src[14];
	Result[2][3] -= tmp[4] * src[12] + tmp[9] * src[13] + tmp[10] * src[14];
	Result[3][0] = tmp[2] * src[10] + tmp[5] * src[11] + tmp[1] * src[9];
	Result[3][0] -= tmp[4] * src[11] + tmp[0] * src[9] + tmp[3] * src[10];
	Result[3][1] = tmp[8] * src[11] + tmp[0] * src[8] + tmp[7] * src[10];
	Result[3][1] -= tmp[6] * src[10] + tmp[9] * src[11] + tmp[1] * src[8];
	Result[3][2] = tmp[6] * src[9] + tmp[11] * src[11] + tmp[3] * src[8];
	Result[3][2] -= tmp[10] * src[11] + tmp[2] * src[8] + tmp[7] * src[9];
	Result[3][3] = tmp[10] * src[10] + tmp[4] * src[8] + tmp[9] * src[9];
	Result[3][3] -= tmp[8] * src[9] + tmp[11] * src[10] + tmp[5] * src[8];
	/* calculate determinant */
	det = src[0] * Result[0][0] + src[1] * Result[0][1] + src[2] * Result[0][2] + src[3] * Result[0][3];
	/* calculate matrix inverse */
	det = 1.0f / det;

	Matrix4 FloatResult;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			FloatResult.set(i, j, float(Result[i][j] * det));
		}
	}
	return FloatResult;
}

GLfloat* Matrix4::getGLMatrix() {
	GLfloat glm[16];
	for (int i = 0; i < 4; ++i)
		for (int j = 0; j < 4; ++j)
			glm[(i * 4) + j] = m[j][i];
	return glm;
}