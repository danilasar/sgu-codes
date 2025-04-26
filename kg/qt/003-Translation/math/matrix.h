#include "units/radian.h"
#include "vec.h"

namespace Math {
	template<size_t N, size_t M, typename T> requires std::is_arithmetic_v<T>
	struct Mat : Vec<N, Vec<M, T, true>> {
		using Vec<N, Vec<M, T, true>>::Vec;
		//Mat() = delete;
		Mat(const Mat& old) = default;
		template<typename Z>
		Mat(Z x) noexcept(std::is_nothrow_constructible_v<T, Z>);
		virtual ~Mat() {}
		static Mat<M, N, T> transpose(const Mat<N, M, T>& mat);
		template<size_t X, size_t Y>
		Mat<N, Y, T> operator*(const Mat<X, Y, T>& r) const;
		Vec<M, T> operator*(const Vec<M, T>& r) const;
	};
	
	typedef Mat<3, 3, float> Mat3;
	
	
	template<size_t N, size_t M, typename T> requires std::is_arithmetic_v<T>
	template<typename Z>
	Mat<N, M, T>::Mat(Z a) noexcept(std::is_nothrow_constructible_v<T, Z>) {
		for(int y = 0; y < N; ++y) {
			for(int x = 0; x < M; ++x) {
				if(y == x) {
					this->coordinates[y][x] = a;
				} else {
					this->coordinates[y][x] = 0;
				}
			}
		}
	}
	
	template<size_t N, size_t M, typename T> requires std::is_arithmetic_v<T>
	Mat<M, N, T> Mat<N, M, T>::transpose(const Mat<N, M, T>& mat) {
		auto clone = Mat<M, N, T>(0);
		for(int y = 0; y < N; ++y) {
			for(int x = 0; x < M; ++x) {
				clone.coordinates[x][y] = mat.coordinates[y][x];
			}
		}
		return clone;
	}
	
	template<size_t N, size_t M, typename T> requires std::is_arithmetic_v<T>
	template<size_t X, size_t Y>
	Mat<N, Y, T> Mat<N, M, T>::operator*(const Mat<X, Y, T>& r) const {
		Mat<N, Y, T> result(*this);
		auto R = r.transpose(r);
		for(size_t i = 0; i < this->coordinates.size(); ++i) {
			result[i] = (*this) * R[i];
		}
		return Mat<N, Y, T>::transpose(result);
	}


	template<size_t N, size_t M, typename T> requires std::is_arithmetic_v<T>
	Vec<M, T> Mat<N, M, T>::operator*(const Vec<M, T>& r) const {
		Vec<M, T> result(r);
		for(size_t i = 0; i < N; ++i) {
			const Vec<M, T> &c = this->coordinates[i];
			result[i] = Vec<M, T>::dot_product(c, r);
		}
		return result;
	}
}
