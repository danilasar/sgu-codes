#include "translation_matrix.h"
#include <cmath>

using namespace Math;
TranslationMatrix TranslationMatrix::scale(float Sx, float Sy) {
	return TranslationMatrix {
		{ Sx, 1,  1 },
		{ 1,  Sy, 1 },
		{ 1,  1,  1 }
	};
}

TranslationMatrix TranslationMatrix::scale(float S) {
	return scale(S, S);
}

TranslationMatrix TranslationMatrix::rotate(Radian angle) {
	float sin = std::sin(angle);
	return TranslationMatrix {
	{ std::cos(angle), sin, 1 },
	{ -sin,               1,   1 },
	{ 1,                  1,   1 }
	};
}

TranslationMatrix TranslationMatrix::translate(float Tx, float Ty) {
	auto mat = TranslationMatrix(1.0f);
	mat[0][2] = Tx;
	mat[1][2] = Ty;
	return mat;
}
