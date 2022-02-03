#pragma once
#include <cstdint>
#include <cstddef>
#include <vector>
#include <memory>
#include <numeric>
#include "common.hpp"
#include "iterators.hpp"

//#include <iostream>

namespace shp {

	class Shape {
	public:
		using Point = Pos<int32_t>;
		using PointF = Pos<double>;
		using BaseIter = GeneratorIterator<Point>;
		using iterator = CompositeIterator<BaseIter>;
		using OptPoint = std::optional<Point>;
		struct Boundary {
			int32_t 
				xm = INT32_MAX, ym = INT32_MAX,
				xM = INT32_MIN, yM = INT32_MIN;

			inline Point middle() const { return { (xM + xm) / 2, (yM - ym) / 2 }; }

			Boundary operator|=(const Boundary &other) {
				xm = std::min(xm, other.xm), ym = std::min(ym, other.ym);
				xM = std::max(xM, other.xM), yM = std::max(yM, other.yM);
				return *this;
			}
		};
				
		inline iterator begin() const { return iterator(underlyingIters()); };
		inline iterator end() const { return iterator(); }
		virtual std::unique_ptr<Shape> copy() const = 0;

		virtual Boundary boundingRect() const = 0;
		virtual inline Point defaultAxis() const { return boundingRect().middle(); }

		inline Shape &translate(int32_t dx, int32_t dy) {
			x += dx;
			y += dy;
			return *this;
		}

		virtual inline Shape &rotate(double angle) {
			return rotate(angle, defaultAxis());
		}

		virtual inline Shape &rotate(double angle, Point axis) {
			const auto [px, py] = Point(x, y).rotated(angle, axis).unpack();
			x = px, y = py;
			return *this;
		}

		virtual inline std::vector<iterator::IterPair> underlyingIters() const {
			return { iterator::IterPair{ BaseIter(genFunc()), BaseIter() } };
		}

		virtual ~Shape() = default;
	protected:
		constexpr static double base_density = 8.;
		int32_t x, y;

		Shape() : x(0), y(0) {};
		Shape(int32_t x, int32_t y) : x(x), y(y) {}

		// iterator templates are dumb so this uses a raw Pointer
		static Boundary pointSeqBoundary(const PointF *data, std::size_t cnt);

		virtual std::function<OptPoint()> genFunc() const = 0;
	};

	class RectBase : public Shape {
	protected:
		int32_t dx, dy;
	public:
		RectBase(int32_t x, int32_t y, int32_t w, int32_t h) :
			Shape(x, y), dx(w), dy(h) {}
		RectBase(Point p0, Point p1) :
			RectBase(p0.x, p0.y, p1.x - p0.x, p1.y - p0.y) {}

		virtual inline Boundary boundingRect() const override { return { x,y,x+dx,y+dy }; }
	};

	class EllipseBase : public Shape {
	protected:
		int32_t rx, ry;
		double rotation;
	public:
		EllipseBase(int32_t x, int32_t y, int32_t rx, int32_t ry, double rotation = 0.) :
			Shape(x, y), rx(rx), ry(ry), rotation(rotation) {}

		virtual inline Boundary boundingRect() const override {
			int32_t maxr = std::max(rx, ry);
			return { x - maxr, y - maxr, x + maxr, y + maxr };
		}

		virtual inline EllipseBase &rotate(double angle) override {
			rotation += angle;
			return *this;
		}

		virtual inline EllipseBase &rotate(double angle, Point axis) override {
			Shape::rotate(angle, axis);
			rotation += angle;
			return *this;
		}
	};

	class CircleBase : public Shape {
	protected:
		int32_t r;
	public:
		CircleBase(int32_t x, int32_t y, int32_t r) : Shape(x, y), r(r) {}

		virtual inline Boundary boundingRect() const override {
			return { x - r, y - r, x + r, y + r };
		}
	};

	class PolyBase : public Shape {
	protected:
		std::vector<PointF> pts{};
		std::optional<Point> axis = std::nullopt;
	public:
		PolyBase(const std::vector<PointF> &pts) :
			Shape(), pts(pts) {}
		PolyBase(int32_t x, int32_t y, int32_t radius, int32_t sides);
		PolyBase(int32_t x, int32_t y, const std::vector<int32_t> &radii,
			int32_t repeats);

