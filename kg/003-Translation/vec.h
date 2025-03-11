
#pragma once
#include <cstdlib>
#include <algorithm>
#include <initializer_list>
#include <stdexcept>

template<size_t N, typename T>
struct Vec {
	T coordinates[N];
	Vec() = delete;
	Vec(const Vec<N, T>& v) = default;
	Vec(const Vec<N - 1, T>& v, T dimension) noexcept;
	template<typename... Args, typename = std::enable_if_t<(std::is_convertible_v<Args, T> && ...)>>
	Vec(Args&&... args) noexcept;
	Vec(std::initializer_list<T> coordinates);
	T operator[](const size_t i);
	friend Vec<N, T>& operator*=(Vec<N, T>& l, const Vec<N, float>& r);
	friend Vec<N, T> operator*(const Vec<N, T>& l, const Vec<N, float>& r);
};
template<typename T>
struct Vec<0, T> {
	Vec(const Vec& v, T dimension) noexcept = delete;
};

typedef Vec<2, float> Vec2;
typedef Vec<3, float> Vec3;
template<size_t N, size_t M, typename T>
using Mat = Vec<N, Vec<M, T>>;

template<size_t N, typename T>
Vec<N, T>::Vec(const Vec<N - 1, T>& v, T dimension) noexcept {
	std::copy(std::begin(v.coordinates), std::end(v.coordinates), std::begin(coordinates));
	coordinates[N - 1] = dimension;
}

template<size_t N, typename T>
template<typename... Args, typename>
Vec<N, T>::Vec(Args&&... args) noexcept {
	static_assert(sizeof...(Args) == N, "Число аргументов должно соответствовать размерности вектора");
	coordinates = { static_cast<T>(std::forward<Args>(args))... };
}

template<size_t N, typename T>
Vec<N, T>::Vec(std::initializer_list<T> list) {
	if(list.size() != N) {
		throw std::invalid_argument("Неверное число аргументов в списке инициализации");
	}
}

template<size_t N, typename T>
Vec<N, T>& operator*=(Vec<N, T>& l, const Vec<N, T>& r) {
	throw std::logic_error("Операция * не определена для этого типа");
}

template<size_t N, typename T>
Vec<N, T> operator*(const Vec<N, T>& l, const Vec<N, T>& r) {
	throw std::logic_error("Операция * не определена для этого типа");
}

template<size_t N>
Vec<N, float>& operator*=(Vec<N, float>& l, const Vec<N, float>& r) {
	for(int i = 0; i < N; ++i) {
		l.coordinates[i] *= r.coordinates[i];
	}
	return l;
}

template<size_t N>
Vec<N, float> operator*(const Vec<N, float>& l, const Vec<N, float>& r) {
	Vec<N, float> result(l);
	result *= r;
	return result;
}

template<size_t N, typename T>
T Vec<N, T>::operator[](const size_t i) {
	return ((T*)this)[i];
}

