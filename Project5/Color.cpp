#include "Color.h"


Color::~Color() {
}

Color operator+ (const Color& lhs, const Color& rhs) {
	return Color(lhs.r + rhs.r, lhs.g + rhs.g, lhs.b + rhs.b);
}
Color operator* (const Color& lhs, const Color& rhs) {
	return Color(lhs.r * rhs.r, lhs.g * rhs.g, lhs.b * rhs.b);
}
Color operator/ (const Color& lhs, const Color& rhs) {
	return Color(lhs.r / rhs.r, lhs.g / rhs.g, lhs.b / rhs.b);
}


Color& Color::operator=(const Color& rhs) {
	this->r = rhs.r;
	this->g = rhs.g;
	this->b = rhs.b;
	return *this;
}
Color& Color::operator+=(const Color& rhs) {
	*this = *this + rhs;
	return *this;
}
Color& Color::operator*=(const Color& rhs) {
	*this = *this * rhs;
	return *this;
}
Color& Color::operator/=(const Color& rhs) {
	*this = *this / rhs;
	return *this;
}
