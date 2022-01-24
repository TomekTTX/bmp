#pragma once
#include "common.hpp"
#include <vector>
#include <random>
#include <chrono>

namespace bmp {
	struct Color {
		uint8_t r, g, b;

		inline constexpr Color() : r(0), g(0), b(0) {};
		inline constexpr Color(int32_t r, int32_t g, int32_t b) : r(r), g(g), b(b) {}
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

	class RandomColor : public ColorProvider {
	public:
		RandomColor() {}

		virtual inline Color get(int32_t x, int32_t y) const override {
			return { rng.integer() };
		}
	};

	class RandomChoice : public ColorProvider {
	private:
		std::vector<Color> colors;
	public:
		RandomChoice(const std::vector<Color> &col) : colors(col) {
			if (colors.empty())
				colors.emplace_back();
		}

		virtual inline Color get(int32_t x, int32_t y) const override {
			return colors[rng.integer(colors.size())];
		}
	};

	class Gradient : public ColorProvider {
	public:
		struct Vect {
			int32_t x, y, dx, dy;
			inline double len() const { return std::sqrt(dx * dx + dy * dy); }
			inline double angle() const { return std::atan2(dy, dx); }
		};
	protected:
		Vect vect{};
	private:
		std::vector<Color> colors;
		double unit_dist = 0, blend_mode = 1;
		uint8_t step = 1;
		bool repeating = false, binary_blend = true;
	public:
		Gradient(std::vector<Color> &&colors, const Vect &vect,	double mult, uint8_t step) :
			colors(colors), vect(vect), unit_dist(vect.len() * mult), step(step) {
			if (colors.empty())
				this->colors.emplace_back();
		}

		virtual Color get(int32_t xp, int32_t yp) const override;

		inline void translate(int32_t x, int32_t y) { vect.x += x, vect.y += y; }
		inline void setVect(const Vect &newVect) { vect = newVect; }
		inline void setBlendMode(double mode = 1.) { blend_mode = mode, binary_blend = false; }
		inline void setBinaryMode() { binary_blend = true; }
		void setRepeating(bool value = true);
	protected:
		virtual double dist(int32_t xp, int32_t yp) const = 0;
	private:
		Color binaryGet(int32_t xp, int32_t yp, double distance) const;
		Color blendGet(int32_t xp, int32_t yp, double distance) const;
		static Color blend(Color color1, Color color2, double frac, double mean_exponent);
	};

	class LinearGradient : public Gradient {
	private:
		double div;
		int32_t c;
	public:
		LinearGradient(std::vector<Color> &&colors, const Vect &vect,
			double mult = 1., uint8_t step = 1) :
			Gradient(std::move(colors), vect, mult, step), div(1 / vect.len()),
			c(-(vect.dx * vect.x + vect.dy * vect.y)) {}
	protected:
		virtual double dist(int32_t xp, int32_t yp) const override;
	};

	class RadialGradient : public Gradient {
	public:
		RadialGradient(std::vector<Color> &&colors, const Vect &vect,
			double mult = 1., uint8_t step = 1) :
			Gradient(std::move(colors), vect, mult, step) {}
	protected:
		virtual double dist(int32_t xp, int32_t yp) const override;
	};

	class ConicalGradient : public Gradient {
	private:
		double base_atan;
	public:
		ConicalGradient(std::vector<Color> &&colors, const Vect &vect,
			double mult = 1., uint8_t step = 1) :
			Gradient(std::move(colors), vect, 1 / mult, step),
			base_atan(vect.angle()) {}
	protected:
		virtual double dist(int32_t xp, int32_t yp) const override;
	};

	//class FunctionalGradient : public Gradient {
	//
	//};
}
