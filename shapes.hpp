#pragma once
#include <cstdint>
#include <cstddef>
#include <vector>
#include <memory>
#include "common.hpp"

#include <iostream>

namespace shp {

	class Shape {
	public:
		using base_type = Pos<int32_t>;
		using iterator = GeneratorIterator<base_type>;
		using opt_type = iterator::optional;
		using interm_type = Pos<double>;
				
		inline iterator begin() const { return iterator(genFunc()); };
		inline iterator end() const { return iterator(); }
		virtual std::unique_ptr<Shape> copy() const = 0;

		inline Shape &translate(int32_t dx, int32_t dy) {
			x += dx;
			y += dy;
			return *this;
		}

		virtual ~Shape() = default;
	protected:
		constexpr static double base_density = 8.;
		int32_t x, y;

		Shape() : x(0), y(0) {};
		Shape(int32_t x, int32_t y) : x(x), y(y) {}

		virtual std::function<opt_type()> genFunc() const = 0;
	};

	class Rotatable {
	protected:
		double rotation;
	public:
		Rotatable() : rotation(0.) {}
		Rotatable(double rotation) : rotation(rotation) {}

		inline virtual void rotate(double angle) { rotation += angle; }
	};

	class RectBase : public Shape {
	protected:
		int32_t dx, dy;
	public:
		RectBase(int32_t x, int32_t y, int32_t w, int32_t h) :
			Shape(x, y), dx(w), dy(h) {}
		RectBase(base_type p0, base_type p1) :
			RectBase(p0.x, p0.y, p1.x - p0.x, p1.y - p0.y) {}
	};

	class EllipseBase : public Shape, public Rotatable {
	protected:
		int32_t rx, ry;
	public:
		EllipseBase(int32_t x, int32_t y, int32_t rx, int32_t ry, double rotation = 0.) :
			Shape(x, y), Rotatable(rotation), rx(rx), ry(ry) {}
	};

	class CircleBase : public Shape {
	protected:
		int32_t r;
	public:
		CircleBase(int32_t x, int32_t y, int32_t r) : Shape(x, y), r(r) {}
	};

	class PolyBase : public Shape, public Rotatable {
	protected:
		std::vector<interm_type> pts{};
		struct Boundary { int32_t xm, ym, xM, yM; };
	public:
		PolyBase(const std::vector<interm_type> &pts) :
			Shape(), Rotatable(), pts(pts) {}

		inline void rotate(double rotation) override {
			Rotatable::rotate(rotation);
			for (auto &p : pts)
				p = p.rotated(rotation);
		}

		Boundary boundingRect() const;
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
		std::function<opt_type()> genFunc() const override;
	};

	class Line : public Shape {
	private:
		int32_t dx, dy;
	public:
		Line(int32_t x0, int32_t y0, int32_t x1, int32_t y1) : Shape(x0, y0), dx(x1 - x0), dy(y1 - y0) {}
		Line(base_type p0, base_type p1) : Line(p0.x, p0.y, p1.x, p1.y) {}

		std::unique_ptr<Shape> copy() const override {
			return std::make_unique<Line>(*this);
		}
	private:
		std::function<opt_type()> genFunc() const override;
	};

	class Rectangle : public RectBase {
	public:
		Rectangle(int32_t x, int32_t y, int32_t w, int32_t h) :
			RectBase(x, y, w, h) {}

		std::unique_ptr<Shape> copy() const override {
			return std::make_unique<Rectangle>(*this);
		}
	private:
		std::function<opt_type()> genFunc() const override;
	};
	
	class FilledRectangle : public RectBase {
	public:
		FilledRectangle(int32_t x, int32_t y, int32_t w, int32_t h) :
			RectBase(x, y, w, h) {}

		std::unique_ptr<Shape> copy() const override {
			return std::make_unique<FilledRectangle>(*this);
		}
	private:
		std::function<opt_type()> genFunc() const override;
	};

	class Circle : public CircleBase {
	public:
		Circle(int32_t x, int32_t y, int32_t r) : CircleBase(x, y, r) {}

		std::unique_ptr<Shape> copy() const override {
			return std::make_unique<Circle>(*this);
		}
	private:
		std::function<opt_type()> genFunc() const override;
	};

	class FilledCircle : public CircleBase {
	public:
		FilledCircle(int32_t x, int32_t y, int32_t r) : CircleBase(x, y, r) {}

		std::unique_ptr<Shape> copy() const override {
			return std::make_unique<FilledCircle>(*this);
		}
	private:
		std::function<opt_type()> genFunc() const override;
	};

