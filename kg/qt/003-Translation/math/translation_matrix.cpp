#include "translation_matrix.h"
#include <cmath>

using namespace Math;
TranslationMatrix TranslationMatrix::scale(float Sx, float Sy) {
	return TranslationMatrix {
		{ Sx, 0,  0 },
		{ 0,  Sy, 0 },
		{ 0,  0,  1 }
	};
}

TranslationMatrix TranslationMatrix::scale(float S) {
	return scale(S, S);
}

#include <iostream>
TranslationMatrix TranslationMatrix::rotate(Radian angle) {
	float a = angle;
	float sin = std::sin(angle);
	float cos = std::cos(angle);
	//sin = 0;
	//cos = 0.8;
	std::cout << sin << std::endl << cos << std::endl;
	return TranslationMatrix {
		{ cos,  sin, 0. },
		{ -sin, cos, 0. },
		{ 0.,   0.,  1. }
	};
}

TranslationMatrix TranslationMatrix::translate(float Tx, float Ty) {
	return TranslationMatrix {
		{ 1,  0,  Tx },
		{ 0,  1,  Ty },
		{ 0,  0,  1 }
	};
	auto mat = TranslationMatrix(1.0f);
	mat[0][2] = Tx;
	mat[1][2] = Ty;
	return mat;
}
