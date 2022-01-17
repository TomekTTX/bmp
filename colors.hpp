#pragma once
#include "byte.hpp"

namespace bmp {
	struct Color {
		ubyte_t r, g, b;

		inline constexpr Color() = default;
		inline constexpr Color(ubyte_t r, ubyte_t g, ubyte_t b) : r(r), g(g), b(b) {}
		inline constexpr Color(uint32_t r, uint32_t g, uint32_t b) : r(r), g(g), b(b) {}
		inline constexpr Color(uint32_t rgb) :
			r((rgb >> 16) & 0xFF), g((rgb >> 8) & 0xFF), b((rgb) & 0xFF) {}

		inline bool operator==(const Color &other) const {
			return r == other.r && g == other.g && b == other.b;
		}
	};

	namespace colors {
		constexpr static Color
			black = 0x000000,
			red = 0xFF0000,
			green = 0x00FF00,
			blue = 0x0000FF,
			cyan = 0x00FFFF,
			magenta = 0xFF00FF,
			yellow = 0xFFFF00,
			white = 0xFFFFFF,
			orange = 0xFF9911,
			pink = 0xFFAABB,
			purple = 0x8800FF,
			brown = 0x774411,
			gray = 0x666666,
			silver = 0xAAAAAA,
			maroon = 0x880000,
			teal = 0x225566;
	}
}