	class Arc : public EllipseBase {
	private:
		double angle_min, angle_max;
	public:
		Arc(int32_t x, int32_t y, int32_t rx, int32_t ry,
			double angle_min, double angle_max, double rotation) :
			EllipseBase(x, y, rx, ry, rotation), angle_min(angle_min), angle_max(angle_max) {}

		std::unique_ptr<Shape> copy() const override {
			return std::make_unique<Arc>(*this);
		}
	private:
		std::function<opt_type()> genFunc() const override;
	};

	class Ellipse : public EllipseBase {
	public:
		Ellipse(int32_t x, int32_t y, int32_t rx, int32_t ry, double rotation) :
			EllipseBase(x, y, rx, ry, rotation) {}

		std::unique_ptr<Shape> copy() const override {
			return std::make_unique<Ellipse>(*this);
		}
	private:
		std::function<opt_type()> genFunc() const override;
	};

	class FilledEllipse : public EllipseBase {
	public:
		FilledEllipse(int32_t x, int32_t y, int32_t rx, int32_t ry, double rotation) :
			EllipseBase(x, y, rx, ry, rotation) {}

		std::unique_ptr<Shape> copy() const override {
			return std::make_unique<FilledEllipse>(*this);
		}
	private:
		std::function<opt_type()> genFunc() const override;
	};

	class CompositeShape : public Shape {
	public:
		using comp_iterator = CompositeIterator<Shape::iterator>;
	private:
		std::vector<std::unique_ptr<Shape>> components{};
	public:
		CompositeShape() = default;
		CompositeShape(std::initializer_list<std::reference_wrapper<Shape>> shapes) {
			for (const auto shape : shapes)
				addShape(shape.get());
		}
		CompositeShape(const CompositeShape &other) {
			components.reserve(other.components.size());
			for (const auto &uptr : other.components)
				components.push_back(uptr->copy());
		}

		virtual void addShape(const Shape &shape) { 
			components.push_back(shape.copy());
		};

		virtual std::unique_ptr<Shape> copy() const override {
			return std::make_unique<CompositeShape>(*this);
		}

		template <typename T>
		T *get(uint32_t index) {
			return dynamic_cast<T *>(components[index].get());
		}
	private:
		comp_iterator composite() const;
		std::function<opt_type()> genFunc() const override;
	};

	class Polyline : public PolyBase {
	public:
		Polyline(const std::vector<interm_type> &pts) : PolyBase(pts) {}

		std::unique_ptr<Shape> copy() const override {
			return std::make_unique<Polyline>(*this);
		}

		virtual CompositeShape materialize() const;
	private:
		std::function<opt_type()> genFunc() const override;
	};
	
	class Polygon : public Polyline {
	public:
		Polygon(const std::vector<interm_type> &pts) : Polyline(pts) {}

		std::unique_ptr<Shape> copy() const override {
			return std::make_unique<Polygon>(*this);
		}

		virtual CompositeShape materialize() const override;
	};	

	class FilledPolygon : public PolyBase {
	public:
		FilledPolygon(const std::vector<interm_type> &pts) : PolyBase(pts) {}

		std::unique_ptr<Shape> copy() const override {
			return std::make_unique<FilledPolygon>(*this);
		}
	private:
		std::function<opt_type()> genFunc() const override;
		bool evenOddRule(int32_t x, int32_t y, bool include_border = false) const;
	};


	template <std::size_t N>
	class BezierCurve : public Shape {
	private:
		std::array<interm_type, N + 1> pts;
		std::array<int32_t, N + 1> coeffs = getCoeffs();
		double maxdist;
	public:
		BezierCurve(std::array<interm_type, N + 1> &&pts) : pts(pts) {
			initMaxDist();
		}
		BezierCurve(const std::vector<interm_type> &vec) {
			std::copy(vec.begin(), vec.begin() + N + 1, pts.begin());
			initMaxDist();
		}

		std::unique_ptr<Shape> copy() const override {
			return std::make_unique<BezierCurve>(*this);
		}
	private:
		std::function<opt_type()> genFunc() const override {
			const double step = .125 / maxdist;
			return[this, step, t = -step]() mutable->opt_type {
				if ((t += step) > 1)
					return std::nullopt;
				if (t == 0.)
					return pts.front().round<int32_t>();
				if (t == 1.)
					return pts.back().round<int32_t>();

				interm_type point{ 0,0 };
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

//class CompoundShape {
//private:
//	std::vector<std::unique_ptr<Shape>> components;
//public:
//private:
//};