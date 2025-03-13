#include "units/radian.h"
#include "vec.h"

namespace Math {
	template<size_t N, size_t M, typename T> requires std::is_arithmetic_v<T>
	struct Mat : Vec<N, Vec<M, T, true>> {
		using Vec<N, Vec<M, T, true>>::Vec;
		Mat<N, M, T>(float x) noexcept;
		static Mat<M, N, T> transpose(const Mat<N, M, T>& mat);
		template<size_t X, size_t Y>
		Mat<N, M, T>& operator*=(const Mat<X, Y, T>& r);
		template<size_t X, size_t Y>
		Mat<N, M, T>& operator*(const Mat<X, Y, T>& r);
	};
	
	typedef Mat<3, 3, float> Mat3;
	
	
	template<size_t N, size_t M, typename T> requires std::is_arithmetic_v<T>
	Mat<N, M, T>::Mat(float a) noexcept {
		for(int y = 0; y < N; ++y) {
			for(int x = 0; x < M; ++x) {
				if(y == x) {
					this->coordinates = a;
				} else {
					this->coordinates = 0;
				}
			}
		}
	}
	
	template<size_t N, size_t M, typename T> requires std::is_arithmetic_v<T>
	Mat<M, N, T> Mat<N, M, T>::transpose(const Mat<N, M, T>& mat) {
		auto clone = Mat<M, N, T>(0);
		for(int y = 0; y < N; ++y) {
			for(int x = 0; x < M; ++x) {
				clone->coordinates[x][y] = mat->coordinates[y][x];
			}
		}
		return *clone;
	}
	
	template<size_t N, size_t M, typename T> requires std::is_arithmetic_v<T>
	template<size_t X, size_t Y>
	Mat<N, M, T>& Mat<N, M, T>::operator*=(const Mat<X, Y, T>& r) {
		
	}
	
	template<size_t N, size_t M, typename T> requires std::is_arithmetic_v<T>
	template<size_t X, size_t Y>
	Mat<N, M, T>& Mat<N, M, T>::operator*(const Mat<X, Y, T>& r) {
	
	}
}
