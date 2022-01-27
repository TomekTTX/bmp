#include "colors.hpp"

namespace bmp {

	inline double transform(double a, double b, double degree = 1.) {
		a = std::pow(a, degree);
		return a / (a + std::pow(b, degree));
	}

	Color Color::blend(Color other, double frac, double blend_mode) const {
		frac = transform(frac, 1 - frac, blend_mode);
		return Color(
			rnd(r * (1 - frac) + other.r * frac),
			rnd(g * (1 - frac) + other.g * frac),
			rnd(b * (1 - frac) + other.b * frac)
		);
	}

	Color Color::blend(Color other, uint8_t alpha) const {
		const uint16_t thisMult = 0xFF - alpha, otherMult = alpha;
		return Color(
			(r * thisMult + other.r * otherMult) / 0xFF,
			(g * thisMult + other.g * otherMult) / 0xFF,
			(b * thisMult + other.b * otherMult) / 0xFF
		);
	}

	Color Color::blend(ColorA other) const {
		return blend(other, other.a);
	}

	Color ColorA::blend(const Color &other) const {
		return other.blend(*this, a);
	}

	bool ColorProvider::getShade(int32_t x, int32_t y, uint8_t degree) {
		switch (degree % degree_cnt) {
		case 0: return false;
		case 1:	return
			(x % 8 == 0 && y % 8 == 0) ||
			(x % 8 == 4 && y % 8 == 4);
		case 2:	return
			(x % 8 == 0 && (y % 8 == 2 || y % 8 == 6)) ||
			(x % 8 == 4 && (y % 8 == 0 || y % 8 == 4));
		case 3:	return
			(x % 4 == 0 && y % 4 == 0) ||
			(x % 4 == 2 && y % 4 == 2);
		case 4: return
			(x % 4 == 0 && (y % 4 == 1 || y % 4 == 3)) ||
			(x % 4 == 2 && (y % 4 == 0 || y % 4 == 2));
		case 5:	return
			(x % 4 == y % 4) || (x % 4 + y % 4 == 4);
		case 6: return
			(x % 2 == y % 2) &&
			!(x % 8 == 1 && y % 8 == 5) &&
			!(x % 8 == 5 && y % 8 == 1);
		case 7: return
			(x % 2 == y % 2);		
		default: return !getShade(x + 1, y, 14 - degree);
		}
	}

	Color Gradient::get(int32_t xp, int32_t yp) const {
		return binary_blend ?
			binaryGet(xp, yp, dist(xp, yp) / unit_dist) :
			blendGet(xp, yp, dist(xp, yp) / unit_dist);
	}

	// get color for binary mode
	Color Gradient::binaryGet(int32_t xp, int32_t yp, double distance) const {
		const uint32_t
			mult = rnd(distance * degree_cnt * (colors.size() - 1) / step) * step,
			deg = mult % degree_cnt;
		uint32_t index = mult / degree_cnt;

		if (repeating)
			index %= (colors.size() - 1);
		else if (index + 1 >= colors.size())
			return colors.back();
		return colors[index + getShade(xp, yp, deg)];
	}

	// get color for blend mode
	// note that this ignores the value of 'step'
	Color Gradient::blendGet(int32_t xp, int32_t yp, double distance) const {
		const double
			mult = distance * (colors.size() - 1),
			frac = std::fmod(mult, 1);
		uint32_t index = static_cast<uint32_t>(mult);

		if (repeating)
			index %= (colors.size() - 1);
		else if (index + 1 >= colors.size())
			return colors.back();
		return colors[index].blend(colors[index + 1], frac, blend_mode);
	}

	void Gradient::setRepeating(bool value) {
		if (value ^ repeating) {
			if (value)
				colors.push_back(colors.front());
			else
				colors.pop_back();
			repeating = value;
		}
	}

	// distance from point to line
	// d(P(xp, yp), (Ax + By + C = 0)) = |A*xp + B*yp + C| / sqrt(A*A + B*B)
	double LinearGradient::dist(int32_t xp, int32_t yp) const {
		return std::abs(vect.dx * xp + vect.dy * yp + c) * length_inverse;
	}

	// cartesian distance
	double RadialGradient::dist(int32_t xp, int32_t yp) const {
		const int32_t dx = vect.x - xp, dy = vect.y - yp;
		return std::sqrt(dx * dx + dy * dy);
	}

	// angular distance
	double ConicalGradient::dist(int32_t xp, int32_t yp) const {
		double ret = (std::atan2(yp - vect.y, xp - vect.x) - base_atan) / tau;
		ret += (ret < 0);
		return ret * vec_magn;
	}

	// combined angular and cartesian distance
	double SpiralGradient::dist(int32_t xp, int32_t yp) const {
		const int32_t dx = xp - vect.x, dy = yp - vect.y;
		const double point_angle = std::atan2(dy, dx);
		const double point_radius = std::sqrt(dx * dx + dy * dy) / sparsity;

		double ret = std::fmod(point_angle - start_angle + point_radius, tau) / tau;
		ret += (ret < 0);
		return ret * sparsity;
	}

	// "rotated manhattan distance" aka square equation
	double SquareGradient::dist(int32_t xp, int32_t yp) const {
		const int32_t dx = xp - vect.x, dy = yp - vect.y;
		return
			std::abs(dx * cosa + dy * sina) +
			std::abs(dx * sina - dy * cosa);
	}
	
	double SuperellipticGradient::dist(int32_t xp, int32_t yp) const {
		const int32_t dx = xp - vect.x, dy = yp - vect.y;
		const double
			dxr = std::pow(std::abs(dx * cosa + dy * sina), degree),
			dyr = std::pow(std::abs(dx * sina - dy * cosa) * ratio, degree);
		return std::pow(dxr + dyr, 1 / degree);
	}

	double SimplexGradient::dist(int32_t xp, int32_t yp) const {
		Pos<double> skewed = skew({ xp,yp });
		Pos<int32_t> cell = skewed;
		Pos<double> coords = skewed - cell;

		return coords.x + coords.y;
	}

	constexpr Pos<double> SimplexGradient::skew(Pos<int32_t> coords) {
		const double skew_val = (1. * coords.x + coords.y) * F;
		return {
			 skew_val + coords.x,
			 skew_val + coords.y,
		};
	}
}
