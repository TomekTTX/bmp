#include <cmath>
#include <queue>
#include <unordered_set>
#include <fstream>
#include "bmp.hpp"
#include "ascii.hpp"

namespace bmp {

	void BitmapFileHeader::readFrom(std::istream &ist) {
		ist.read(reinterpret_cast<char *>(&bfType), sizeof bfType);
		ist.read(reinterpret_cast<char *>(&bfSize), sizeof bfSize);
		ist.read(reinterpret_cast<char *>(&bfReserved1), sizeof bfReserved1);
		ist.read(reinterpret_cast<char *>(&bfReserved2), sizeof bfReserved2);
		ist.read(reinterpret_cast<char *>(&bfOffBits), sizeof bfOffBits);
	}

	void  BitmapFileHeader::writeTo(std::ostream &ost) const {
		ost.write(reinterpret_cast<const char *>(&bfType), sizeof bfType);
		ost.write(reinterpret_cast<const char *>(&bfSize), sizeof bfSize);
		ost.write(reinterpret_cast<const char *>(&bfReserved1), sizeof bfReserved1);
		ost.write(reinterpret_cast<const char *>(&bfReserved2), sizeof bfReserved2);
		ost.write(reinterpret_cast<const char *>(&bfOffBits), sizeof bfOffBits);
	}

	void BitmapInfoHeader::readFrom(std::istream &ist) {
		ist.read(reinterpret_cast<char *>(&biSize), sizeof biSize);
		ist.read(reinterpret_cast<char *>(&biWidth), sizeof biWidth);
		ist.read(reinterpret_cast<char *>(&biHeight), sizeof biHeight);
		ist.read(reinterpret_cast<char *>(&biPlanes), sizeof biPlanes);
		ist.read(reinterpret_cast<char *>(&biBitCount), sizeof biBitCount);
		ist.read(reinterpret_cast<char *>(&biCompression), sizeof biCompression);
		ist.read(reinterpret_cast<char *>(&biSizeImage), sizeof biSizeImage);
		ist.read(reinterpret_cast<char *>(&biXpelsPerMeter), sizeof biXpelsPerMeter);
		ist.read(reinterpret_cast<char *>(&biYpelsPerMeter), sizeof biYpelsPerMeter);
		ist.read(reinterpret_cast<char *>(&biCrlUses), sizeof biCrlUses);
		ist.read(reinterpret_cast<char *>(&biCrlImportant), sizeof biCrlImportant);
	}

	void BitmapInfoHeader::writeTo(std::ostream &ost) const {
		ost.write(reinterpret_cast<const char *>(&biSize), sizeof biSize);
		ost.write(reinterpret_cast<const char *>(&biWidth), sizeof biWidth);
		ost.write(reinterpret_cast<const char *>(&biHeight), sizeof biHeight);
		ost.write(reinterpret_cast<const char *>(&biPlanes), sizeof biPlanes);
		ost.write(reinterpret_cast<const char *>(&biBitCount), sizeof biBitCount);
		ost.write(reinterpret_cast<const char *>(&biCompression), sizeof biCompression);
		ost.write(reinterpret_cast<const char *>(&biSizeImage), sizeof biSizeImage);
		ost.write(reinterpret_cast<const char *>(&biXpelsPerMeter), sizeof biXpelsPerMeter);
		ost.write(reinterpret_cast<const char *>(&biYpelsPerMeter), sizeof biYpelsPerMeter);
		ost.write(reinterpret_cast<const char *>(&biCrlUses), sizeof biCrlUses);
		ost.write(reinterpret_cast<const char *>(&biCrlImportant), sizeof biCrlImportant);
	}

	BMP::BMP(std::istream &ist, Color bgColor) : bgColor(bgColor) {
		readFrom(ist);
	}

	BMP::BMP(std::size_t width, std::size_t height, Color bgColor) : bgColor(bgColor) {
		initDefaultHeaders();

		pad_size = width % 4;

		bih.biWidth = width;
		bih.biHeight = height;
		bih.biSizeImage = (3 * width + pad_size) * height;
		bfh.bfSize = bfh.bfOffBits + bih.biSizeImage;

		color_space = Matrix<Color>(height, width, bgColor);
	}

	BMP::BMP(const std::string_view &fileName, Color bgColor) {
		std::ifstream file{ fileName.data(), std::ios::binary | std::ios::in };
		if (file.is_open())
			readFrom(file);
		else
			initDefaultHeaders();
	}