		PolyBase &rotate(double angle) override;
		PolyBase &rotate(double angle, Point axis) override;
		PolyBase &ravel(int32_t times);

		inline Boundary boundingRect() const override {
			return pointSeqBoundary(pts.data(), pts.size());
		};

		Point defaultAxis() const override;
	};

	class Pixel : public Shape {
	public:
		Pixel(int32_t x, int32_t y) : Shape(x, y) {}

		std::unique_ptr<Shape> copy() const override {
			return std::make_unique<Pixel>(*this);
		}

		inline Boundary boundingRect() const override { return { x,y,x,y }; }
	private:
		std::function<OptPoint()> genFunc() const override;
	};

	class SimpleLine : public Shape {
	private:
		int32_t len;
		int8_t dx, dy;
	public:
		SimpleLine(int32_t x, int32_t y, int8_t dx, int8_t dy, int32_t len) :
			Shape(x, y), dx(dx), dy(dy), len(len) {}

		std::unique_ptr<Shape> copy() const override {
			return std::make_unique<SimpleLine>(*this);
		}
	private:
		std::function<OptPoint()> genFunc() const override;

		virtual inline Boundary boundingRect() const override {
			return { 
				std::min(x, x + dx * len),
				std::min(y, y + dy * len),
				std::max(x, x + dx * len),
				std::max(y, y + dy * len),
			};
		}
	};

	class Line : public Shape {
	private:
		int32_t dx, dy;
	public:
		Line(int32_t x0, int32_t y0, int32_t x1, int32_t y1) : Shape(x0, y0), dx(x1 - x0), dy(y1 - y0) {}
		Line(Point p0, Point p1) : Line(p0.x, p0.y, p1.x, p1.y) {}

		std::unique_ptr<Shape> copy() const override {
			return std::make_unique<Line>(*this);
		}
	private:
		std::function<OptPoint()> genFunc() const override;

		virtual inline Boundary boundingRect() const override {
			return {
				std::min(x, x + dx),
				std::min(y, y + dy),
				std::max(x, x + dx),
				std::max(y, y + dy),
			};
		}
	};

	class Parametric : public Shape {
	private:
		using ParamFunc = std::function<PointF(double)>;

		double tm, tM, density, rotation = 0.;
		ParamFunc func;
	public:
		Parametric(int32_t x, int32_t y, ParamFunc func,
			double t_min, double t_max, double density = 1.) :
			Shape(x, y), func(std::move(func)), tm(t_min), tM(t_max),
			density(density) {}
		
		inline Parametric &rotate(double angle) override {
			rotation += angle;
			return *this;
		}

		inline Parametric &rotate(double angle, Point axis) override {
			Shape::rotate(angle, axis);
			rotation += angle;
			return *this;
		}

		// TODO make this return a meaningful value
		inline Boundary boundingRect() const override { return { x - 30,y - 30,x + 30,y + 30 }; }

		std::unique_ptr<Shape> copy() const override {
			return std::make_unique<Parametric>(*this);
		}
	private:
		std::function<OptPoint()> genFunc() const override;
	};

	class Rectangle : public RectBase {
	public:
		Rectangle(int32_t x, int32_t y, int32_t w, int32_t h) :
			RectBase(x, y, w, h) {}

		std::unique_ptr<Shape> copy() const override {
			return std::make_unique<Rectangle>(*this);
		}
	private:
		std::function<OptPoint()> genFunc() const override;
	};
	
	class FilledRectangle : public RectBase {
	public:
		FilledRectangle(int32_t x, int32_t y, int32_t w, int32_t h) :
			RectBase(x, y, w, h) {}

		std::unique_ptr<Shape> copy() const override {
			return std::make_unique<FilledRectangle>(*this);
		}
	private:
		std::function<OptPoint()> genFunc() const override;
	};

	class Circle : public CircleBase {
	public:
		Circle(int32_t x, int32_t y, int32_t r) : CircleBase(x, y, r) {}

		std::unique_ptr<Shape> copy() const override {
			return std::make_unique<Circle>(*this);
		}
	private:
		std::function<OptPoint()> genFunc() const override;
	};

	class FilledCircle : public CircleBase {
	public:
		FilledCircle(int32_t x, int32_t y, int32_t r) : CircleBase(x, y, r) {}

		std::unique_ptr<Shape> copy() const override {
			return std::make_unique<FilledCircle>(*this);
		}
	private:
		std::function<OptPoint()> genFunc() const override;
	};

