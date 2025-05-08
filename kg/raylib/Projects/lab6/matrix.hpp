#pragma once

#include <stddef.h>
#include <raylib.h>

struct Vec2;
struct Vec3;
struct Vec4;
struct Mat2;
struct Mat3;
struct Mat4;

struct Vec2 {
    float x = 0;
    float y = 0;

    Vec2();
    Vec2(float a, float b);
	Vec2(const Vec3& v);

	Vec2& operator*=(const Vec2& v) {
		x *= v.x;
		y *= v.y;
		return *this;
	}

	Vec2 operator*(const Vec2& v) const {
		return Vec2(*this) *= v;
	}

    float &operator[](size_t i) {
        return (reinterpret_cast<float *>(this))[i];
    }
};

struct Vec3 {
    float x = 0;
    float y = 0;
    float z = 0;

    Vec3() {}

    Vec3(float a, float b, float c) : x(a), y(b), z(c) {}

    Vec3(Vec2 v, float c) : Vec3(v.x, v.y, c) {}

	Vec3& operator+=(const Vec3& v);
	Vec3 operator+(const Vec3& v) const;
	Vec3& operator-=(const Vec3& v);
	Vec3 operator-(const Vec3& v) const;
	Vec3& operator*=(const float n);
	Vec3 operator*(const float n) const;

    Vec3 &operator*=(const Vec3 &v) {
        this->x *= v.x;
        this->y *= v.y;
        this->z *= v.z;
        return *this;
    }

    const Vec3 operator*(const Vec3 &v) const {
        return Vec3(*this) *= v;
    }

    float &operator[](size_t i) {
        return (reinterpret_cast<float *>(this))[i];
    }

    const float &operator[](size_t i) const {
        return (reinterpret_cast<const float *>(this))[i];
    }
};

struct Vec4 {
    float x = 0;
    float y = 0;
    float z = 0;
    float w = 0;

    Vec4() {}

    Vec4(float a, float b, float c, float d) : x(a), y(b), z(c), w(d) {}

    Vec4(Vec3 v, float d) : Vec4(v.x, v.y, v.z, d) {}

    Vec4 &operator*=(const Vec4 &v) {
        this->x *= v.x;
        this->y *= v.y;
        this->z *= v.z;
        this->w *= v.w;
        return *this;
    }

    const Vec4 operator*(const Vec4 &v) const {
        return Vec4(*this) *= v;
    }

    float &operator[](size_t i) {
        return (reinterpret_cast<float *>(this))[i];
    }

    const float &operator[](size_t i) const {
        return (reinterpret_cast<const float *>(this))[i];
    }
};

inline float dot(const Vec4 &a, const Vec4 &b) {
    Vec4 tmp = a * b;
    return tmp.x + tmp.y + tmp.z + tmp.w;
}

inline float dot(const Vec3 &a, const Vec3 &b) {
    Vec3 tmp = a * b;
    return tmp.x + tmp.y + tmp.z;
}

inline float dot(const Vec2 &a, const Vec2 &b) {
	Vec2 tmp = a * b;
	return tmp.x + tmp.y;
}

struct Mat4 {
    Vec4 row1{};
    Vec4 row2{};
    Vec4 row3{};
    Vec4 row4{};

    Mat4() {}

    Mat4(Vec4 r1, Vec4 r2, Vec4 r3, Vec4 r4) : row1(r1), row2(r2), row3(r3), row4(r4) {}

    Mat4(float a) {
        row1 = Vec4(a, 0.f, 0.f, 0.f);
        row2 = Vec4(0.f, a, 0.f, 0.f);
        row3 = Vec4(0.f, 0.f, a, 0.f);
        row4 = Vec4(0.f, 0.f, 0.f, a);
    }

    Vec4 &operator[](size_t i) {
        return (reinterpret_cast<Vec4 *>(this))[i];
    }

    const Vec4 &operator[](size_t i) const {
        return (reinterpret_cast<const Vec4 *>(this))[i];
    }

