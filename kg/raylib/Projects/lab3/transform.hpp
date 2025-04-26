#pragma once

#include "matrix.hpp"

#include <math.h>

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

inline Mat3 scale(float S) {
    return scale(S, S);
}

inline Mat3 rotate(float theta) {
    Mat3 res = Mat3(1.f);
    res[0][0] = static_cast<float>(cos(theta));
    res[1][1] = res[0][0];
    res[0][1] = static_cast<float>(-sin(theta));
    res[1][0] = -res[0][1];
    return res;
}

inline Mat3 mirrorX() {
    Mat3 res(1.f);
    res[1][1] = -1;
    return res;
}

inline Mat3 mirrorY() {
    Mat3 res(1.f);
    res[0][0] = -1;
    return res;
}