	class Arc : public EllipseBase {
	private:
		double angle_min, angle_max;
	public:
		Arc(int32_t x, int32_t y, int32_t rx, int32_t ry,
			double angle_min, double angle_max, double rotation = 0.) :
			EllipseBase(x, y, rx, ry, rotation), angle_min(angle_min), angle_max(angle_max) {}

		std::unique_ptr<Shape> copy() const override {
			return std::make_unique<Arc>(*this);
		}
	private:
		std::function<OptPoint()> genFunc() const override;
	};

	class Ellipse : public EllipseBase {
	public:
		Ellipse(int32_t x, int32_t y, int32_t rx, int32_t ry, double rotation = 0.) :
			EllipseBase(x, y, rx, ry, rotation) {}

		std::unique_ptr<Shape> copy() const override {
			return std::make_unique<Ellipse>(*this);
		}
	private:
		std::function<OptPoint()> genFunc() const override;
	};

	class FilledEllipse : public EllipseBase {
	public:
		FilledEllipse(int32_t x, int32_t y, int32_t rx, int32_t ry, double rotation = 0.) :
			EllipseBase(x, y, rx, ry, rotation) {}

		std::unique_ptr<Shape> copy() const override {
			return std::make_unique<FilledEllipse>(*this);
		}
	private:
		std::function<OptPoint()> genFunc() const override;
	};

	class CompositeShape : public Shape {
	private:
		std::vector<std::unique_ptr<Shape>> components{};
	public:
		CompositeShape() = default;
		CompositeShape(std::vector<std::reference_wrapper<Shape>> shapes) {
			for (const auto shape : shapes)
				addShape(shape.get());
		}
		//CompositeShape(std::vector<std::unique_ptr<Shape>> &&shapes) :
		//	components(shapes) {}
		CompositeShape(const CompositeShape &other) {
			components.reserve(other.components.size());
			for (const auto &component : other.components)
				components.push_back(component->copy());
		}

		virtual inline void addShape(const Shape &shape) { 
			components.push_back(shape.copy());
		};

		virtual std::unique_ptr<Shape> copy() const override {
			return std::make_unique<CompositeShape>(*this);
		}

		Boundary boundingRect() const override;
		CompositeShape &rotate(double rotation) override;
		CompositeShape &rotate(double rotation, Point axis) override;

		inline std::vector<iterator::IterPair> underlyingIters() const override {
			std::vector<iterator::IterPair> ret{};
			for (const auto &comp : components)
				for (const auto &iterPair : comp->underlyingIters())
					ret.push_back(iterPair);
			return ret;
		}

		inline const std::vector<std::unique_ptr<Shape>> &content() const {
			return components;
		}

		template <typename T>
		T& get(uint32_t index) {
			return *dynamic_cast<T *>(components[index].get());
		}
	private:
		inline std::function<OptPoint()> genFunc() const override { return {}; }
	};

	class LineSet : public PolyBase {
	public:
		LineSet(const std::vector<PointF> &pts) :
			PolyBase(pts) {}
		LineSet(int32_t x, int32_t y, int32_t radius, int32_t sides) :
			PolyBase(x, y, radius, sides) {}
		LineSet(int32_t x, int32_t y, const std::vector<int32_t> &radii,
			int32_t repeats) : PolyBase(x, y, radii, repeats) {}

		std::unique_ptr<Shape> copy() const override {
			return std::make_unique<LineSet>(*this);
		}

		virtual std::size_t size() const;
		virtual Line part(uint32_t index) const;
	private:
		std::function<OptPoint()> genFunc() const override;
	};

	class Polyline : public LineSet {
	public:
		Polyline(const std::vector<PointF> &pts) :
			LineSet(pts) {}
		Polyline(int32_t x, int32_t y, int32_t radius, int32_t sides) :
			LineSet(x, y, radius, sides) {}
		Polyline(int32_t x, int32_t y, const std::vector<int32_t> &radii,
			int32_t repeats) : LineSet(x, y, radii, repeats) {}

		std::unique_ptr<Shape> copy() const override {
			return std::make_unique<Polyline>(*this);
		}

		std::size_t size() const override;
		Line part(uint32_t index) const override;
	};
	
