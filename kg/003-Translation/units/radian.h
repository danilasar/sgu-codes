#pragma once
struct Degree;
struct Radian {
	Radian(float v);
	operator Degree() const;
	operator float() const;
private:
	float value;
};
