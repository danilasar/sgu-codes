#include "matrix.hpp"
#include <cmath>
#include <cstdint>


Vec2::Vec2() {}
Vec2::Vec2(float a, float b) : x(a), y(b) {}
Vec2::Vec2(const Vec3& v) : x(v.x), y(v.y) {}

Vec3& Vec3::operator+=(const Vec3& v) {
	x += v.x;
	y += v.y;
	z += v.z;
	return *this;
}

Vec3 Vec3::operator+(const Vec3& v) const {
	return Vec3(*this) += v;
}

Vec3& Vec3::operator-=(const Vec3& v) {
	x -= v.x;
	y -= v.y;
	z -= v.z;
	return *this;
}

Vec3 Vec3::operator-(const Vec3& v) const {
	return Vec3(*this) -= v;
}

Vec3& Vec3::operator*=(const float n) {
	return *this *= Vec3(n, n, n);
}

Vec3 Vec3::operator*(const float n) const {
	return Vec3(*this) *= n;
}


Mat3& Mat3::operator+=(const Mat3 &m) {
	for(uint8_t i = 0; i < 3; ++i) {
		(*this)[i] += m[i];
	}
	return *this;
}

Mat3 Mat3::operator+(const Mat3 &m) const {
	return Mat3(*this) += m;
}

Mat3& Mat3::operator*=(const float n) {
	for(int i = 0; i < 3; ++i) {
		(*this)[i] *= n;
	}
	return *this;
}

Mat3 Mat3::operator*(const float n) const {
	return Mat3(*this) *= n;
}

inline Mat3 cross_M(const Vec3& p) {
	return Mat3(
		Vec3(0.f, -p.z, p.y),
		Vec3(p.z, 0.f, -p.x),
		Vec3(-p.y, p.x, 0.f)
	);
}

inline float length(const Vec3& p) {
	return std::sqrt(dot(p, p));
}


inline Vec3 norm(Vec3 p) {
	return normalize(Vec4(p, length(p)));
}