	class Polygon : public LineSet {
	public:
		Polygon(const std::vector<PointF> &pts) : LineSet(pts) {}
		Polygon(int32_t x, int32_t y, int32_t radius, int32_t sides) :
			LineSet(x, y, radius, sides) {}
		Polygon(int32_t x, int32_t y, const std::vector<int32_t> &radii,
			int32_t repeats) : LineSet(x, y, radii, repeats) {}

		std::unique_ptr<Shape> copy() const override {
			return std::make_unique<Polygon>(*this);
		}

		std::size_t size() const override;
		Line part(uint32_t index) const override;
	};	

	class FilledPolygon : public PolyBase {
	public:
		FilledPolygon(const std::vector<PointF> &pts) : PolyBase(pts) {}
		FilledPolygon(int32_t x, int32_t y, int32_t radius, int32_t sides) :
			PolyBase(x, y, radius, sides) {}
		FilledPolygon(int32_t x, int32_t y, const std::vector<int32_t> &radii,
			int32_t repeats) : PolyBase(x, y, radii, repeats) {}

		std::unique_ptr<Shape> copy() const override {
			return std::make_unique<FilledPolygon>(*this);
		}
	private:
		std::function<OptPoint()> genFunc() const override;
		bool fillCondition(int32_t x, int32_t y, bool include_border = false) const;
	};

	class CharFactory;

	class Character : public CompositeShape {
	private:
		static CharFactory cf;
	public:
		const char chr;

		Character(char c, int32_t x, int32_t y, double scaleX = 1., double scaleY = 1.);
		Character(char c, const std::vector<std::reference_wrapper<Shape>> &shapes) :
			CompositeShape(shapes), chr(c) {}		

		std::unique_ptr<Shape> copy() const override {
			return std::make_unique<Character>(*this);
		}
	};

	class String : public CompositeShape {
	private:
		struct StringParams {
			int32_t x, y;
			double scaleX = 1., scaleY = 1.;
			int32_t interX = 3, interY = 3;
		};
		std::string asciiStr{};
	public:
		String() {}	
		String(std::string_view str, const StringParams &params);

		inline const std::string &str() const { return asciiStr; }
		
		// shape parameter must be an instance of Character
		void addShape(const Shape &shape) override {
			asciiStr += dynamic_cast<const Character *>(&shape)->chr;
			CompositeShape::addShape(shape);
		};

		Character& operator[](uint32_t index) {
			return get<Character>(index);
		}
	};

	template <std::size_t N>
	class BezierCurve : public Shape {
	private:
		std::array<PointF, N + 1> pts;
		std::array<int32_t, N + 1> coeffs = getCoeffs();
		double maxdist;
	public:
		BezierCurve(std::array<PointF, N + 1> &&pts) : pts(pts) {
			initMaxDist();
		}
		BezierCurve(const std::vector<PointF> &vec) {
			std::copy(vec.begin(), vec.begin() + N + 1, pts.begin());
			initMaxDist();
		}

		std::unique_ptr<Shape> copy() const override {
			return std::make_unique<BezierCurve>(*this);
		}

		BezierCurve &rotate(double angle, Point axis) override {
			for (auto &p : pts)
				p = p.rotated(angle, axis);
			return *this;
		}

		Boundary boundingRect() const override {
			return pointSeqBoundary(pts.data(), pts.size());
		}
	private:
		std::function<OptPoint()> genFunc() const override {
			const double step = 1. / (maxdist * base_density);
			return[this, step, t = -step]() mutable->OptPoint {
				if ((t += step) > 1)
					return std::nullopt;
				if (t == 0.)
					return pts.front().round<int32_t>();
				if (t == 1.)
					return pts.back().round<int32_t>();

				PointF point{ 0,0 };
				for (std::size_t i = 0; i <= N; ++i) {
					const double mult = std::pow(t, i) * std::pow(1 - t, N - i) * coeffs[i];
					point += pts[i] * mult;
				}

				return point.round<int32_t>();
			};
		}

		void initMaxDist() {
			for (std::size_t i = 1; i < N + 1; ++i)
				maxdist = std::max(maxdist, pts[i - 1].dist(pts[i]));
		}

		static constexpr std::array<int32_t, N + 1> getCoeffs() {
			std::array<int32_t, N + 1> ret{};
			ret[0] = 1;
			for (int32_t k = 1; k < N + 1; ++k)
				ret[k] = ret[k - 1] * (N + 1 - k) / k;
			return ret;
		}
	};
}
