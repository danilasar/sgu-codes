#include "degree.h"
#include "radian.h"
#include <math.h>
using namespace Math;
Radian::Radian(float v) : value(v) {}
Degree::operator Radian() const {
	return Radian(value * (M_PI / 180));
}
Degree::operator float() const {
	return value;
}
