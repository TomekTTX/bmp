#include "shapes.hpp"
#include <cmath>

namespace shp {
	std::function<Shape::opt_type()> SimpleLine::genFunc() const {
		return[this, xp = 0, yp = 0, len_left = len]() mutable->opt_type {
			if (len_left-- > 0) {
				base_type ret = { xp + x,yp + y };
				xp += dx, yp += dy;
				return ret;
			}
			return std::nullopt;
		};
	}

	std::function<Shape::opt_type()> Line::genFunc() const {
		const int32_t dxa = abs(dx), dya = -abs(dy);
		const int8_t sx = sgn(dx), sy = sgn(dy);
		return[this, dxa, dya, sx, sy, xp = 0, yp = 0, err = dxa + dya]() mutable->opt_type {
			if (xp == dx && yp == dy)
				return std::nullopt;
			const int32_t e2 = 2 * err;
			base_type ret = { xp + x,yp + y };

			if (e2 >= dya) {
				err += dya;
				xp += sx;
			}
			if (e2 <= dxa) {
				err += dxa;
				yp += sy;
			}
			return ret;
		};		
	}

	std::function<Shape::opt_type()> Circle::genFunc() const {
		const double angle_inc = tau / (base_density * r);
		const double half_step = angle_inc / 2;

		return[this, angle_inc, half_step, angle = -half_step]() mutable->opt_type {
			if ((angle += angle_inc) > tau + half_step)
				return std::nullopt;
			return base_type(rnd(r * cos(angle)) + x, rnd(r * sin(angle)) + y);
		};
	}

	std::function<Shape::opt_type()> FilledCircle::genFunc() const {
		return[this, xp = -r, yp = -r]() mutable->opt_type {
			for (; yp <= r; ++xp) {
				if (xp > r) {
					xp = -r;
					yp++;
				}
				if (xp * xp + yp * yp <= r * r)
					return base_type(x + xp++, y + yp);
			}
			return std::nullopt;
		};
	}

	std::function<Shape::opt_type()> Ellipse::genFunc() const {
		const double angle_inc = tau / (base_density * std::max(rx, ry));
		const double half_step = angle_inc / 2;
		const double sinr = sin(rotation), cosr = cos(rotation);

		return[this, angle_inc, half_step, sinr, cosr, angle = -half_step]() mutable->opt_type {
			if ((angle += angle_inc) > tau + half_step)
				return std::nullopt;

			const double
				xp = rx * cos(angle),
				yp = ry * -sin(angle);
			return base_type(rnd(xp * cosr + yp * sinr) + x, rnd(yp * cosr - xp * sinr) + y);
		};
	}

	std::function<Shape::opt_type()> FilledEllipse::genFunc() const {
		const double sinr = sin(rotation), cosr = cos(rotation);
		const int32_t limit = std::max(rx, ry);
		return[this, sinr, cosr, limit, xp = -limit, yp = -limit]() mutable->opt_type {
			while (yp <= limit) {
				while (xp <= limit) {
					const double xr = xp * cosr + yp * sinr, yr = yp * cosr - xp * sinr;

					if (xr * xr / rx / rx + yr * yr / ry / ry <= 1)
						return base_type(xp++ + x, yp + y);
					xp++;
				}
				xp = -rx;
				yp++;
			}
			return std::nullopt;
		};
	}

	std::function<Shape::opt_type()> Arc::genFunc() const {
		const double angle_inc = tau / (base_density * std::max(rx, ry));

		return[this, angle_inc, angle = angle_min - angle_inc]() mutable->opt_type {
			if ((angle += angle_inc) > angle_max)
				return std::nullopt;

			const double
				xp = rx * cos(angle),
				yp = ry * -sin(angle),
				sinr = sin(rotation),
				cosr = cos(rotation);
			return base_type(rnd(xp * cosr + yp * sinr) + x, rnd(yp * cosr - xp * sinr) + y);
		};
	}

	CompositeShape::comp_iterator CompositeShape::composite() const {
		std::vector<comp_iterator::IterPair> iters;
		for (auto &comp : components)
			iters.push_back({ comp->begin(), comp->end() });
		return comp_iterator(std::move(iters));
	}

	std::function<Shape::opt_type()> shp::CompositeShape::genFunc() const {
		return[it = composite(), end_it = comp_iterator()]() mutable->opt_type {
			if (it == end_it)
				return std::nullopt;
			return *it++;
		};
	}
}
