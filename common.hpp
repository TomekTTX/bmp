#pragma once
#include <ctime>
#include <random>
#include "positions.hpp"

constexpr inline static double tau = 6.28318530718;
constexpr inline static double pi = 3.14159265359;

constexpr inline int8_t sgn(int32_t x) { return (x > 0) - (x < 0); }
constexpr inline int32_t ipow(int32_t base, uint8_t exp) {
	int32_t ret = 1;

	while (exp) {
		if (exp & 1)
			ret *= base;
		base *= base;
		exp >>= 1;
	}

	return ret;
}

static struct {
	std::minstd_rand engine{ static_cast<uint32_t>(time(nullptr)) };
	std::uniform_int_distribution<uint32_t> distint{ 0U, ~0U };
	std::uniform_real_distribution<double> distreal{ 0U, 1 };

	inline double real() { return distreal(engine); }
	inline uint32_t integer() { return distint(engine); }
	inline uint32_t integer(uint32_t limit) {
		return static_cast<uint32_t>(distreal(engine) * limit);
	}
	inline uint32_t integer(uint32_t inf, uint32_t sup) {
		return std::uniform_int_distribution<uint32_t>(inf, sup)(engine);
	}
} rng;
