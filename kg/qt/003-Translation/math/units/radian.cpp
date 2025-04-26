#include "radian.h"
#include "degree.h"
#include <math.h>

using namespace Math;

Radian::Radian(float v) : value(v) {}
Radian::operator Degree() const {
	return Degree(value * (180 / M_PI));
}
Radian::operator float() const {
	return value;
}
