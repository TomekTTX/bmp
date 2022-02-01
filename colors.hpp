#pragma once
#include "common.hpp"
#include <vector>
#include <random>
#include <chrono>

namespace bmp {
	struct ColorA;

	struct Color {
		uint8_t r, g, b;

		inline constexpr Color() : r(0), g(0), b(0) {}
		inline constexpr Color(int32_t r, int32_t g, int32_t b) : r(r), g(g), b(b) {}
		inline constexpr Color(uint32_t r, uint32_t g, uint32_t b) : r(r), g(g), b(b) {}
		inline constexpr Color(uint32_t rgb) :
			r((rgb >> 16) & 0xFF), g((rgb >> 8) & 0xFF), b((rgb) & 0xFF) {}

		inline bool operator==(const Color &other) const {
			return r == other.r && g == other.g && b == other.b;
		}

		inline Color grayscale() {
			const uint8_t aprx_lumi = (r + r + r + (g << 2) + b) >> 3;
			return { aprx_lumi,aprx_lumi,aprx_lumi };
		}

		Color blend(Color other, double frac, double blend_mode) const;
		Color blend(Color other, uint8_t alpha) const;
		Color blend(ColorA other) const;
	};

	struct ColorA : public Color {
		uint8_t a;

		inline constexpr ColorA() : Color(), a(0) {}
		inline constexpr ColorA(int32_t r, int32_t g, int32_t b):
			Color(r, g, b), a(0xFF) {}
		inline constexpr ColorA(uint32_t r, uint32_t g, uint32_t b) :
			Color(r, g, b), a(0xFF) {}
		inline constexpr ColorA(int32_t r, int32_t g, int32_t b,
			int32_t a) : Color(r,g,b), a(a) {}
		inline constexpr ColorA(uint32_t r, uint32_t g, uint32_t b,
			uint32_t a) : Color(r, g, b), a(a) {}
		inline constexpr ColorA(uint32_t argb) :
			Color(argb), a((argb >> 24) & 0xFF) {}

		Color blend(const Color &other) const;
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

		inline Color get(int32_t x, int32_t y) const override {
			return color[getShade(x, y, degree)];
		}
	};

	class RandomColor : public ColorProvider {
	public:
		RandomColor() {}

		inline Color get(int32_t x, int32_t y) const override {
			return rng.integer();
		}
	};

	class RandomChoice : public ColorProvider {
	private:
		std::vector<Color> colors;
	public:
		RandomChoice(const std::vector<Color> &cols) : colors(cols) {
			if (colors.empty())
				colors.emplace_back();
		}

		inline Color get(int32_t x, int32_t y) const override {
			return colors[rng.integer(colors.size())];
		}
	};

	class RandomSingleColor : public ColorProvider {
	private:
		Color color;
	public:
		RandomSingleColor() : color(rng.integer()) {}

		inline Color get(int32_t x, int32_t y) const override {
			return color;
		}
	};

	class Progression : public ColorProvider {
	private:
		std::vector<Color> colors;
		double step;
		mutable double state = 0.;
	public:
		Progression(const std::vector<Color> &cols, double step) :
			colors(cols), step(step) {
			if (colors.empty())
				colors.emplace_back();
		}

		void advance() const {
			state = std::fmod(state + step, colors.size());
		}

		inline Color get(int32_t x, int32_t y) const override {
			const int32_t index1 = static_cast<int32_t>(state);
			const int32_t index2 = (index1 + 1) % colors.size();
			const double frac = state - index1;

			return colors[index1].blend(colors[index2], frac, 1.);
		}
	};

	class AutoProgression : public Progression {
	public:
		AutoProgression(const std::vector<Color> &cols, double step) :
			Progression(cols, step) {}

		inline Color get(int32_t x, int32_t y) const override {
			Color ret = Progression::get(x, y);
			advance();
			return ret;
		}
	};

