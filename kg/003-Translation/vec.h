
#pragma once
#include <cstdlib>
#include <algorithm>
#include <initializer_list>
#include <stdexcept>

template<size_t N>
struct Vec {
	float coordinates[N];
	Vec() = delete;
	Vec(const Vec<N>& v) = default;
	Vec(const Vec<N - 1>& v, float dimension) noexcept;
	template<typename... Args, typename = std::enable_if_t<(std::is_convertible_v<Args, float> && ...)>>
	Vec(Args&&... args) noexcept;
	Vec(std::initializer_list<float> coordinates);
	Vec<N>& operator*=(const Vec<N>& r);
	Vec<N> operator*(const Vec<N>& r);
	float operator[](const size_t i);
};
template<>
struct Vec<0> {
	Vec(const Vec& v, float dimension) noexcept = delete;
};

typedef Vec<2> Vec2;
typedef Vec<3> Vec3;

template<size_t N>
Vec<N>::Vec(const Vec<N - 1>& v, float dimension) noexcept {
	std::copy(std::begin(v.coordinates), std::end(v.coordinates), std::begin(coordinates));
	coordinates[N - 1] = dimension;
}

template<size_t N>
template<typename... Args, typename>
Vec<N>::Vec(Args&&... args) noexcept {
	static_assert(sizeof...(Args) == N, "Число аргументов должно соответствовать размерности вектора");
	coordinates = { static_cast<float>(std::forward<Args>(args))... };
}

template<size_t N>
Vec<N>::Vec(std::initializer_list<float> list) {
	if(list.size() != N) {
		throw std::invalid_argument("Неверное число аргументов в списке инициализации");
	}
}

template<size_t N>
Vec<N>& Vec<N>::operator*=(const Vec<N>& r) {
	for(int i = 0; i < N; ++i) {
		coordinates[i] *= r.coordinates[i];
	}
	return &this;
}


template<size_t N>
Vec<N> Vec<N>::operator*(const Vec<N>& r) {
	Vec<N> result(this);
	result *= r;
	return result;
}

template<size_t N>
float Vec<N>::operator[](const size_t i) {
	return (float)(*(this + (i * sizeof float)));
}

