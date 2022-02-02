#include "shapes.hpp"
#include "ascii.hpp"
#include <cmath>

namespace shp {
	std::function<Shape::OptPoint()> SimpleLine::genFunc() const {
		return[this, xp = 0, yp = 0, len_left = len]() mutable->OptPoint {
			if (len_left-- > 0) {
				Point ret = { xp + x,yp + y };
				xp += dx, yp += dy;
				return ret;
			}
			return std::nullopt;
		};
	}

	std::function<Shape::OptPoint()> Line::genFunc() const {
		const int32_t dxa = abs(dx), dya = -abs(dy);
		const int8_t sx = sgn(dx), sy = sgn(dy);
		const int32_t x = this->x, y = this->y, dx = this->dx, dy = this->dy;
		return[x, y, dx, dy, dxa, dya, sx, sy, xp = 0, yp = 0,
			err = dxa + dya, endflag = false]() mutable->OptPoint {
			if (endflag)
				return std::nullopt;
			if (xp == dx && yp == dy)
				endflag = true;
			const int32_t e2 = 2 * err;
			Point ret = { xp + x,yp + y };

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

	std::function<Shape::OptPoint()> Rectangle::genFunc() const	{
		return[this, xp = 0, yp = 0]() mutable->OptPoint {
			Point ret{ x + xp,y + yp };

			if (yp >= dy)
				return std::nullopt;
			xp += (yp == 0 || yp == dy - 1) ? 1 : dx - 1;
			if (xp >= dx) {
				xp = 0;
				yp++;
			}

			return ret;
		};
	}

	std::function<Shape::OptPoint()> FilledRectangle::genFunc() const {
		return[this, xp = 0, yp = 0]() mutable->OptPoint {
			if (xp >= dx) {
				xp = 0;
				yp++;
			}
			if (yp >= dy)
				return std::nullopt;
			return Point(x + xp++, y + yp);
		};
	}

	std::function<Shape::OptPoint()> Circle::genFunc() const {
		const double angle_inc = tau / (base_density * r);
		const double half_step = angle_inc / 2;

		return[this, angle_inc, half_step, angle = -half_step]() mutable->OptPoint {
			if ((angle += angle_inc) > tau + half_step)
				return std::nullopt;
			return Point(rnd(r * cos(angle)) + x, rnd(r * sin(angle)) + y);
		};
	}

	std::function<Shape::OptPoint()> FilledCircle::genFunc() const {
		return[this, xp = -r, yp = -r]() mutable->OptPoint {
			for (; yp <= r; ++xp) {
				if (xp > r) {
					xp = -r;
					yp++;
				}
				if (xp * xp + yp * yp <= r * r)
					return Point(x + xp++, y + yp);
			}
			return std::nullopt;
		};
	}

	std::function<Shape::OptPoint()> Ellipse::genFunc() const {
		const double angle_inc = tau / (base_density * std::max(rx, ry));
		const double half_step = angle_inc / 2;
		const double sinr = sin(rotation), cosr = cos(rotation);

		return[this, angle_inc, half_step, sinr, cosr, angle = -half_step]() mutable->OptPoint {
			if ((angle += angle_inc) > tau + half_step)
				return std::nullopt;

			const double
				xp = rx * cos(angle),
				yp = ry * -sin(angle);
			return Point(rnd(xp * cosr + yp * sinr) + x, rnd(yp * cosr - xp * sinr) + y);
		};
	}

	std::function<Shape::OptPoint()> FilledEllipse::genFunc() const {
		const double sinr = -sin(rotation), cosr = cos(rotation);
		const int32_t limit = std::max(rx, ry);
		return[this, sinr, cosr, limit, xp = -limit, yp = -limit]() mutable->OptPoint {
			while (yp <= limit) {
				while (xp <= limit) {
					const double xr = xp * cosr + yp * sinr, yr = yp * cosr - xp * sinr;
					if (xr * xr / rx / rx + yr * yr / ry / ry <= 1)
						return Point(xp++ + x, yp + y);
					xp++;
				}
				xp = -rx;
				yp++;
			}
			return std::nullopt;
		};
	}

	std::function<Shape::OptPoint()> Arc::genFunc() const {
		const double angle_inc = tau / (base_density * std::max(rx, ry));

		return[this, angle_inc, angle = angle_min - angle_inc]() mutable->OptPoint {
			if ((angle += angle_inc) > angle_max)
				return std::nullopt;

			const double
				xp = rx * cos(angle),
				yp = ry * -sin(angle),
				sinr = sin(angle),
				cosr = cos(angle);
			return Point(rnd(xp * cosr + yp * sinr) + x, rnd(yp * cosr - xp * sinr) + y);
		};
	}

	Shape::Boundary CompositeShape::boundingRect() const {
		Boundary ret{};
		for (const auto &p : components)
			ret |= p->boundingRect();
		return ret;
	}

	Line Polyline::part(uint32_t index) const {
		return Line{ Point(pts[index]), Point(pts[(index + 1) % pts.size()]) };
	}

	std::function<Shape::OptPoint()> Polyline::genFunc() const {
		auto it{ iterator() }, end_it{ iterator() };
		return [this, it, end_it, index = -1, line = part(0)]() mutable->OptPoint {
			if (it == end_it) {
				if (++index == iterLimit)
					return std::nullopt;
				line = part(index);
				it = line.begin();
			}
			return *it++;
		};
	}

	std::function<Shape::OptPoint()> FilledPolygon::genFunc() const {
		Boundary br = boundingRect();
		return[this, br, xp = br.xm, yp = br.ym]() mutable->OptPoint {
			while (yp <= br.yM) {
				while (xp <= br.xM) {
					if (fillCondition(xp, yp))
						return Point(x + xp++, y + yp);
					xp++;
				}
				xp = br.xm;
				yp++;
			}
			return std::nullopt;
		};
	}

	bool FilledPolygon::fillCondition(int32_t x, int32_t y, bool include_border) const {
		bool ret = false;

		for (int32_t i = 0, j = (int32_t)pts.size() - 1; i < (int32_t)pts.size(); j = i++) {
			const auto pti = pts[i].round<int32_t>(), ptj = pts[j].round<int32_t>();
			if (x == pti.x && y == pti.y)
				return include_border;
			if ((pti.y > y) ^ (ptj.y > y)) {
				const int32_t slope =
					(x - pti.x) * (ptj.y - pti.y) -
					(y - pti.y) * (ptj.x - pti.x);
				if (slope == 0)
					return include_border;
				if ((slope < 0) ^ (ptj.y < pti.y)) {
					ret = !ret;
				}
			}
		}

		return ret;
	}

	Shape::Boundary Shape::pointSeqBoundary(const PointF *data, std::size_t cnt) {
		double
			xm = +INFINITY, xM = -INFINITY,
			ym = +INFINITY, yM = -INFINITY;
		for (std::size_t i = 0; i < cnt; ++i) {
			xm = std::min(xm, data[i].x);
			ym = std::min(ym, data[i].y);
			xM = std::max(xM, data[i].x);
			yM = std::max(yM, data[i].y);
		}
		return {
			static_cast<int32_t>(xm),
			static_cast<int32_t>(ym),
			static_cast<int32_t>(std::ceil(xM)),
			static_cast<int32_t>(std::ceil(yM)),
		};

	}

	PolyBase::PolyBase(int32_t x, int32_t y, int32_t radius, int32_t sides) {
		const double
			angle_inc = tau / sides,
			angle_init = (pi - angle_inc) / 2;

		pts.reserve(sides);
		for (double angle = angle_init; sides--; angle += angle_inc)
			pts.emplace_back(x + radius * cos(angle), y + radius * sin(angle));
		axis = { x,y };
	}

	PolyBase::PolyBase(int32_t x, int32_t y, const std::vector<int32_t> &radii,
		int32_t repeats) {
		const int32_t sides = repeats * radii.size();
		const double angle_inc = tau / sides;
		double angle = (pi - tau / repeats) / 2;

		pts.reserve(sides);
		while (repeats-- > 0) {
			for (auto radius : radii) {
				pts.emplace_back(x + radius * cos(angle), y + radius * sin(angle));
				angle += angle_inc;
			}
		}
		axis = { x,y };
	}

	PolyBase &PolyBase::rotate(double angle) {
		return rotate(angle, defaultAxis());
	}

	PolyBase &PolyBase::rotate(double angle, Point axis)	{
		for (auto &p : pts)
			p = p.rotated(angle, axis);
		return *this;
	}

	PolyBase &PolyBase::ravel(int32_t times) {
		const int32_t n = static_cast<int32_t>(pts.size());
		auto newvec = std::vector<PointF>(n);

		times = times % n;
		for (int32_t i = 0, index = 0; i < n; ++i) {
			newvec[i] = pts[index];
			index = (n + index + times) % n;
		}
		pts = newvec;
		return *this;
	}

	Shape::Point PolyBase::defaultAxis() const {
		return axis ? *axis : Shape::defaultAxis();
	}

	CompositeShape &CompositeShape::rotate(double angle) {
		return rotate(angle, defaultAxis());
	}

	CompositeShape &CompositeShape::rotate(double angle, Point axis) {
		for (const auto &comp : components)
			comp->rotate(angle, axis);
		return *this;
	}

	CharFactory Character::cf{};

	Character::Character(char chr, int32_t x, int32_t y, double scaleX, double scaleY) : chr(chr) {
		Character c = cf.make(chr, x, y, scaleX, scaleY);
		for (const auto &comp : c.content())
			addShape(*comp);
	}

	String::String(std::string_view str, const StringParams &params) : asciiStr(str) {
		int32_t x = params.x, y = params.y;
		const int32_t
			dx = rnd(XYFactory::baseSizeX * params.scaleX) + params.interX,
			dy = rnd(XYFactory::baseSizeY * params.scaleY) + params.interY;

		for (char c : str) {
			if (c == '\n') {
				y += dy;
				x = params.x;
				continue;
			}
			addShape(Character(c, x, y, params.scaleX, params.scaleY));
			x += dx;
		}
	}
}
