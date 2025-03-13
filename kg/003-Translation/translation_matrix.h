#include "matrix.h"
namespace Math {
	struct TranslationMatrix : Mat<3, 3, float> {
		using Mat3::Mat;
		static TranslationMatrix scale(float Sx, float Sy);
		static TranslationMatrix scale(float S);
		static TranslationMatrix rotate(Radian angle);
		static TranslationMatrix translate(float Tx, float Ty);
	};
}

