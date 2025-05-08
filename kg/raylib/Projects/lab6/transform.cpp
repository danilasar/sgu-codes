#include "transform.hpp"
#include "matrix.hpp"
#include <stdexcept>

Mat4 rotate(float theta, Vec3 n) {
	n = norm(n);

	const float cos_t = std::cos(theta);
	const float sin_t = std::sin(theta);
	const float one_minus_cos_t = 1.0f - cos_t;

	const float R00 = cos_t + one_minus_cos_t * n.x * n.x;
	const float R01 = one_minus_cos_t * n.x * n.y - sin_t * n.z;
	const float R02 = one_minus_cos_t * n.x * n.z + sin_t * n.y;

	const float R10 = one_minus_cos_t * n.y * n.x + sin_t * n.z;
	const float R11 = cos_t + one_minus_cos_t * n.y * n.y;
	const float R12 = one_minus_cos_t * n.y * n.z - sin_t * n.x;

	const float R20 = one_minus_cos_t * n.z * n.x - sin_t * n.y;
	const float R21 = one_minus_cos_t * n.z * n.y + sin_t * n.x;
	const float R22 = cos_t + one_minus_cos_t * n.z * n.z;

	Mat4 result = Mat4(
		{R00, R01, R02, 0.0f},
		{R10, R11, R12, 0.0f},
		{R20, R21, R22, 0.0f},
		{0.0f, 0.0f, 0.0f, 1.0f}
	);

	return result;
}

Mat4 look_at(Vec3 S, Vec3 P, Vec3 up) {
    Vec3 direction = {S[0] - P[0], S[1] - P[1], S[2] - P[2]};
    Vec3 e3 = norm(direction);

    Vec3 u = norm(up);
    Vec3 e1 = cross(u, e3);
    float e1_len = length(e1);

    constexpr float eps = 1e-6f;
    if (e1_len < eps) {
        u = norm(Vec3{0, 1, 0});
        e1 = cross(u, e3);
        e1_len = length(e1);
        if (e1_len < eps) {
            u = norm(Vec3{0, 0, 1});
            e1 = cross(u, e3);
            e1_len = length(e1);
            if (e1_len < eps) 
                throw std::invalid_argument("Invalid up vector");
        }
    }
    e1 = norm(e1);

    Vec3 e2 = norm(cross(e3, e1));

    Mat4 R = Mat4(
        {e1[0], e1[1], e1[2], 0},
        {e2[0], e2[1], e2[2], 0},
        {e3[0], e3[1], e3[2], 0},
        {0,     0,     0,     1}
    );

    Mat4 T = translate(-S[0], -S[1], -S[2]);

    return R * T;
}
