
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
	Vec(const Vec<N - 1, T>& v, float dimension) noexcept;
	template<typename... Args, typename = std::enable_if_t<(std::is_convertible_v<Args, T> && ...)>>
	Vec(Args&&... args) noexcept;
	Vec(std::initializer_list<float> coordinates);
	Vec<N, T>& operator*=(const Vec<N, T>& r);
	Vec<N, T> operator*(const Vec<N, T>& r);
	float operator[](const size_t i);
};
template<typename T>
struct Vec<0, T> {
	Vec(const Vec& v, float dimension) noexcept = delete;
};

typedef Vec<2, float> Vec2;
typedef Vec<3, float> Vec3;

template<size_t N, typename T>
Vec<N, T>::Vec(const Vec<N - 1, T>& v, float dimension) noexcept {
	std::copy(std::begin(v.coordinates), std::end(v.coordinates), std::begin(coordinates));
	coordinates[N - 1] = dimension;
}

template<size_t N, typename T>
template<typename... Args, typename>
Vec<N, T>::Vec(Args&&... args) noexcept {
	static_assert(sizeof...(Args) == N, "Число аргументов должно соответствовать размерности вектора");
	coordinates = { static_cast<float>(std::forward<Args>(args))... };
}

template<size_t N, typename T>
Vec<N, T>::Vec(std::initializer_list<float> list) {
	if(list.size() != N) {
		throw std::invalid_argument("Неверное число аргументов в списке инициализации");
	}
}

template<size_t N, typename T>
Vec<N, T>& Vec<N, T>::operator*=(const Vec<N, T>& r) {
	for(int i = 0; i < N; ++i) {
		coordinates[i] *= r.coordinates[i];
	}
	return &this;
}


template<size_t N, typename T>
Vec<N, T> Vec<N, T>::operator*(const Vec<N, T>& r) {
	Vec<N, T> result(this);
	result *= r;
	return result;
}

template<size_t N, typename T>
float Vec<N, T>::operator[](const size_t i) {
	return ((T*)this)[i];
}

