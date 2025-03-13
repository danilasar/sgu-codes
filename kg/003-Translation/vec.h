
#pragma once
#include <cstdlib>
#include <algorithm>
#include <initializer_list>
#include <stdexcept>
#include <iterator>
#include <numeric>


template<size_t N, typename T>
struct VecBase {
	T coordinates[N];

	VecBase() = delete;
	template<typename... Args, typename = std::enable_if_t<(std::is_convertible_v<Args, T> && ...)>>
	VecBase(Args&&... args) noexcept((std::is_nothrow_constructible_v<T, Args> && ...));
	VecBase(const VecBase<N, T>& v) = default;
	VecBase(const VecBase<N - 1, T>& v, T dimension) noexcept;
	VecBase(std::initializer_list<T> coordinates);

	T& operator[](const size_t i);
};

template<size_t N, typename T, bool = std::is_arithmetic_v<T>>
struct Vec : VecBase<N, T> {
	using VecBase<N, T>::VecBase;
};


template<size_t N, typename T>
struct Vec<N, T, true> : VecBase<N, T> {
	using VecBase<N, T>::VecBase;

	T dot_product(const Vec<N, T>& r);
	static T dot_product(const Vec<N, T>& l, const Vec<N, T>& r);

	Vec<N, T>& operator*=(const Vec<N, T>& r);
	friend Vec<N, T> operator*(const Vec<N, T>& l, const Vec<N, T>& r);

	Vec<N - 1, T> normalize();
};



typedef Vec<2, float> Vec2;
typedef Vec<3, float> Vec3;

template<size_t N, typename T>
VecBase<N, T>::VecBase(const VecBase<N - 1, T>& v, T dimension) noexcept {
	std::copy(std::begin(v.coordinates), std::end(v.coordinates), std::begin(coordinates));
	coordinates[N - 1] = dimension;
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
VecBase<N, T>::VecBase(std::initializer_list<T> list) {
	/*if(list.size() != N) {
		throw std::invalid_argument("Неверное число аргументов в списке инициализации");
	}*/
	static_assert(sizeof list == N, "Неверное число аргументов в списке инициализации");
	// TODO:
}

template<size_t N, typename T>
T& VecBase<N, T>::operator[](const size_t i) {
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
Vec<N, T, true> operator*(const Vec<N, T, true>& l, const Vec<N, T, true>& r) {
	Vec<N, float> result(l);
	result *= r;
	return result;
}


template<size_t N, typename T>
T Vec<N, T, true>::dot_product(const Vec<N, T>& r) {
	return dot_product(*this, r);
}

template<size_t N, typename T>
T Vec<N, T, true>::dot_product(const Vec<N, T>& l, const Vec<N, T>& r) {
	auto tmp = l * r;
	return std::accumulate(begin(tmp.coordinates), end(tmp.coordinates), 0);
}

template<size_t N, typename T>
Vec<N - 1, T> Vec<N, T, true>::normalize() {
	std::initializer_list<T> init(std::begin(this->coordinates), std::end(this->coordinates) - 1);
	Vec<N - 1, T> vec(init);
	for(T& i : vec) {
		i /= this->coordinates[N - 1];
	}
	return vec;
}
