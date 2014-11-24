#include "Vector3.h"

using namespace std;

Vector3::Vector3(double x, double y, double z) {
	set(x, y, z);
}

Vector3::Vector3(const Vector3& other) {
	set(other.getX(), other.getY(), other.getZ());
}

Vector3& Vector3::operator= (const Vector3 &v) {
	vec[0] = v.getX();
	vec[1] = v.getY();
	vec[2] = v.getZ();

	return (*this);
}

Vector3 Vector3::operator+(const Vector3& other) {
	return Vector3(this->getX() + other.getX(), this->getY() + other.getY(), this->getZ() + other.getZ());
}

Vector3 Vector3::operator-(const Vector3& other) {
	return Vector3(this->getX() - other.getX(), this->getY() - other.getY(), this->getZ() - other.getZ());
}

double Vector3::operator[](const int i) {
	return this->get(i);
}

Vector3 Vector3::operator*(double d) {
	return Vector3(getX()*d, getY()*d, getZ()*d);
}

void Vector3::set(double x, double y, double z) {
	vec[0] = x;
	vec[1] = y;
	vec[2] = z;
}

double Vector3::get(int i) {
	switch (i) {
	case 0: return vec[0];
	case 1: return vec[1];
	case 2: return vec[2];
	default: printf("Error: Invalid index.\n"); return -1.0;
	}
}

double Vector3::get(char c) {
	switch (c) {
	case 'x':
	case 'X':
		return vec[0];
	case 'y':
	case 'Y':
		return vec[1];
	case 'z':
	case 'Z':
		return vec[2];
	default: printf("Error: Invalid index.\n"); return -1.0;
	}
}

void Vector3::negate() {
	vec[0] = -vec[0];
	vec[1] = -vec[1];
	vec[2] = -vec[2];
}

void Vector3::scale(double s) {
	vec[0] *= s;
	vec[1] *= s;
	vec[2] *= s;
}

double Vector3::dot(const Vector3& b) {
	return vec[0] * b.getX() + vec[1] * b.getY() + vec[2] * b.getZ();
}

double Vector3::dot(const Vector3& a, const Vector3& b) {
	return a.getX() * b.getX() + a.getY() * b.getY() + a.getZ() * b.getZ();
}

Vector3 Vector3::cross(const Vector3& a, const Vector3& b) {

	vec[0] = (a.getY() * b.getZ()) - (a.getZ() * b.getY());
	vec[1] = (a.getZ() * b.getX()) - (a.getX() * b.getZ());
	vec[2] = (a.getX() * b.getY()) - (a.getY() * b.getX());

	return Vector3(vec[0], vec[1], vec[2]);
}

double Vector3::length() {
	return sqrt(vec[0] * vec[0] + vec[1] * vec[1] + vec[2] * vec[2]);
}

void Vector3::normalize() {
	double len = length();
	if (len <= 0.0) return;
	scale(1.0 / len);
}

void Vector3::print(std::string comment) {
	printf("%s (%.2f, %.2f, %.2f)\n", comment.c_str(), vec[0], vec[1], vec[2]);
}

double Vector3::angleFrom(Vector3& b) {
	return (acos(this->dot(b) / (length() * b.length()))) * 180.0 / 3.14159265358979323846;
}