	void BMP::readFrom(std::istream &ist) {
		bfh.readFrom(ist);
		bih.readFrom(ist);
		pad_size = bih.biWidth % 4;
		color_space = Matrix<Color>(bih.biHeight, bih.biWidth);

		int32_t width_ctr = 0;
		for (auto &col : color_space) {
			char bgr[3];
			ist.read(bgr, sizeof bgr);
			col.b = bgr[0];
			col.g = bgr[1];
			col.r = bgr[2];
			if (pad_size != 0 && ++width_ctr >= bih.biWidth) {
				width_ctr = 0;
				ist.ignore(pad_size);
			}
		}
	}

	void BMP::initDefaultHeaders() {
		bfh.bfType = 'B' | ('M' << 8);
		bfh.bfReserved1 = bfh.bfReserved2 = 0;
		bfh.bfOffBits = bfh.bfSize = 54;

		bih.biSize = 40;
		bih.biPlanes = 1;
		bih.biBitCount = 24;
		bih.biCompression = 0;
		bih.biXpelsPerMeter = bih.biYpelsPerMeter = 3780;
		bih.biCrlUses = bih.biCrlImportant = 0;
		bih.biWidth = bih.biHeight = 0;
	}

	void BMP::writeTo(std::ostream &ost) const {
		constexpr char zeros[3] = { 0 };

		bfh.writeTo(ost);
		bih.writeTo(ost);

		int32_t width_ctr = 0;
		for (const auto &col : color_space) {
			const char bgr[3] = { (char)col.b, (char)col.g, (char)col.r };
			ost.write(bgr, sizeof bgr);
			if (pad_size != 0 && ++width_ctr >= bih.biWidth) {
				width_ctr = 0;
				ost.write(zeros, pad_size);
			}
		}
	}

	void BMP::writeTo(const std::string_view &fileName) const {
		std::ofstream file{ fileName.data(), std::ios::binary | std::ios::out };
		if (file.is_open())
			writeTo(file);
	}

	void BMP::drawShape(const shp::Shape &shape, Color color, int32_t x, int32_t y) {
		for (const auto &p : shape)
			drawPixel(p.x + x, p.y + y, color);
	}

	void BMP::drawShape(const shp::Shape &shape, const ColorProvider &prov,
		int32_t x, int32_t y) {
		for (const auto &p : shape)
			drawPixel(p.x + x, p.y + y, prov.get(p.x, p.y));
	}

	void BMP::drawShape(const shp::Shape &shape, Color color,
		uint8_t alpha, int32_t x, int32_t y) {
		for (const auto &p : shape)
			drawPixel(p.x + x, p.y + y, color, alpha);
	}

	void BMP::drawShape(const shp::Shape &shape, const ColorProvider &prov,
		uint8_t alpha, int32_t x, int32_t y) {
		for (const auto &p : shape)
			drawPixel(p.x + x, p.y + y, prov.get(p.x, p.y), alpha);
	}

	Surface BMP::copySurface(const shp::Shape &shape, int32_t x, int32_t y) const {
		auto br = shape.boundingRect();
		Surface ret{ 1U + br.xM - br.xm, 1U + br.yM - br.ym };

		for (const auto &p : shape)
			ret.set(p.x - br.xm, p.y - br.ym, pixel(x + p.x, y + p.y));

		return ret;
	}

	void BMP::pasteSurface(const Surface &surface, int32_t x, int32_t y, uint8_t alpha) {
		for (uint32_t yp = 0; yp < surface.height(); ++yp)
			for (uint32_t xp = 0; xp < surface.width(); ++xp)
				if (surface.hasColor(xp, yp))
					drawPixel(x + xp, y + yp, surface(xp, yp), alpha);
	}

	void BMP::blit(const BMP &src, int32_t x, int32_t y, uint8_t alpha) {
		for (uint32_t yp = 0; yp < src.height() && yp + y < height(); ++yp)
			for (uint32_t xp = 0; xp < src.width() && xp + x < width(); ++xp)
				drawPixel(x + xp, y + yp, src.pixel(xp, yp), alpha);
	}

	void BMP::drawSimpleLine(int32_t x, int32_t y, int8_t dx, int8_t dy, int32_t len, Color color) {
		dx = sgn(dx);
		dy = sgn(dy);

		while (len-- > -1) {
			drawPixel(x, y, color);
			x += dx;
			y += dy;
		}
	}

