#include "matrix.h"
namespace Math {
	struct TranslationMatrix : Mat3 {
		using Mat3::Mat;
		TranslationMatrix(const TranslationMatrix& old) = default;
		TranslationMatrix(const Mat3& m) : Mat3(m) {}
		static TranslationMatrix scale(float Sx, float Sy);
		static TranslationMatrix scale(float S);
		static TranslationMatrix rotate(Radian angle);
		static TranslationMatrix translate(float Tx, float Ty);
	};
}

