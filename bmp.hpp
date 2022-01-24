#pragma once
#include <cstdint>
#include <istream>
#include <ostream>
#include <functional>
#include <string_view>

#include "common.hpp"
#include "matrix.hpp"
#include "colors.hpp"
#include "ascii.hpp"
#include "shapes.hpp"

namespace bmp {

	struct BitmapFileHeader {
		uint16_t bfType;
		int32_t bfSize;
		uint16_t bfReserved1;
		uint16_t bfReserved2;
		int32_t bfOffBits;

		void readFrom(std::istream &ist);
		void writeTo(std::ostream &ost) const;
	};

	struct BitmapInfoHeader {
		int32_t biSize;
		int32_t biWidth;
		int32_t biHeight;
		uint16_t biPlanes;
		uint16_t biBitCount;
		int32_t biCompression;
		int32_t biSizeImage;
		int32_t biXpelsPerMeter;
		int32_t biYpelsPerMeter;
		int32_t biCrlUses;
		int32_t biCrlImportant;

		void readFrom(std::istream &ist);
		void writeTo(std::ostream &ost) const;
	};

	class Poly {
	private:
		std::vector<Pos<int32_t>> vertices;
	public:
		using iterator = typename std::vector<Pos<int32_t>>::iterator;
		using const_iterator = typename std::vector<Pos<int32_t>>::const_iterator;

		inline Poly(std::initializer_list<Pos<int32_t>> pts) : vertices(pts) {}
		inline Poly(std::vector<Pos<int32_t>> &&pts) : vertices(pts) {}

		inline Pos<int32_t> operator[](uint32_t i) const { return vertices[i]; }
		inline std::size_t size() const { return vertices.size(); }

		inline iterator begin() { return vertices.begin(); }
		inline iterator end() { return vertices.end(); }
		inline const_iterator begin() const { return vertices.cbegin(); }
		inline const_iterator end() const { return vertices.cend(); }

		Poly& interleave(const Poly &other, uint32_t skip_count = 1);
		Poly interleaved(const Poly &other, uint32_t skip_count = 1) const;

		Poly& rearrange(const std::vector<uint32_t> &order);
		Poly rearranged(const std::vector<uint32_t> &order) const;

		Poly& wrap(uint32_t times);
		Poly wrapped(uint32_t times) const;

		static Poly regular(int32_t x, int32_t y, int32_t r, uint32_t deg, double angle_base = 0.);
		static Poly interleaveMany(const std::vector<Poly> &poly_list);
	};

	class Surface {
	private:
		std::size_t w, h;
		Matrix<Color> color_space;
		Matrix<bool> transparency;
	public:
		Surface(std::size_t width, std::size_t height);

		inline std::size_t width() const { return w; }
		inline std::size_t height() const { return h; }

		inline void set(std::size_t x, std::size_t y, Color color) {
			color_space(y, x) = color;
			transparency[y][x] = false;
		}		
		inline void reset(std::size_t x, std::size_t y) {
			transparency[y][x] = true;
		}
		inline void clear() {
			std::fill(transparency.begin(), transparency.end(), true);
		}
		inline bool hasColor(std::size_t x, std::size_t y) const {
			return !transparency[y][x];
		}
		inline Color operator()(std::size_t x, std::size_t y) const {
			return color_space(y, x);
		}
	};

	class BMP {
	private:
		BitmapFileHeader bfh;
		BitmapInfoHeader bih;
		Matrix<Color> color_space;
		Color bgColor;
		uint8_t pad_size;
	public:
		using BezierArrayQuadr = std::array<Pos<double>, 3>;
		using BezierArrayCubic = std::array<Pos<double>, 4>;
		using ParamFunc = std::function<double(double)>;

		BMP(std::istream &ist, Color bgColor = colors::white);
		BMP(std::size_t width, std::size_t height, Color bgColor = colors::white);

		inline uint32_t width() const { return bih.biWidth; }
		inline uint32_t height() const { return bih.biHeight; }
		inline Color bgcolor() const { return bgColor; }

		inline Color pixel(int32_t x, int32_t y) const { return color_space(invY(y), x); }
		inline Color &pixel(int32_t x, int32_t y) { return color_space(invY(y), x); }
		inline void drawPixel(int32_t x, int32_t y, Color color) { pixel(x, y) = color; }
		inline void drawPixel(int32_t x, int32_t y, const ColorProvider &cp) { pixel(x, y) = cp.get(x, y); }
		inline void drawPixel(int32_t x, int32_t y, Color color, uint8_t alpha) {
			pixel(x, y) = pixel(x, y).blend(color, alpha);
		}
		inline void drawPixel(int32_t x, int32_t y, const ColorProvider &cp, uint8_t alpha) {
			drawPixel(x, y, cp.get(x, y), alpha);
		}
		inline void drawPixelRound(double x, double y, Color color) {
			drawPixel(rnd(x), rnd(y), color);
		}
		inline void drawPixelRound(double x, double y, const ColorProvider &cp) {
			drawPixel(rnd(x), rnd(y), cp);
		}