	void BMP::drawLine(int32_t x0, int32_t y0, int32_t x1, int32_t y1, Color color) {
		drawPixel(x0, y0, color);
		drawPixel(x1, y1, color);
		if (x0 == x1 && y0 == y1)
			return;

		const double dx = static_cast<double>(x1) - x0;
		const double dy = static_cast<double>(y1) - y0;
		double x = x0, y = y0;
		double *arg, *val, arg_inc, tangent;
		if (std::abs(dx) > std::abs(dy)) {
			arg = &x;
			val = &y;
			arg_inc = (x0 < x1) ? 1 : -1;
			tangent = dy / dx * arg_inc;
		}
		else {
			arg = &y;
			val = &x;
			arg_inc = (y0 < y1) ? 1 : -1;
			tangent = dx / dy * arg_inc;
		}

		while (((x < x1) ^ (dx < 0)) || ((y < y1) ^ (dy < 0))) {
			drawPixelRound(x, y, color);
			*arg += arg_inc;
			*val += tangent;
		}
	}

	void BMP::drawPolyline(const Poly &poly, Color color) {
		for (int32_t i = 1, j = 0; i < (int32_t)poly.size(); j = i++)
			drawLine(poly[i].x, poly[i].y, poly[j].x, poly[j].y, color);
	}

	void BMP::drawQuadrBezier(const BezierArrayQuadr &pts, Color color) {
		constexpr double step_base = 0.5;
		const double steps[] = { pts[0].dist(pts[1]) + 1, pts[1].dist(pts[2]) + 1 };
		double step = step_base / steps[0];

		for (double t = 0, it = 1; t <= 1; it = 1 - (t += step)) {
			const Pos<double> point =
				pts[0] * (it * it) +
				pts[1] * (2 * t * it) +
				pts[2] * (t * t);
			step = step_base / (t * steps[1] + it * steps[0]);
			drawPixelRound(point.x, point.y, color);
		}
	}

	void BMP::drawQuadrBezier(std::initializer_list<Pos<double>> pts, Color color) {
		constexpr uint8_t elems = 3;
		uint8_t ctr = 0;
		BezierArrayQuadr arr{};

		for (const auto &p : pts) {
			arr[ctr++] = p;
			if (ctr == elems)
				break;
		}
		drawQuadrBezier(arr, color);
	}

	void BMP::drawCubicBezier(const BezierArrayCubic &pts, Color color) {
		constexpr double step_base = 0.5;
		const double steps[] = {
			pts[0].dist(pts[1]) + 1,
			pts[1].dist(pts[2]) + 1,
			pts[2].dist(pts[3]) + 1
		};
		double step = step_base / steps[0];

		for (double t = 0, it = 1; t <= 1; it = 1 - (t += step)) {
			const Pos<double> point =
				pts[0] * (it * it * it) +
				pts[1] * (3 * t * it * it) +
				pts[2] * (3 * t * t * it) +
				pts[3] * (t * t * t);
			step = step_base / (t * steps[2] + steps[1] + it * steps[0]);
			drawPixelRound(point.x, point.y, color);
		}
	}

	void BMP::drawCubicBezier(std::initializer_list<Pos<double>> pts, Color color) {
		constexpr uint8_t elems = 4;
		uint8_t ctr = 0;
		BezierArrayCubic arr{};

		for (const auto &p : pts) {
			arr[ctr++] = p;
			if (ctr == elems)
				break;
		}
		drawCubicBezier(arr, color);
	}

	void BMP::drawParametric(int32_t x, int32_t y, ParamFunc xfunc, ParamFunc yfunc,
		Color color, double tmin, double tmax, double density) {
		const double t_inc = 1. / density;

		for (double t = tmin; t <= tmax; t += t_inc)
			drawPixel(x + rnd(xfunc(t)), y + rnd(yfunc(t)), color);
	}

	void BMP::drawRect(int32_t x0, int32_t y0, int32_t x1, int32_t y1, Color color) {
		const int32_t width = x1 - x0, height = y1 - y0;

		drawSimpleLine(x0, y0, 1, 0, width, color);
		drawSimpleLine(x0, y0, 0, 1, height, color);
		drawSimpleLine(x0, y1, 1, 0, width, color);
		drawSimpleLine(x1, y0, 0, 1, height, color);
	}

	void BMP::fillRect(int32_t x0, int32_t y0, int32_t x1, int32_t y1, Color color) {
		const int32_t width = x1 - x0 + 1;

		for (int32_t y = y0; y <= y1; ++y)
			drawSimpleLine(x0, y, 1, 0, width, color);
	}

