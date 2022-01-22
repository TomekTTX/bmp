#include "colors.hpp"

namespace bmp {

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
		default: return !getShade(x, y, 14 - degree);
		}
	}

	// distance from point to line
	// d(P(xp, yp), (Ax + By + C = 0)) = |A*xp + B*yp + C| / sqrt(A*A + B*B)
	double LinearGradient::dist(int32_t xp, int32_t yp) const	{
		static const double div = 1 / vect.len();
		static const int32_t c = -(vect.dx * vect.x + vect.dy * vect.y);
		return std::abs(vect.dx * xp + vect.dy * yp + c) * div;
	}

	double RadialGradient::dist(int32_t xp, int32_t yp) const {
		const int32_t xdif = vect.x - xp, ydif = vect.y - yp;
		return std::sqrt(xdif * xdif + ydif * ydif);
	}

	double ConicalGradient::dist(int32_t xp, int32_t yp) const	{
		static const double base = vect.angle();
		double ret = std::atan2(yp - vect.y, xp - vect.x) - base;
		if (ret < 0)
			ret += tau;
		return ret;
	}

	Color Gradient::binaryGet(int32_t xp, int32_t yp) const {
		const uint32_t
			mult = rnd(dist(xp, yp) / unit_dist) * step,
			index = mult / degree_cnt,
			deg = mult % degree_cnt;

		if (index >= colors.size() - 1)
			return colors.back();
		return colors[index + getShade(xp, yp, deg)];
	}
}
