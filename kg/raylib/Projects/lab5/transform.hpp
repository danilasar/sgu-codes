#pragma once

#include "matrix.hpp"

#include <math.h>

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
