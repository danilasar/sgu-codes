
#pragma once
#include <cstdlib>
#include <algorithm>
#include <initializer_list>
#include <qpoint.h>
#include <stdexcept>
#include <iterator>
#include <numeric>
#include <QPointF>

namespace Math {
	template<size_t N, typename T>
	struct VecBase {
		struct EmptyType {};
		using T1 = typename std::conditional_t<N >= 1, T, EmptyType>;
		using T2 = typename std::conditional_t<N >= 2, T, EmptyType>;
		using T3 = typename std::conditional_t<N >= 3, T, EmptyType>;
		using T4 = typename std::conditional_t<N >= 4, T, EmptyType>;
		// WARN: неопределённое поведение, может не работать в некоторых компиляторах
		union {
			struct {
				T1 x; T2 y; T3 z; T4 w;
			};
			std::array<T, N> coordinates;
			//T coordinates[N];
		};
	
		VecBase() noexcept;
		template<typename... Args, typename = std::enable_if_t<(std::is_convertible_v<Args, T> && ...)>>
		VecBase(Args&&... args) noexcept((std::is_nothrow_constructible_v<T, Args> && ...));
		VecBase(const VecBase<N, T>& v) = default;
		explicit VecBase(const std::array<T, N>& arr);
		explicit VecBase(std::array<T, N>::iterator begin, std::array<T, N>::iterator end);
		VecBase(const VecBase<N - 1, T>& v, T dimension) noexcept;
		VecBase(std::initializer_list<T> coordinates);
	
		T& operator[](const size_t i);
		const T& operator[](const size_t i) const;
	};
	
	template<size_t N, typename T, bool = std::is_arithmetic_v<T>>
	struct Vec : VecBase<N, T> {
		using VecBase<N, T>::VecBase;
		//Vec() = delete;
	};
	
	
	template<size_t N, typename T>
	struct Vec<N, T, true> : VecBase<N, T> {
		using VecBase<N, T>::VecBase;

		T dot_product(const Vec<N, T>& r);
		static T dot_product(const Vec<N, T>& l, const Vec<N, T>& r);
	
		Vec<N, T>& operator*=(const Vec<N, T>& r);
		Vec<N, T> operator*(const Vec<N, T>& r) const;
	
		Vec<N - 1, T> normalize();
	
		//template<typename _z = std::enable_if_t<N == 2, void*>>
		operator QPointF() const;
	};

	
	typedef Vec<3, float> Vec3;
	typedef Vec<2, float> Vec2;

	template<size_t N, typename T>
	VecBase<N, T>::VecBase() noexcept {

	}

	template<size_t N, typename T>
	VecBase<N, T>::VecBase(const VecBase<N - 1, T>& v, T dimension) noexcept {
		std::copy(std::begin(v.coordinates), std::end(v.coordinates), std::begin(coordinates));
		coordinates[N - 1] = dimension;
	}

	template<size_t N, typename T>
	VecBase<N, T>::VecBase(std::array<T, N>::iterator begin, std::array<T, N>::iterator end) {	
		std::copy(begin, end, std::begin(coordinates));
	}
	
	template<size_t N, typename T>
	template<typename... Args, typename>
	VecBase<N, T>::VecBase(Args&&... args)
		noexcept((std::is_nothrow_constructible_v<T, Args> && ...))
		: coordinates{ static_cast<T>(std::forward<Args>(args))... }
	{
		static_assert(sizeof...(Args) == N, "Число аргументов должно соответствовать размерности вектора");
	}
	
	template<size_t N, typename T>
	VecBase<N,T>::VecBase(const std::array<T, N>& arr) {
		std::copy(arr.cbegin(), arr.cend(), coordinates.begin());
	}
	
	template<size_t N, typename T>
	VecBase<N, T>::VecBase(std::initializer_list<T> list) {
		if(list.size() != N) {
			throw std::invalid_argument("Неверное число аргументов в списке инициализации");
		}
		for(size_t i = 0; i < list.size(); ++i) {
			coordinates[i] = *(list.begin() + i);
		}
	}
	
	template<size_t N, typename T>
	T& VecBase<N, T>::operator[](const size_t i) {
		return ((T*)this)[i];
	}

	template<size_t N, typename T>
	const T& VecBase<N, T>::operator[](const size_t i) const {
		return ((T*)this)[i];
	}
	
	template<size_t N, typename T>
	Vec<N, T>& Vec<N, T, true>::operator*=(const Vec<N, T>& r) {
		for(int i = 0; i < N; ++i) {
			this->coordinates[i] *= r.coordinates[i];
		}
		return *this;
	}
	
	template<size_t N, typename T>
	Vec<N, T> Vec<N, T, true>::operator*(const Vec<N, T>& r) const {
		Vec<N, T> result(*this);
		result *= r;
		return result;
	}
	
	template<size_t N, typename T>
	Vec<N, T, true>::operator QPointF() const {
		static_assert(N == 2, "Поддерживаются только двумерные векторы");
		return QPointF(this->x, this->y);
	}
	
	template<size_t N, typename T>
	T Vec<N, T, true>::dot_product(const Vec<N, T>& r) {
		return dot_product(*this, r);
	}
	
	template<size_t N, typename T>
	T Vec<N, T, true>::dot_product(const Vec<N, T>& l, const Vec<N, T>& r) {
		auto tmp = l * r;
		return std::accumulate(begin(tmp.coordinates), end(tmp.coordinates), 0.f);
	}
	
	template<size_t N, typename T>
	Vec<N - 1, T> Vec<N, T, true>::normalize() {
		Vec<N - 1, T> vec(this->coordinates.begin(), this->coordinates.end() - 1);
		for(T& i : vec.coordinates) {
			i /= this->coordinates[N - 1];
		}
		return vec;
	}
}