	void BMP::drawFilledRect(int32_t x0, int32_t y0, int32_t x1, int32_t y1,
		Color line_color, Color fill_color) {

		if (x1 == 0 || y1 == 0)
			return;
		fillRect(x0 + 1, y0 + 1, x1 - 1, y1 - 1, fill_color);
		drawRect(x0, y0, x1, y1, line_color);
	}

	void BMP::drawRect(int32_t x0, int32_t y0, int32_t x1, int32_t y1, double rotation, Color color) {
		drawPolygon(rotatedRect(x0, y0, x1, y1, rotation), color);
	}

	void BMP::fillRect(int32_t x0, int32_t y0, int32_t x1, int32_t y1, double rotation, Color color) {
		fillPolygon(rotatedRect(x0, y0, x1, y1, rotation), color);
	}

	void BMP::drawFilledRect(int32_t x0, int32_t y0, int32_t x1, int32_t y1, double rotation,
		Color line_color, Color fill_color) {

		drawFilledPolygon(rotatedRect(x0, y0, x1, y1, rotation), line_color, fill_color);
	}

	void BMP::drawPolygon(const Poly &poly, Color color) {
		for (int32_t i = 0, j = (int32_t)poly.size() - 1; i < (int32_t)poly.size(); j = i++)
			drawLine(poly[i].x, poly[i].y, poly[j].x, poly[j].y, color);
	}

	void BMP::fillPolygon(const Poly &poly, Color color, bool include_border) {
		const auto br = boundingRect(poly);
		const int32_t xmin = br[0], ymin = br[1], xmax = br[2], ymax = br[3];

		for (int32_t y = ymin; y <= ymax; ++y)
			for (int32_t x = xmin; x <= xmax; ++x)
				if (evenOddRule(x, y, poly, include_border))
					drawPixel(x, y, color);
	}

	void BMP::drawFilledPolygon(const Poly &poly, Color line_color, Color fill_color) {
		fillPolygon(poly, fill_color, false);
		drawPolygon(poly, line_color);
	}

	void BMP::drawArc(int32_t x, int32_t y, int32_t rx, int32_t ry,
		double from, double to, Color color) {

		constexpr double pixel_mult = 8;
		const double angle_inc = tau / (std::max(rx, ry) * pixel_mult);
		const double offset = 0.001;

		for (double angle = from + offset; angle <= to + offset; angle += angle_inc)
			drawPixelRound(x + rx * cos(-angle), y + ry * sin(-angle), color);
	}

	void BMP::drawCircle(int32_t x, int32_t y, int32_t r, Color color) {
		drawEllipse(x, y, r, r, color);
	}

	void BMP::fillCircle(int32_t x, int32_t y, int32_t r, Color color) {
		fillEllipse(x, y, r, r, color);
	}

	void BMP::drawFilledCircle(int32_t x, int32_t y, int32_t r, Color line_color, Color fill_color) {
		drawFilledEllipse(x, y, r, r, line_color, fill_color);
	}

	void BMP::drawEllipse(int32_t x, int32_t y, int32_t rx, int32_t ry, Color color) {
		constexpr double pixel_mult = 8;
		const double angle_inc = tau / (std::max(rx, ry) * pixel_mult);
		const double half_step = angle_inc / 2;

		for (double angle = half_step; angle <= tau + half_step; angle += angle_inc)
			drawPixelRound(x + rx * cos(angle), y + ry * sin(angle), color);
	}

	void BMP::fillEllipse(int32_t x, int32_t y, int32_t rx, int32_t ry, Color color) {
		for (int32_t yp = -ry; yp <= ry; ++yp)
			for (int32_t xp = -rx; xp <= rx; ++xp)
				if (ellipse_pred_int(xp, yp, rx, ry))
					drawPixel(x + xp, y + yp, color);
	}

	void BMP::drawFilledEllipse(int32_t x, int32_t y, int32_t rx, int32_t ry,
		Color line_color, Color fill_color) {

		fillEllipse(x, y, rx, ry, fill_color);
		drawEllipse(x, y, rx, ry, line_color);
	}

	void BMP::drawEllipse(int32_t x, int32_t y, int32_t rx, int32_t ry, double rotation, Color color) {
		constexpr double pixel_mult = 8;
		const double angle_inc = tau / (std::max(rx, ry) * pixel_mult);
		const double half_step = angle_inc / 2;
		const double sinr = sin(rotation), cosr = cos(rotation);

		for (double angle = half_step; angle <= tau + half_step; angle += angle_inc) {
			const double dx = rx * cos(angle), dy = ry * sin(angle);
			drawPixelRound(x + dx * cosr + dy * sinr, y + dy * cosr - dx * sinr, color);
		}
	}