	class Gradient : public ColorProvider {
	public:
		struct Vect {
			int32_t x, y, dx, dy;
			inline double len() const { return std::sqrt(dx * dx + dy * dy); }
			inline double angle() const { return std::atan2(dy, dx); }
			inline double sin() const { return dy / len(); }
			inline double cos() const { return dx / len(); }
		};
	protected:
		Vect vect{}; // vect is used for calculations in overrides of dist()
	private:
		std::vector<Color> colors;
		double unit_dist = 0, blend_mode = 1;
		uint8_t step = 1;
		bool repeating = false, binary_blend = true;
	public:
		Gradient(const std::vector<Color> &colors, const Vect &vect, double mult, uint8_t step) :
			colors(colors), vect(vect), unit_dist(vect.len() * mult), step(step) {
			if (colors.empty())
				this->colors.emplace_back();
			setRepeating();
		}

		virtual Color get(int32_t xp, int32_t yp) const override;

		inline void translate(int32_t x, int32_t y) { vect.x += x, vect.y += y; }
		inline void setBlendMode(double mode = 1.) { blend_mode = mode, binary_blend = false; }
		inline void setBinaryMode() { binary_blend = true; }
		void setRepeating(bool value = true);
	private:
		virtual double dist(int32_t xp, int32_t yp) const = 0;
		Color binaryGet(int32_t xp, int32_t yp, double distance) const;
		Color blendGet(int32_t xp, int32_t yp, double distance) const;
	};

	class LinearGradient : public Gradient {
	private:
		double length_inverse;
		int32_t c;
	public:
		LinearGradient(const std::vector<Color> &colors, const Vect &vect,
			double mult = 1., uint8_t step = 1) :
			Gradient(colors, vect, mult, step), length_inverse(1 / vect.len()),
			c(-(vect.dx * vect.x + vect.dy * vect.y)) {}
	private:
		double dist(int32_t xp, int32_t yp) const override;
	};

	class RadialGradient : public Gradient {
	public:
		RadialGradient(const std::vector<Color> &colors, const Vect &vect,
			double mult = 1., uint8_t step = 1) :
			Gradient(colors, vect, mult, step) {}
	private:
		double dist(int32_t xp, int32_t yp) const override;
	};

	class ConicalGradient : public Gradient {
	private:
		double base_atan, vec_magn;
	public:
		ConicalGradient(const std::vector<Color> &colors, const Vect &vect,
			double mult = 1., uint8_t step = 1) :
			Gradient(colors, vect, 1 / mult, step),
			base_atan(vect.angle()), vec_magn(vect.len()) {}
	private:
		double dist(int32_t xp, int32_t yp) const override;
	};

	class SpiralGradient : public Gradient {
	private:
		double start_angle, sparsity;
	public:
		SpiralGradient(const std::vector<Color> &colors, const Vect &vect,
			double mult = 1., uint8_t step = 1) :
			Gradient(colors, vect, 1 / mult, step),
			start_angle(vect.angle()), sparsity(vect.len()) {}
	private:
		double dist(int32_t xp, int32_t yp) const override;
	};

	class SquareGradient : public Gradient {
	private:
		double sina, cosa;
	public:
		SquareGradient(const std::vector<Color> &colors, const Vect &vect,
			double mult = 1., uint8_t step = 1) :
			Gradient(colors, vect, mult, step),
			sina(vect.sin()), cosa(vect.cos()) {}
	private:
		double dist(int32_t xp, int32_t yp) const override;
	};

	class SuperellipticGradient : public Gradient {
	private:
		double sina, cosa, degree, ratio;
	public:
		SuperellipticGradient(const std::vector<Color> &colors, const Vect &vect,
			double deg, double xyratio = 1., double mult = 1., uint8_t step = 1) :
			Gradient(colors, vect, mult, step), ratio(xyratio),
			degree(deg), sina(vect.sin()), cosa(vect.cos()) {}
	private:
		double dist(int32_t xp, int32_t yp) const override;
	};

	// WIP
	class SimplexGradient : public Gradient {
	private:
		static constexpr double F = 0.3660254037844; // (sqrt(3) - 1) / 2
		static constexpr double G = 0.2113248654052; // (1 - 1/sqrt(3)) / 2
	public:
		SimplexGradient(const std::vector<Color> &colors, const Vect &vect,
			double mult = 1., uint8_t step = 1) :
			Gradient(colors, vect, mult, step) {}
	private:
		double dist(int32_t xp, int32_t yp) const override;
		static constexpr Pos<double> skew(Pos<int32_t> coords);
	};
}