		void drawShape(const shp::Shape &shape, Color color, int32_t x = 0, int32_t y = 0);
		void drawShape(const shp::Shape &shape,	const ColorProvider &prov,
			int32_t x = 0, int32_t y = 0);	
		void drawShape(const shp::Shape &shape, Color color,
			uint8_t alpha, int32_t x = 0, int32_t y = 0);
		void drawShape(const shp::Shape &shape,	const ColorProvider &prov,
			uint8_t alpha, int32_t x = 0, int32_t y = 0);

		Surface copySurface(const shp::Shape &shape, int32_t x = 0, int32_t y = 0) const;
		void pasteSurface(const Surface &surface, int32_t x, int32_t y, uint8_t alpha = 0xFF);


		void floodFill(int32_t x, int32_t y, Color color);
		void fillAll(Color color);
		void clear();

		void writeTo(std::ostream &ost) const;
		void writeTo(const std::string_view &fileName) const;


		// simplified drawing functions:

		void drawSimpleLine(int32_t x, int32_t y, int8_t dx, int8_t dy, int32_t len, Color color);
		void drawLine(int32_t x0, int32_t y0, int32_t x1, int32_t y1, Color color);
		void drawPolyline(const Poly &poly, Color color);
		void drawQuadrBezier(const BezierArrayQuadr &pts, Color color);
		void drawQuadrBezier(std::initializer_list<Pos<double>> pts, Color color);
		void drawCubicBezier(const BezierArrayCubic &pts, Color color);
		void drawCubicBezier(std::initializer_list<Pos<double>> pts, Color color);
		void drawParametric(int32_t x, int32_t y, ParamFunc xfunc, ParamFunc yfunc,
			Color color, double tmin, double tmax, double density = 8.);

		void drawRect(int32_t x0, int32_t y0, int32_t x1, int32_t y1, Color color);
		void fillRect(int32_t x0, int32_t y0, int32_t x1, int32_t y1, Color color);
		void drawFilledRect(int32_t x0, int32_t y0, int32_t x1, int32_t y1,
			Color line_color, Color fill_color);
		void drawRect(int32_t x0, int32_t y0, int32_t x1, int32_t y1, double rotation, Color color);
		void fillRect(int32_t x0, int32_t y0, int32_t x1, int32_t y1, double rotation, Color color);
		void drawFilledRect(int32_t x0, int32_t y0, int32_t x1, int32_t y1, double rotation,
			Color line_color, Color fill_color);

		void drawPolygon(const Poly &poly, Color color);
		void fillPolygon(const Poly &poly, Color color, bool include_border = true);
		void drawFilledPolygon(const Poly &poly, Color line_color, Color fill_color);

		void drawArc(int32_t x, int32_t y, int32_t rx, int32_t ry,
			double from, double to, Color color);

		void drawCircle(int32_t x, int32_t y, int32_t r, Color color);
		void fillCircle(int32_t x, int32_t y, int32_t r, Color color);
		void drawFilledCircle(int32_t x, int32_t y, int32_t r, Color line_color, Color fill_color);

		void drawEllipse(int32_t x, int32_t y, int32_t rx, int32_t ry, Color color);
		void fillEllipse(int32_t x, int32_t y, int32_t rx, int32_t ry, Color color);
		void drawFilledEllipse(int32_t x, int32_t y, int32_t rx, int32_t ry,
			Color line_color, Color fill_color);
		void drawEllipse(int32_t x, int32_t y, int32_t rx, int32_t ry, double rotation, Color color);
		void fillEllipse(int32_t x, int32_t y, int32_t rx, int32_t ry, double rotation, Color color);
		void drawFilledEllipse(int32_t x, int32_t y, int32_t rx, int32_t ry, double rotation,
			Color line_color, Color fill_color);

		void drawAscii(char c, int32_t x, int32_t y, Color color, double scaleX = 1, double scaleY = 1);
		void drawString(const std::string_view &str, int32_t x, int32_t y,
			Color color, double scaleX = 1, double scaleY = 1, int32_t interspace = 1);
	private:
		inline int32_t invY(int32_t y) const { return bih.biHeight - 1 - y; }
		inline static bool ellipse_pred_int(int32_t x, int32_t y, int32_t rx, int32_t ry) {
			return x * x * ry * ry + y * y * rx * rx < rx *rx *ry *ry;
		}
		inline static bool ellipse_pred(double x, double y, double rx, double ry) {
			return x * x / (rx * rx) + y * y / (ry * ry) <= 1;
		}
		inline bool validPos(int32_t x, int32_t y) const {
			return
				x >= 0 && y >= 0 &&
				x < bih.biWidth &&y < bih.biHeight;
		}

		void initDefaultHeaders();
		static bool evenOddRule(int32_t x, int32_t y, const Poly &poly, bool include_border = false);
		static Poly rotatedRect(int32_t x0, int32_t y0, int32_t x1, int32_t y1, double rotation);
		static std::array<int32_t, 4> boundingRect(const Poly &poly);
	};
}