	void BMP::fillEllipse(int32_t x, int32_t y, int32_t rx, int32_t ry, double rotation, Color color) {
		const int32_t xm = std::max(x, y), ym = xm;
		const double sinr = sin(-rotation), cosr = cos(-rotation);
		const auto predicate = [=](int32_t x, int32_t y)->bool {
			const double rot_x = x * cosr + y * sinr;
			const double rot_y = y * cosr - x * sinr;
			return ellipse_pred(rot_x, rot_y, rx, ry);
		};

		for (int32_t yp = -ym; yp <= ym; ++yp)
			for (int32_t xp = -xm; xp <= xm; ++xp)
				if (predicate(xp, yp))
					drawPixel(xp + x, yp + x, color);
	}



	void BMP::drawFilledEllipse(int32_t x, int32_t y, int32_t rx, int32_t ry,
		double rotation, Color line_color, Color fill_color) {

		fillEllipse(x, y, rx, ry, rotation, fill_color);
		drawEllipse(x, y, rx, ry, rotation, line_color);
	}

	void BMP::drawAscii(char c, int32_t x, int32_t y, Color color, double scaleX, double scaleY) {
		ascii_dispatch(c)(*this, x, y, color, scaleX, scaleY);
	}

	void BMP::drawString(const std::string_view &str, int32_t x, int32_t y,
		Color color, double scaleX, double scaleY, int32_t interspace) {

		const auto dims = ascii_dimensions(scaleX, scaleY);
		int32_t xp = x, yp = y;
		for (char c : str) {
			switch (c) {
			case '\n':
				xp = x;
				yp += dims.y + interspace + 1;
				break;
			default:
				drawAscii(c, xp, yp, color, scaleX, scaleY);
				xp += dims.x + interspace;
				break;
			}
		}
	}

	void BMP::floodFill(int32_t x, int32_t y, const Color color) {
		Pos<int32_t> cur;
		const Color target = pixel(x, y);
		if (color == target)
			return;
		std::queue<Pos<int32_t>> to_visit{};

		drawPixel(x, y, color);
		to_visit.push({ x,y });
		while (!to_visit.empty()) {
			cur = to_visit.front();
			to_visit.pop();

			for (const auto &pos : cur.neighbors()) {
				if (validPos(pos.x, pos.y) && pixel(pos.x, pos.y) == target) {
					to_visit.push(pos);
					drawPixel(pos.x, pos.y, color);
				}
			}
		}
	}

	void BMP::fillAll(Color color) {
		std::fill(color_space.begin(), color_space.end(), color);
	}

	void BMP::fillAll(const ColorProvider &cp) {
		for (uint32_t yp = 0; yp < height(); ++yp)
			for (uint32_t xp = 0; xp < width(); ++xp)
				drawPixel(xp, yp, cp);
	}

	void BMP::clear() {
		fillAll(bgColor);
	}

	bool BMP::evenOddRule(int32_t x, int32_t y, const Poly &poly, bool include_border) {
		bool ret = false;

		for (int32_t i = 0, j = (int32_t)poly.size() - 1; i < (int32_t)poly.size(); j = i++) {
			if (x == poly[i].x && y == poly[i].y)
				return include_border;
			if ((poly[i].y > y) ^ (poly[j].y > y)) {
				const int32_t slope =
					(x - poly[i].x) * (poly[j].y - poly[i].y) -
					(y - poly[i].y) * (poly[j].x - poly[i].x);
				if (slope == 0)
					return include_border;
				if ((slope < 0) ^ (poly[j].y < poly[i].y))
					ret = !ret;
			}
		}

		return ret;
	}

	Poly BMP::rotatedRect(int32_t x0, int32_t y0, int32_t x1, int32_t y1, double rotation) {
		const double xm = (double(x1) + x0) / 2, ym = (double(y1) + y0) / 2;

		const Pos<double> rect[] = {
			Pos<double>(x0 - xm, y0 - ym).rotated(rotation),
			Pos<double>(x0 - xm, y1 - ym).rotated(rotation),
			Pos<double>(x1 - xm, y1 - ym).rotated(rotation),
			Pos<double>(x1 - xm, y0 - ym).rotated(rotation),
		};

		return {
			{ rnd(rect[0].x + xm), rnd(rect[0].y + ym) },
			{ rnd(rect[1].x + xm), rnd(rect[1].y + ym) },
			{ rnd(rect[2].x + xm), rnd(rect[2].y + ym) },
			{ rnd(rect[3].x + xm), rnd(rect[3].y + ym) },
		};
	}

