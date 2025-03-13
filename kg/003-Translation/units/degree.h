#pragma once
struct Radian;
struct Degree {
	Degree(float v);
	operator Radian() const;
	operator float() const;
private:
	float value;
};
