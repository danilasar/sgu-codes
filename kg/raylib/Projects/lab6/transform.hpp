#pragma once

#include "matrix.hpp"
#include <cmath>

inline Mat4 translate(float Tx, float Ty, float Tz) {
    Mat4 res = Mat4(1.f);
    res[0][3] = Tx;
    res[1][3] = Ty;
    res[2][3] = Tz;
    return res;
}

inline Mat4 scale(float Sx, float Sy, float Sz) {
    Mat4 res = Mat4(0.f);
    res[0][0] = Sx;
    res[1][1] = Sy;
    res[2][2] = Sz;
	res[3][3] = 1;
    return res;
}

inline Mat4 scale(float S) {
    return scale(S, S, S);
}

inline Mat4 rotateX(float theta) {
    Mat4 res = Mat4(1.f);
    res[1][1] = static_cast<float>(cos(theta));
    res[2][2] = res[1][1];
    res[1][2] = static_cast<float>(-sin(theta));
    res[2][1] = -res[1][2];
    return res;
}

inline Mat4 rotateY(float theta) {
    Mat4 res = Mat4(1.f);
    res[0][0] = static_cast<float>(cos(theta));
    res[2][2] = res[0][0];
    res[2][0] = static_cast<float>(-sin(theta));
    res[0][2] = -res[2][0];
    return res;
}

inline Mat4 rotateZ(float theta) {
    Mat4 res = Mat4(1.f);
    res[0][0] = static_cast<float>(cos(theta));
    res[1][1] = res[0][0];
    res[0][1] = static_cast<float>(-sin(theta));
    res[1][0] = -res[0][1];
    return res;
}

inline Mat4 mirrorX() {
    Mat4 res(1.f);
    res[1][1] = -1;
    res[2][2] = -1;
    return res;
}

inline Mat4 mirrorY() {
    Mat4 res(1.f);
    res[0][0] = -1;
    res[2][2] = -1;
    return res;
}

inline Mat4 mirrorZ() {
    Mat4 res(1.f);
    res[0][0] = -1;
    res[1][1] = -1;
    return res;
}


inline Mat3 translate(float Tx, float Ty) {

	Mat3 res = Mat3(1.f);
	res[0][2] = Tx;
	res[1][2] = Ty;
	return res;
}

inline Mat3 scale(float Sx, float Sy) {
	Mat3 res = Mat3(1.f);
	res[0][0] = Sx;
	res[1][1] = Sy;
	return res;
}

Mat4 rotate(float theta, Vec3 n);

inline Mat4 rotateP(float theta, Vec3 n, Vec3 P) {
	return translate(P.x, P.y, P.z) *
		(rotate(theta, n) * translate(-P.x, -P.y, -P.z));
}

Mat4 look_at(Vec3 S, Vec3 P, Vec3 u);

inline Mat4 ortho(float l, float r, float b, float t, float zn, float zf) {
	return Mat4(Vec4(2.f / (r - l), 0.f, 0.f, -(r + l) / (r - l)),
		Vec4(0.f, 2.f / (t - b), 0.f, -(t + b) / (t - b)),
		Vec4(0.f, 0.f, -2 / (zf - zn), -(zf + zn) / (zf - zn)),
		Vec4(0.f, 0.f, 0.f, 1.f));
}
inline Mat4 frustum(float l, float r, float b, float t, float n, float f) {
    return Mat4(
        Vec4(2 * n / (r - l), 0.f,            (r + l) / (r - l),  0.f),
        Vec4(0.f,            2 * n / (t - b), (t + b) / (t - b),  0.f),
        Vec4(0.f,            0.f,            -(f + n) / (f - n), -2 * f * n / (f - n)),
        Vec4(0.f,            0.f,            -1.f,               0.f)
    );
}

inline Mat4 perspective(float fovy, float aspect, float n, float f) {
    const float t = n * std::tan(fovy / 2.f);
    const float b = -t;
    const float r = t * aspect;
    const float l = -r;
    
    return frustum(l, r, b, t, n, f);
}