	std::array<int32_t, 4> BMP::boundingRect(const Poly &poly) {
		std::array<int32_t, 4> ret{ 0,0,0,0 };

		for (const auto &p : poly) {
			ret[0] = std::min(ret[0], p.x);
			ret[1] = std::min(ret[1], p.y);
			ret[2] = std::max(ret[2], p.x);
			ret[3] = std::max(ret[3], p.y);
		}

		return ret;
	}


	Poly &Poly::interleave(const Poly &other, uint32_t skip_count) {
		std::vector<Pos<int32_t>> new_vertices{};
		const_iterator this_it = begin(), other_it = other.begin();
		bool thisHasData = true, otherHasData = true;

		while (thisHasData || otherHasData) {
			for (uint32_t i = 0; thisHasData && i < skip_count; ++i) {
				new_vertices.push_back(*this_it++);
				if (this_it == end())
					thisHasData = false;
			}
			if (otherHasData) {
				new_vertices.push_back(*other_it++);
				if (other_it == other.end())
					otherHasData = false;
			}
		}
		vertices = new_vertices;

		return *this;
	}

	Surface::Surface(std::size_t width, std::size_t height) : w(width), h(height) {
		color_space = Matrix<Color>(h, w, colors::black);
		transparency = Matrix<bool>(h, w, true);
	}

	Poly Poly::interleaved(const Poly &other, uint32_t skip_count) const {
		Poly ret = *this;
		return ret.interleave(other, skip_count);
	}

	Poly &Poly::rearrange(const std::vector<uint32_t> &order) {
		std::vector<Pos<int32_t>> new_order{ vertices.size() };
		uint32_t i = 0;

		for (auto ind : order)
			new_order[i++] = vertices[ind];
		vertices = new_order;

		return *this;
	}

	Poly Poly::rearranged(const std::vector<uint32_t> &order) const {
		Poly ret = *this;
		return ret.rearrange(order);
	}

	Poly &Poly::wrap(uint32_t times) {
		const std::size_t n = vertices.size();
		auto order = std::vector<uint32_t>(n);
		uint32_t acc = 0;

		for (std::size_t i = 0; i < n; ++i) {
			order[i] = acc;
			acc = (acc + times) % n;
		}

		return rearrange(order);
	}

	Poly Poly::wrapped(uint32_t times) const {
		Poly ret = *this;
		return ret.wrap(times);
	}

	Poly Poly::regular(int32_t x, int32_t y, int32_t r, uint32_t deg, double angle_base) {
		const double angle_inc = 2 * pi / deg;
		double angle = angle_base + pi / 2 - ((deg % 2 == 0) * (pi / deg));
		std::vector<Pos<int32_t>> pts{};

		while (deg--) {
			pts.push_back({ rnd(x + r * cos(-angle)),rnd(y + r * sin(-angle)) });
			angle += angle_inc;
		}

		return { std::move(pts) };
	}

	Poly Poly::interleaveMany(const std::vector<Poly> &poly_list) {
		const auto maxSize = std::max_element(poly_list.begin(), poly_list.end(),
			[](auto &a, auto &b) { return a.size() < b.size(); })->size();
		std::vector<Pos<int32_t>> ret{};

		for (std::size_t i = 0; i < maxSize; ++i)
			for (const auto &poly : poly_list)
				if (i < poly.size())
					ret.push_back(poly[i]);

		return { std::move(ret) };
	}
}


/*

void BMP::oldFloodFill(int32_t x, int32_t y, Color color) {
	const Color target = pixel(x, y);
	std::queue<Pos<int32_t>> to_visit{};
	std::unordered_set<Pos<int32_t>> visited{};
	Pos<int32_t> cur;

	to_visit.push({ x,y });
	visited.insert({ x,y });

	while (!to_visit.empty()) {
		cur = to_visit.front();
		to_visit.pop();

		drawPixel(cur.x, cur.y, color);
		for (const auto &pos : cur.neighbors()) {
			if (validPos(pos.x, pos.y) && visited.count(pos) == 0 && pixel(pos.x, pos.y) == target) {
				to_visit.push(pos);
				visited.insert(pos);
			}
		}
	}
}
*/