    Mat4 &transpose() {
        Mat4 tmp(*this);
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                (*this)[i][j] = tmp[j][i];
            }
        }
        return *this;
    }

    const Vec4 operator*(const Vec4 &v) const {
        Vec4 res{};
        for (int i = 0; i < 4; ++i) {
            res[i] = dot((*this)[i], v);
        }
        return res;
    }

    Mat4 &operator*=(const Mat4 &m) {
        Mat4 A(*this);
        Mat4 B(m);
        B.transpose();
        for (int i = 0; i < 4; i++) {
            (*this)[i] = A * B[i];
        }
        return this->transpose();
    }

    const Mat4 operator*(const Mat4 &m) const {
        return Mat4(*this) *= m;
    }
};

struct Mat3 {
    Vec3 row1{};
    Vec3 row2{};
    Vec3 row3{};

    Mat3() {}

    Mat3(Vec3 r1, Vec3 r2, Vec3 r3) : row1(r1), row2(r2), row3(r3) {}

	Mat3(Mat4 m) : 
		row1({m.row1.x, m.row1.y, m.row1.z}),
		row2({m.row2.x, m.row2.y, m.row2.z}),
		row3({m.row3.x, m.row3.y, m.row3.z}) {};

    Mat3(float a) {
        row1 = Vec3(a, 0.f, 0.f);
        row2 = Vec3(0.f, a, 0.f);
        row3 = Vec3(0.f, 0.f, a);
    }

    Vec3 &operator[](size_t i) {
        return (reinterpret_cast<Vec3 *>(this))[i];
    }

    const Vec3 &operator[](size_t i) const {
        return (reinterpret_cast<const Vec3 *>(this))[i];
    }

    Mat3 &transpose() {
        Mat3 tmp(*this);
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                (*this)[i][j] = tmp[j][i];
            }
        }
        return *this;
    }

	Mat3& operator+=(const Mat3 &m);
	Mat3 operator+(const Mat3 &m) const;
	Mat3& operator*=(const float n);
	Mat3 operator*(const float n) const;

    const Vec3 operator*(const Vec3 &v) const {
        Vec3 res{};
        for (int i = 0; i < 3; ++i) {
            res[i] = dot((*this)[i], v);
        }
        return res;
    }

    Mat3 &operator*=(const Mat3 &m) {
        Mat3 A(*this);
        Mat3 B(m);
        B.transpose();
        for (int i = 0; i < 3; i++) {
            (*this)[i] = A * B[i];
        }
        return this->transpose();
    }

    const Mat3 operator*(const Mat3 &m) const {
        return Mat3(*this) *= m;
    }
};

struct Mat2 {
    Vec2 row1{};
    Vec2 row2{};

    Mat2() {}

    Mat2(Vec2 r1, Vec2 r2) : row1(r1), row2(r2) {}

    Mat2(float a) {
        row1 = Vec2(a, 0.f);
        row2 = Vec2(0.f, a);
    }

	Mat2(Mat3 m) : row1({m.row1.x, m.row1.y}), row2({m.row2.x, m.row2.y}) {}

    Vec2 &operator[](size_t i) {
        return (reinterpret_cast<Vec2 *>(this))[i];
    }

    const Vec2 &operator[](size_t i) const {
        return (reinterpret_cast<const Vec2 *>(this))[i];
    }

    Mat2 &transpose() {
        Mat2 tmp(*this);
        for (int i = 0; i < 2; ++i) {
            for (int j = 0; j < 2; ++j) {
                (*this)[i][j] = tmp[j][i];
            }
        }
        return *this;
    }

    const Vec2 operator*(const Vec2 &v) const {
        Vec2 res{};
        for (int i = 0; i < 2; ++i) {
            res[i] = dot((*this)[i], v);
        }
        return res;
    }

    Mat2 &operator*=(const Mat2 &m) {
        Mat2 A(*this);
        Mat2 B(m);
        B.transpose();
        for (int i = 0; i < 2; i++) {
            (*this)[i] = A * B[i];
        }
        return this->transpose();
    }

    const Mat2 operator*(const Mat2 &m) const {
        return Mat2(*this) *= m;
    }
};

inline Vec2 normalize(const Vec3 &v) {
    return Vec2(v.x / v.z, v.y / v.z);
}

inline Vec3 normalize(const Vec4 &v) {
    return Vec3(v.x / v.w, v.y / v.w, v.z / v.w);
}

inline Mat3 cross_M(const Vec3& p);
inline float length(const Vec3& p);
inline Vec3 norm(Vec3 p);
