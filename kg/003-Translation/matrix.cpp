#include "matrix.h"

Vec2::Vec2(float x, float y) noexcept: x(x), y(y) {}

Vec3::Vec3(float x, float y, float z) noexcept: x(x), y(y), z(z) {}

Vec3::Vec3(const Vec2& v, float z) noexcept: Vec3(v.x, v.y, z) {}
