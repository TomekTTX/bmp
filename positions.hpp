#pragma once
#include <array>
#include <cmath>

inline int32_t rnd(double d) { return static_cast<int32_t>(std::round(d)); }

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

	std::pair<T, T> unpack() const { return std::make_pair(x, y); }

	Pos rotated(double angle) const {
		return rotated(sin(angle), cos(angle));
	}
	Pos rotated(double sina, double cosa) const {
		return Pos(Pos<double>{ x * cosa + y * sina, -x * sina + y * cosa });
	}
	Pos rotated(double angle, Pos axis) const {
		return (*this - axis).rotated(sin(angle), cos(angle)) + axis;
	}
	Pos rotated(double sina, double cosa, Pos axis) const {
		return (*this - axis).rotated(sina, cosa) + axis;
	}
	template <typename T>
	Pos<T> round() const {
		return { 
			static_cast<T>(rnd(x)),
			static_cast<T>(rnd(y)),
		};
	}
	template <typename T>
	operator Pos<T>() const {
		return { static_cast<T>(x),	static_cast<T>(y), };
	}

	double distance2(const Pos &other) const {
		const T dx = std::max(x, other.x) - std::min(x, other.x);
		const T dy = std::max(y, other.y) - std::min(y, other.y);
		return dx * dx + dy * dy;
	}

	double dist(const Pos &other) const {
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
