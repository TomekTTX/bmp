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

	// distance from point to line
	// d(P(xp, yp), (Ax + By + C = 0)) = |A*xp + B*yp + C| / sqrt(A*A + B*B)
	double LinearGradient::dist(int32_t xp, int32_t yp) const {
		return std::abs(vect.dx * xp + vect.dy * yp + c) * div;
	}

	// cartesian distance
	double RadialGradient::dist(int32_t xp, int32_t yp) const {
		const int32_t xdif = vect.x - xp, ydif = vect.y - yp;
		return std::sqrt(xdif * xdif + ydif * ydif);
	}

	// angular distance
	double ConicalGradient::dist(int32_t xp, int32_t yp) const {
		double ret = std::atan2(yp - vect.y, xp - vect.x) - base_atan;
		if (ret < 0)
			ret += tau;
		return ret;
	}

	void Gradient::setRepeating(bool value)	{
		if (value ^ repeating) {
			if (value)
				colors.push_back(colors.front());
			else
				colors.pop_back();
			repeating = value;
		}
	}

	Color Gradient::binaryGet(int32_t xp, int32_t yp, double distance) const {
		const uint32_t
			mult = rnd(distance) * step,
			deg = mult % degree_cnt;
		uint32_t index = mult / degree_cnt;

		if (repeating)
			index %= (colors.size() - 1);
		else if (index + 1 >= colors.size())
			return colors.back();
		return colors[index + getShade(xp, yp, deg)];
	}
	
	Color Gradient::blendGet(int32_t xp, int32_t yp, double distance) const {
		const double
			mult = distance * step / degree_cnt,
			frac = std::fmod(mult, 1);
		uint32_t index = static_cast<uint32_t>(mult);

		if (repeating)
			index %= (colors.size() - 1);
		else if (index >= colors.size() - 1)
			return colors.back();
		return colors[index].blend( colors[index + 1], frac, blend_mode);
	}

	Color Gradient::get(int32_t xp, int32_t yp) const {
		return binary_blend ?
			binaryGet(xp, yp, dist(xp, yp) / unit_dist) :
			blendGet(xp, yp, dist(xp, yp) / unit_dist);
	}
}
