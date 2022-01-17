#pragma once
#include <array>
#include <cmath>

template <typename T>
struct Pos {
	T x, y;

	constexpr Pos() : x(0), y(0) {}
	constexpr Pos(T x, T y) : x(x), y(y) {}
	constexpr Pos(std::initializer_list<T> params) :
		x(params.begin()[0]), y(params.begin()[1]) {}

	bool operator==(const Pos &other) const { return x == other.x && y == other.y; }
	bool operator!=(const Pos &other) const { return !(*this == other); }
	Pos operator+(const Pos &other) const { return { x + other.x, y + other.y }; }
	Pos operator-() const { return { -x,-y }; }
	Pos operator-(const Pos &other) const { return { x - other.x, y - other.y }; }
	Pos operator*(T mult) const { return { x * mult, y * mult }; }
	Pos operator/(T mult) const { return { x / mult, y / mult }; }
	Pos operator+=(const Pos &other) {
		x += other.x;
		y += other.y;
		return *this;
	}
	Pos operator-=(const Pos &other) {
		x -= other.x;
		y -= other.y;
		return *this;
	}
	Pos operator*=(T mult) {
		x *= mult;
		y *= mult;
		return *this;
	}
	Pos operator/=(T mult) {
		x /= mult;
		y /= mult;
		return *this;
	}

	Pos rotated(double angle) const {
		return rotated(sin(angle), cos(angle));
	}
	Pos rotated(double sina, double cosa) const {
		return { x * cosa + y * sina, -x * sina + y * cosa };
	}

	double distance2(const Pos &other) const {
		const T dx = std::max(x, other.x) - std::min(x, other.x);
		const T dy = std::max(y, other.y) - std::min(y, other.y);
		return dx * dx + dy * dy;
	}

	double distance(const Pos &other) const {
		return std::sqrt(distance2(other));
	}

	std::array<Pos, 4> neighbors() const {
		return { {
			{x - 1, y},
			{x + 1, y},
			{x, y - 1},
			{x, y + 1},
		} };
	}
};

namespace std {
	template <typename T>
	struct hash<Pos<T>> {
		std::size_t operator()(const Pos<T> &xy) const {
			return std::hash<T>()(xy.x) ^ (std::hash<T>()(xy.y) << 1);
		}
	};
}
