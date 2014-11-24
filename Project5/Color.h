#pragma once

using namespace std;

class Color {
private:
	float r, g, b;
public:
	Color(float r0 = 0.0, float g0 = 0.0, float b0 = 0.0) : r(r0), g(g0), b(b0) {}
	~Color();

	void setR(float r) { this->r = r; }
	void setG(float g) { this->g = g; }
	void setB(float b) { this->b = b; }

	float getR() const { return r; }
	float getG() const { return g; }
	float getB() const { return b; }

	friend Color operator+(const Color& lhs, const Color& rhs);
	friend Color operator*(const Color& lhs, const Color& r);
	friend Color operator/(const Color& lhs, const Color& r);

	Color& operator= (const Color& rhs);
	Color& operator+= (const Color& rhs);
	Color& operator*= (const Color& rhs);
	Color& operator/= (const Color& rhs);

	friend Color operator-(float s, const Color& c) { return Color(s - c.r, s - c.g, s - c.b); }
	friend Color operator-(const Color& c, float s) { return Color(c.r - s, c.g - s, c.b - s); }
	friend Color operator*(const Color &c, float s) { return Color(c.r *s, c.g *s, c.b *s); }
	friend Color operator*(float s, const Color &c) { return Color(c.r *s, c.g *s, c.b *s); }
	friend Color operator/ (const Color &c, float s) { if (s != 0.0) return Color(c.r / s, c.g / s, c.b / s); return Color(0, 0, 0); }
	Color& operator*= (float s) { *this = *this * s; return *this; }
	Color& operator/= (float s) { *this = *this / s; return *this; }
};

