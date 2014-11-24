#include "Vector4.h"

using namespace std;

Vector4::Vector4(double x, double y, double z, double w) {
	vec[0] = x;
	vec[1] = y;
	vec[2] = z;
	vec[3] = w;
}

Vector4 Vector4::operator+(const Vector4& other) {
	return Vector4(this->getX() + other.getX(), this->getY() + other.getY(), this->getZ() + other.getZ(), /*this->getW() + other.getW()*/1.0);
}

Vector4 Vector4::operator-(const Vector4& other) {
	return Vector4(this->getX() - other.getX(), this->getY() - other.getY(), this->getZ() - other.getZ(), /*this->getW() - other.getW()*/1.0);
}

double Vector4::operator[](const int i) {
	return this->get(i);
}

void Vector4::set(double x, double y, double z, double w) {
	vec[0] = x;
	vec[1] = y;
	vec[2] = z;
	vec[3] = w;
}

double Vector4::get(int i) const {
	switch (i) {
	case 0: return vec[0];
	case 1: return vec[1];
	case 2: return vec[2];
	case 3: return vec[3];
	default: printf("Error: Invalid index.\n"); return -1.0;
	}
}

double Vector4::length() {
	return sqrt(vec[0] * vec[0] + vec[1] * vec[1] + vec[2] * vec[2]);
}

void Vector4::dehomogenize() {
	if (vec[3] != 0.0) {
		vec[0] /= vec[3];
		vec[1] /= vec[3];
		vec[2] /= vec[3];
		vec[3] = 1.0;
	}
}

void Vector4::print(std::string comment) {
	printf("%s (%.2f, %.2f, %.2f, %.2f)\n", comment.c_str(), getX(), getY(), getZ(), getW());
}