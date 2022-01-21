#pragma once
#include "byte.hpp"
#include "common.hpp"
#include <vector>

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

	class ColorProvider {
	public:
		constexpr static uint8_t degree_cnt = 15;

		virtual Color get(int32_t x, int32_t y) const = 0;
	protected:
		static bool getShade(int32_t x, int32_t y, uint8_t degree);
	};

	class FlatColor : public ColorProvider {
	private:
		Color color;
	public:
		FlatColor(Color color) : color(color) {}

		virtual inline Color get(int32_t x, int32_t y) const override {
			return color;
		}
	};

	class FlatShade : public ColorProvider {
	private:
		Color color[2];
		uint8_t degree;
	public:
		FlatShade(Color color1, Color color2, uint8_t degree) :	degree(degree) {
			color[0] = color1;
			color[1] = color2;
		}

		virtual inline Color get(int32_t x, int32_t y) const override {
			return color[getShade(x, y, degree)];
		}
	};

	class Gradient : public ColorProvider {
	protected:
		std::vector<Color> colors;
		int32_t x, y, dx, dy;
	public:
		Gradient(std::vector<Color> &&colors, int32_t x, int32_t y, int32_t dx, int32_t dy) :
			colors(colors), x(x), y(y), dx(dx), dy(dy) {}
	};

	class ShapedGradient : public Gradient {
	protected:
		double unit_dist = 0;
	public:
		ShapedGradient(std::vector<Color> &&colors,
			int32_t x, int32_t y, int32_t dx, int32_t dy) :
			Gradient(std::move(colors), x, y, dx, dy) {}
	protected:
		virtual double dist(int32_t xp, int32_t yp) const = 0;
	};

	class LinearGradient : public ShapedGradient {
	public:
		LinearGradient(std::vector<Color> &&colors,
			int32_t x, int32_t y, int32_t dx, int32_t dy) :
			ShapedGradient(std::move(colors), x, y, dx, dy)	{
			unit_dist = dist(x + dx, y + dy);
		}
	protected:
		virtual double dist(int32_t xp, int32_t yp) const override;
	};

	class RadialGradient : public ShapedGradient {
	public:
		RadialGradient(std::vector<Color> &&colors,
			int32_t x, int32_t y, int32_t dx, int32_t dy) :
			ShapedGradient(std::move(colors), x, y, dx, dy) {
			unit_dist = dist(x + dx, y + dy);
		}
	protected:
		virtual double dist(int32_t xp, int32_t yp) const override;
	};

	class ConicalGradient : public ShapedGradient {
	public:
		ConicalGradient(std::vector<Color> &&colors,
			int32_t x, int32_t y, int32_t dx, int32_t dy) :
			ShapedGradient(std::move(colors), x, y, dx, dy) {
			unit_dist = dist(x + dx, y + dy);
		}
	protected:
		virtual double dist(int32_t xp, int32_t yp) const override;
	};

	class BinaryLinearGradient : public LinearGradient {
	public:
		BinaryLinearGradient(std::vector<Color> &&colors,
			int32_t x, int32_t y, int32_t dx, int32_t dy) :
			LinearGradient(std::move(colors), x, y, dx, dy) {}

		virtual Color get(int32_t x, int32_t y) const override;
	};
}
