#include <functional>
#include "bmp.hpp"
#include "ascii.hpp"
#include "common.hpp"

namespace bmp {
	constexpr int32_t baseSizeX = 16, baseSizeY = 20;
	using PosD = Pos<double>;

	void nonprintable(BMP &bmp, int32_t x, int32_t y, Color color, double scaleX, double scaleY) {}

	void drawChar_excl(BMP &bmp, int32_t x, int32_t y, Color color, double scaleX, double scaleY) {
		const int32_t
			x1 = rnd(x + baseSizeX * 0.5 * scaleX),
			y0 = y,
			y1 = rnd(y + baseSizeY * 1. * scaleY),
			ly = rnd(baseSizeY * 0.8 * scaleY);

		bmp.drawSimpleLine(x1, y0, 0, 1, ly, color);
		bmp.drawPixel(x1, y1, color);
	}

	void drawChar_quot(BMP &bmp, int32_t x, int32_t y, Color color, double scaleX, double scaleY) {
		const int32_t
			x1 = rnd(x + baseSizeX * 0.4 * scaleX),
			x2 = rnd(x + baseSizeX * 0.6 * scaleX),
			y0 = y,
			ly = rnd(baseSizeY * 0.2 * scaleY);

		bmp.drawSimpleLine(x1, y0, 0, 1, ly, color);
		bmp.drawSimpleLine(x2, y0, 0, 1, ly, color);
	}

	void drawChar_hash(BMP &bmp, int32_t x, int32_t y, Color color, double scaleX, double scaleY) {}
	void drawChar_dolr(BMP &bmp, int32_t x, int32_t y, Color color, double scaleX, double scaleY) {}
	void drawChar_perc(BMP &bmp, int32_t x, int32_t y, Color color, double scaleX, double scaleY) {}
	void drawChar_amps(BMP &bmp, int32_t x, int32_t y, Color color, double scaleX, double scaleY) {}
	void drawChar_apos(BMP &bmp, int32_t x, int32_t y, Color color, double scaleX, double scaleY) {}
	void drawChar_robr(BMP &bmp, int32_t x, int32_t y, Color color, double scaleX, double scaleY) {}
	void drawChar_rcbr(BMP &bmp, int32_t x, int32_t y, Color color, double scaleX, double scaleY) {}
	void drawChar_astr(BMP &bmp, int32_t x, int32_t y, Color color, double scaleX, double scaleY) {}
	void drawChar_plus(BMP &bmp, int32_t x, int32_t y, Color color, double scaleX, double scaleY) {}
	void drawChar_comm(BMP &bmp, int32_t x, int32_t y, Color color, double scaleX, double scaleY) {}
	void drawChar_mins(BMP &bmp, int32_t x, int32_t y, Color color, double scaleX, double scaleY) {}
	void drawChar_peri(BMP &bmp, int32_t x, int32_t y, Color color, double scaleX, double scaleY) {}
	void drawChar_slsh(BMP &bmp, int32_t x, int32_t y, Color color, double scaleX, double scaleY) {}
	void drawChar_0(BMP &bmp, int32_t x, int32_t y, Color color, double scaleX, double scaleY) {}
	void drawChar_1(BMP &bmp, int32_t x, int32_t y, Color color, double scaleX, double scaleY) {}
	void drawChar_2(BMP &bmp, int32_t x, int32_t y, Color color, double scaleX, double scaleY) {}
	void drawChar_3(BMP &bmp, int32_t x, int32_t y, Color color, double scaleX, double scaleY) {}
	void drawChar_4(BMP &bmp, int32_t x, int32_t y, Color color, double scaleX, double scaleY) {}
	void drawChar_5(BMP &bmp, int32_t x, int32_t y, Color color, double scaleX, double scaleY) {}
	void drawChar_6(BMP &bmp, int32_t x, int32_t y, Color color, double scaleX, double scaleY) {}
	void drawChar_7(BMP &bmp, int32_t x, int32_t y, Color color, double scaleX, double scaleY) {}
	void drawChar_8(BMP &bmp, int32_t x, int32_t y, Color color, double scaleX, double scaleY) {}
	void drawChar_9(BMP &bmp, int32_t x, int32_t y, Color color, double scaleX, double scaleY) {}
	void drawChar_coln(BMP &bmp, int32_t x, int32_t y, Color color, double scaleX, double scaleY) {}
	void drawChar_smcl(BMP &bmp, int32_t x, int32_t y, Color color, double scaleX, double scaleY) {}
	void drawChar_less(BMP &bmp, int32_t x, int32_t y, Color color, double scaleX, double scaleY) {}
	void drawChar_equl(BMP &bmp, int32_t x, int32_t y, Color color, double scaleX, double scaleY) {}
	void drawChar_grtr(BMP &bmp, int32_t x, int32_t y, Color color, double scaleX, double scaleY) {}
	void drawChar_qstn(BMP &bmp, int32_t x, int32_t y, Color color, double scaleX, double scaleY) {}
	void drawChar_at(BMP &bmp, int32_t x, int32_t y, Color color, double scaleX, double scaleY) {}

	void drawChar_A(BMP &bmp, int32_t x, int32_t y, Color color, double scaleX, double scaleY) {
		const int32_t
			x1 = rnd(x),
			x2 = rnd(x + baseSizeX * 0.25 * scaleX),
			x3 = rnd(x + baseSizeX * 0.5 * scaleX),
			x4 = rnd(x + baseSizeX * 0.75 * scaleX),
			x5 = rnd(x + baseSizeX * 1. * scaleX) - 1,
			y1 = rnd(y),
			y2 = rnd(y + baseSizeY * 0.55 * scaleY),
			y3 = rnd(y + baseSizeY * 1. * scaleY);

		bmp.drawLine(x1, y3, x3, y1, color);
		bmp.drawLine(x3, y1, x5, y3, color);
		bmp.drawLine(x2, y2, x4, y2, color);
	}

	void drawChar_B(BMP &bmp, int32_t x, int32_t y, Color color, double scaleX, double scaleY) {
		const int32_t
			x1 = rnd(x + baseSizeX * 0.1 * scaleX),
			x2 = rnd(x + baseSizeX * 1.05 * scaleX),
			x3 = rnd(x + baseSizeX * 1.25 * scaleX),
			y1 = rnd(y),
			y2 = rnd(y + baseSizeY * 0.47 * scaleY),
			y3 = rnd(y + baseSizeY * 0.5 * scaleY),
			y4 = rnd(y + baseSizeY * 0.53 * scaleY),
			y5 = rnd(y + baseSizeY * 1. * scaleY);

		bmp.drawSimpleLine(x1, y1, 0, 1, rnd(baseSizeY * scaleY), color);
		bmp.drawCubicBezier({ PosD(x1,y1), PosD(x2,y1), PosD(x2,y4), PosD(x1,y3) }, color);
		bmp.drawCubicBezier({ PosD(x1,y3), PosD(x3,y2), PosD(x3,y5), PosD(x1,y5) }, color);
	}

	void drawChar_C(BMP &bmp, int32_t x, int32_t y, Color color, double scaleX, double scaleY) {
		const int32_t
			rx = rnd(baseSizeX * 0.5 * scaleX),
			ry = rnd(baseSizeY * 0.5 * scaleY);

		bmp.drawArc(x + rx, y + ry, rx, ry, 0.5, 5.8, color);
	}

	void drawChar_D(BMP &bmp, int32_t x, int32_t y, Color color, double scaleX, double scaleY) {
		BMP::BezierArrayCubic arr{};
		const double
			x1 = x,
			y1 = y,
			x2 = rnd(x + baseSizeX * 1.2 * scaleX),
			y2 = rnd(y + baseSizeY * 1 * scaleY);


		bmp.drawSimpleLine(x, y, 0, 1, rnd(baseSizeY * scaleY), color);
		arr[0] = { x1,y1 }, arr[1] = { x2,y1 }, arr[2] = { x2,y2 }, arr[3] = { x1,y2 };
		bmp.drawCubicBezier(arr, color);
	}

	void drawChar_E(BMP &bmp, int32_t x, int32_t y, Color color, double scaleX, double scaleY) {
		const int32_t
			y1 = rnd(y + baseSizeY * 0.5 * scaleY),
			y2 = rnd(y + baseSizeY * 1. * scaleY),
			lx1 = rnd(baseSizeX * 1. * scaleX) - 2,
			lx2 = rnd(baseSizeX * 0.75 * scaleX) - 2,
			ly = rnd(baseSizeY * 1. * scaleY);

		bmp.drawSimpleLine(x, y, 0, 1, ly, color);
		bmp.drawSimpleLine(x, y, 1, 0, lx1, color);
		bmp.drawSimpleLine(x, y1, 1, 0, lx2, color);
		bmp.drawSimpleLine(x, y2, 1, 0, lx1, color);
	}

	void drawChar_F(BMP &bmp, int32_t x, int32_t y, Color color, double scaleX, double scaleY) {
		const int32_t
			y1 = rnd(y + baseSizeY * 0.5 * scaleY),
			lx1 = rnd(baseSizeX * 1. * scaleX) - 2,
			lx2 = rnd(baseSizeX * 0.75 * scaleX) - 2,
			ly = rnd(baseSizeY * 1. * scaleY);

		bmp.drawSimpleLine(x, y, 0, 1, ly, color);
		bmp.drawSimpleLine(x, y, 1, 0, lx1, color);
		bmp.drawSimpleLine(x, y1, 1, 0, lx2, color);
	}

	void drawChar_G(BMP &bmp, int32_t x, int32_t y, Color color, double scaleX, double scaleY) {
		const int32_t
			x1 = rnd(x + baseSizeX * 0.55 * scaleX),
			rx = rnd(baseSizeX * 0.5 * scaleX) - 1,
			ry = rnd(baseSizeY * 0.5 * scaleY);

		bmp.drawArc(x + rx, y + ry, rx, ry, 0.6, 6.2831, color);
		bmp.drawSimpleLine(x1, y + ry, 1, 0, rnd(baseSizeX * 0.3 * scaleX), color);
	}

	void drawChar_H(BMP &bmp, int32_t x, int32_t y, Color color, double scaleX, double scaleY) {
		const int32_t
			x1 = rnd(x + baseSizeX * 1. * scaleX) - 1,
			y1 = rnd(y + baseSizeY * 0.5 * scaleY),
			y2 = rnd(y + baseSizeY * 1. * scaleY);

		bmp.drawSimpleLine(x, y, 0, 1, y2 - y, color);
		bmp.drawSimpleLine(x1, y, 0, 1, y2 - y, color);
		bmp.drawSimpleLine(x, y1, 1, 0, x1 - x, color);
	}

	void drawChar_I(BMP &bmp, int32_t x, int32_t y, Color color, double scaleX, double scaleY) {
		const int32_t
			x1 = rnd(x + baseSizeX * 0.3 * scaleX),
			x2 = rnd(x + baseSizeX * 0.5 * scaleX),
			y1 = rnd(y + baseSizeY * 1. * scaleY),
			lx = rnd(baseSizeX * 0.4 * scaleX),
			ly = rnd(baseSizeY * 1. * scaleY);

		bmp.drawSimpleLine(x1, y, 1, 0, lx, color);
		bmp.drawSimpleLine(x1, y1, 1, 0, lx, color);
		bmp.drawSimpleLine(x2, y, 0, 1, ly, color);
	}

	void drawChar_J(BMP &bmp, int32_t x, int32_t y, Color color, double scaleX, double scaleY) {
		const int32_t
			x1 = rnd(x + baseSizeX * 1. * scaleX) - 1,
			ly = rnd(baseSizeY * 0.6 * scaleY),
			xm = rnd(x + baseSizeX * 0.5 * scaleX) - 1,
			ym = rnd(y + baseSizeY * 0.6 * scaleY),
			rx = rnd(baseSizeX * 0.5 * scaleX),
			ry = rnd(baseSizeY * 0.4 * scaleY);

		bmp.drawSimpleLine(x1, y, 0, 1, ly, color);
		bmp.drawArc(xm, ym, rx, ry, 3.5, 6.2831, color);
	}

	void drawChar_K(BMP &bmp, int32_t x, int32_t y, Color color, double scaleX, double scaleY) {
		const int32_t
			x1 = rnd(x + baseSizeX * 1. * scaleX) - 1,
			y1 = rnd(y + baseSizeY * 0.5 * scaleY),
			y2 = rnd(y + baseSizeY * 1. * scaleY),
			ly = rnd(baseSizeY * 1. * scaleY);

		bmp.drawSimpleLine(x, y, 0, 1, ly, color);
		bmp.drawLine(x + 1, y1, x1, y, color);
		bmp.drawLine(x + 1, y1, x1, y2, color);
	}

	void drawChar_L(BMP &bmp, int32_t x, int32_t y, Color color, double scaleX, double scaleY) {
		const int32_t
			lx = rnd(baseSizeX * 0.9 * scaleX) - 1,
			ly = rnd(baseSizeY * 1. * scaleY);

		bmp.drawSimpleLine(x, y, 0, 1, ly, color);
		bmp.drawSimpleLine(x, y + ly, 1, 0, lx, color);
	}

	void drawChar_M(BMP &bmp, int32_t x, int32_t y, Color color, double scaleX, double scaleY) {
		const int32_t
			x1 = rnd(x + baseSizeX * 0.5 * scaleX),
			x2 = rnd(x + baseSizeX * 1. * scaleX) - 1,
			y1 = rnd(y + baseSizeY * 0.55 * scaleY),
			ly = rnd(baseSizeY * 1. * scaleY);

		bmp.drawSimpleLine(x, y, 0, 1, ly, color);
		bmp.drawSimpleLine(x2, y, 0, 1, ly, color);
		bmp.drawLine(x, y, x1, y1, color);
		bmp.drawLine(x2, y, x1, y1, color);
	}

	void drawChar_N(BMP &bmp, int32_t x, int32_t y, Color color, double scaleX, double scaleY) {
		const int32_t
			x1 = rnd(x + baseSizeX * 1. * scaleX) - 1,
			y1 = rnd(y + baseSizeY * 1. * scaleY),
			ly = rnd(baseSizeY * 1. * scaleY);

		bmp.drawSimpleLine(x, y, 0, 1, ly, color);
		bmp.drawSimpleLine(x1, y, 0, 1, ly, color);
		bmp.drawLine(x, y, x1, y1, color);
	}

	void drawChar_O(BMP &bmp, int32_t x, int32_t y, Color color, double scaleX, double scaleY) {
		const int32_t
			rx = rnd(baseSizeX * 0.5 * scaleX) - 1,
			ry = rnd(baseSizeY * 0.5 * scaleY);

		bmp.drawEllipse(x + rx, y + ry, rx, ry, color);
	}

	void drawChar_P(BMP &bmp, int32_t x, int32_t y, Color color, double scaleX, double scaleY) {
		const int32_t
			x1 = rnd(x + baseSizeX * 1.05 * scaleX),
			y1 = rnd(y + baseSizeY * 0.55 * scaleY),
			ly = rnd(baseSizeY * 1. * scaleY);

		bmp.drawSimpleLine(x, y, 0, 1, ly, color);
		bmp.drawCubicBezier({ PosD(x,y), PosD(x1,y), PosD(x1,y1), PosD(x,y1) }, color);
	}

	void drawChar_Q(BMP &bmp, int32_t x, int32_t y, Color color, double scaleX, double scaleY) {
		const int32_t
			x1 = rnd(x + baseSizeX * 0.65 * scaleX),
			y1 = rnd(y + baseSizeY * 0.7 * scaleY),
			x2 = rnd(x + baseSizeX * 1. * scaleX) - 1,
			y2 = rnd(y + baseSizeY * 1. * scaleY);

		drawChar_O(bmp, x, y, color, scaleX, scaleY);
		bmp.drawLine(x1, y1, x2, y2, color);
	}

	void drawChar_R(BMP &bmp, int32_t x, int32_t y, Color color, double scaleX, double scaleY) {
		const int32_t
			x1 = rnd(x + baseSizeX * 0.9 * scaleX),
			y1 = rnd(y + baseSizeY * 0.55 * scaleY),
			y2 = rnd(y + baseSizeY * 1. * scaleY);

		drawChar_P(bmp, x, y, color, scaleX, scaleY);
		bmp.drawLine(x, y1, x1, y2, color);
	}

	void drawChar_S(BMP &bmp, int32_t x, int32_t y, Color color, double scaleX, double scaleY) {
		const int32_t
			rx = rnd(baseSizeX * 0.5 * scaleX) - 1,
			ry = rnd(baseSizeY * 0.5 * scaleY);
		const BMP::ParamFunc xfunc = [=](double t) { return rx * sin(2 * t); };
		const BMP::ParamFunc yfunc = [=](double t) { return ry * cos(t) * abs(cos(t)); };

		bmp.drawParametric(x + rx, y + ry, xfunc, yfunc, color, -0.7, 3.8, 4. * std::max(rx, ry));
	}

	void drawChar_T(BMP &bmp, int32_t x, int32_t y, Color color, double scaleX, double scaleY) {
		const int32_t
			x1 = rnd(x + baseSizeX * 0.5 * scaleX),
			lx = rnd(baseSizeX * 1. * scaleX) - 1,
			ly = rnd(baseSizeY * 1. * scaleY);

		bmp.drawSimpleLine(x, y, 1, 0, lx, color);
		bmp.drawSimpleLine(x1, y, 0, 1, ly, color);
	}

	void drawChar_U(BMP &bmp, int32_t x, int32_t y, Color color, double scaleX, double scaleY) {
		const int32_t
			ly = rnd(baseSizeY * 0.6 * scaleY),
			xm = rnd(x + (baseSizeX) * 0.5 * scaleX) - 1,
			ym = y + ly,
			rx = rnd((baseSizeX - 1.) * 0.5 * scaleX) - 1,
			ry = rnd(baseSizeY * 0.4 * scaleY);

		bmp.drawSimpleLine(x, y, 0, 1, ly, color);
		bmp.drawSimpleLine(x + 2 * rx, y, 0, 1, ly, color);
		bmp.drawArc(xm, ym, rx, ry, 3.1416, 6.2831, color);
	}

	void drawChar_V(BMP &bmp, int32_t x, int32_t y, Color color, double scaleX, double scaleY) {
		const int32_t
			x1 = rnd(x + baseSizeX * 0.5 * scaleX),
			x2 = rnd(x + baseSizeX * 1. * scaleX) - 1,
			y1 = rnd(y + baseSizeY * 1. * scaleY);

		bmp.drawLine(x, y, x1, y1, color);
		bmp.drawLine(x2, y, x1, y1, color);
	}

	void drawChar_W(BMP &bmp, int32_t x, int32_t y, Color color, double scaleX, double scaleY) {
		const int32_t
			x1 = rnd(x + baseSizeX * 0.25 * scaleX),
			x2 = rnd(x + baseSizeX * 0.5 * scaleX),
			x3 = rnd(x + baseSizeX * 0.75 * scaleX),
			x4 = rnd(x + baseSizeX * 1. * scaleX) - 1,
			y1 = rnd(y + baseSizeY * 0.4 * scaleY),
			y2 = rnd(y + baseSizeY * 1. * scaleY);

		bmp.drawPolyline({ {x,y},{x1,y2},{x2,y1},{x3,y2},{x4,y} }, color);
	}

	void drawChar_X(BMP &bmp, int32_t x, int32_t y, Color color, double scaleX, double scaleY) {
		const int32_t
			x1 = rnd(x + baseSizeX * 1. * scaleX) - 1,
			y1 = rnd(y + baseSizeY * 1. * scaleY);

		bmp.drawLine(x, y, x1, y1, color);
		bmp.drawLine(x1, y, x, y1, color);
	}

	void drawChar_Y(BMP &bmp, int32_t x, int32_t y, Color color, double scaleX, double scaleY) {
		const int32_t
			x1 = rnd(x + baseSizeX * 0.5 * scaleX),
			y1 = rnd(y + baseSizeY * 0.4 * scaleY),
			ly = rnd(baseSizeY * 0.6 * scaleY);

		drawChar_V(bmp, x, y, color, scaleX, scaleY * 0.4);
		bmp.drawSimpleLine(x1, y1, 0, 1, ly, color);
	}

	void drawChar_Z(BMP &bmp, int32_t x, int32_t y, Color color, double scaleX, double scaleY) {
		const int32_t
			lx = rnd(baseSizeX * 1. * scaleX) - 1,
			x1 = x + lx,
			y1 = rnd(y + baseSizeY * 1. * scaleY);

		bmp.drawSimpleLine(x, y, 1, 0, lx, color);
		bmp.drawSimpleLine(x, y1, 1, 0, lx, color);
		bmp.drawLine(x1, y, x, y1, color);
	}

	void drawChar_sqob(BMP &bmp, int32_t x, int32_t y, Color color, double scaleX, double scaleY) {}
	void drawChar_bslh(BMP &bmp, int32_t x, int32_t y, Color color, double scaleX, double scaleY) {}
	void drawChar_sqcb(BMP &bmp, int32_t x, int32_t y, Color color, double scaleX, double scaleY) {}
	void drawChar_chev(BMP &bmp, int32_t x, int32_t y, Color color, double scaleX, double scaleY) {}
	void drawChar_unds(BMP &bmp, int32_t x, int32_t y, Color color, double scaleX, double scaleY) {}
	void drawChar_bqte(BMP &bmp, int32_t x, int32_t y, Color color, double scaleX, double scaleY) {}
	void drawChar_a(BMP &bmp, int32_t x, int32_t y, Color color, double scaleX, double scaleY) {}
	void drawChar_b(BMP &bmp, int32_t x, int32_t y, Color color, double scaleX, double scaleY) {}
	void drawChar_c(BMP &bmp, int32_t x, int32_t y, Color color, double scaleX, double scaleY) {}
	void drawChar_d(BMP &bmp, int32_t x, int32_t y, Color color, double scaleX, double scaleY) {}
	void drawChar_e(BMP &bmp, int32_t x, int32_t y, Color color, double scaleX, double scaleY) {}
	void drawChar_f(BMP &bmp, int32_t x, int32_t y, Color color, double scaleX, double scaleY) {}
	void drawChar_g(BMP &bmp, int32_t x, int32_t y, Color color, double scaleX, double scaleY) {}
	void drawChar_h(BMP &bmp, int32_t x, int32_t y, Color color, double scaleX, double scaleY) {}
	void drawChar_i(BMP &bmp, int32_t x, int32_t y, Color color, double scaleX, double scaleY) {}
	void drawChar_j(BMP &bmp, int32_t x, int32_t y, Color color, double scaleX, double scaleY) {}
	void drawChar_k(BMP &bmp, int32_t x, int32_t y, Color color, double scaleX, double scaleY) {}
	void drawChar_l(BMP &bmp, int32_t x, int32_t y, Color color, double scaleX, double scaleY) {}
	void drawChar_m(BMP &bmp, int32_t x, int32_t y, Color color, double scaleX, double scaleY) {}
	void drawChar_n(BMP &bmp, int32_t x, int32_t y, Color color, double scaleX, double scaleY) {}
	void drawChar_o(BMP &bmp, int32_t x, int32_t y, Color color, double scaleX, double scaleY) {}
	void drawChar_p(BMP &bmp, int32_t x, int32_t y, Color color, double scaleX, double scaleY) {}
	void drawChar_q(BMP &bmp, int32_t x, int32_t y, Color color, double scaleX, double scaleY) {}
	void drawChar_r(BMP &bmp, int32_t x, int32_t y, Color color, double scaleX, double scaleY) {}
	void drawChar_s(BMP &bmp, int32_t x, int32_t y, Color color, double scaleX, double scaleY) {}
	void drawChar_t(BMP &bmp, int32_t x, int32_t y, Color color, double scaleX, double scaleY) {}
	void drawChar_u(BMP &bmp, int32_t x, int32_t y, Color color, double scaleX, double scaleY) {}
	void drawChar_v(BMP &bmp, int32_t x, int32_t y, Color color, double scaleX, double scaleY) {}
	void drawChar_w(BMP &bmp, int32_t x, int32_t y, Color color, double scaleX, double scaleY) {}
	void drawChar_x(BMP &bmp, int32_t x, int32_t y, Color color, double scaleX, double scaleY) {}
	void drawChar_y(BMP &bmp, int32_t x, int32_t y, Color color, double scaleX, double scaleY) {}
	void drawChar_z(BMP &bmp, int32_t x, int32_t y, Color color, double scaleX, double scaleY) {}
	void drawChar_cobr(BMP &bmp, int32_t x, int32_t y, Color color, double scaleX, double scaleY) {}
	void drawChar_pipe(BMP &bmp, int32_t x, int32_t y, Color color, double scaleX, double scaleY) {}
	void drawChar_ccbr(BMP &bmp, int32_t x, int32_t y, Color color, double scaleX, double scaleY) {}
	void drawChar_tild(BMP &bmp, int32_t x, int32_t y, Color color, double scaleX, double scaleY) {}

	const TextFunc funcs[] = {
		nullptr,       // NUL
		nonprintable,  // SOH
		nonprintable,  // STX
		nonprintable,  // ETX
		nonprintable,  // EOT
		nonprintable,  // ENQ
		nonprintable,  // ACK
		nonprintable,  // BEL
		nonprintable,  // BS
		nonprintable,  // HT
		nonprintable,  // LF
		nonprintable,  // VT
		nonprintable,  // FF
		nonprintable,  // CR
		nonprintable,  // SO
		nonprintable,  // SI
		nonprintable,  // DLE
		nonprintable,  // DC1
		nonprintable,  // DC2
		nonprintable,  // DC3
		nonprintable,  // DC4
		nonprintable,  // NAK
		nonprintable,  // SYN
		nonprintable,  // ETB
		nonprintable,  // CAN
		nonprintable,  // EM
		nonprintable,  // SUB
		nonprintable,  // ESC
		nonprintable,  // FS
		nonprintable,  // GS
		nonprintable,  // RS
		nonprintable,  // US
		nonprintable,  // SPACE
		drawChar_excl, // !
		drawChar_quot, // "
		drawChar_hash, // #
		drawChar_dolr, // $
		drawChar_perc, // %
		drawChar_amps, // &
		drawChar_apos, // '
		drawChar_robr, // (
		drawChar_rcbr, // )
		drawChar_astr, // *
		drawChar_plus, // +
		drawChar_comm, // ,
		drawChar_mins, // -
		drawChar_peri, // .
		drawChar_slsh, // /
		drawChar_0,	   // 0
		drawChar_1,	   // 1
		drawChar_2,	   // 2
		drawChar_3,	   // 3
		drawChar_4,	   // 4
		drawChar_5,	   // 5
		drawChar_6,	   // 6
		drawChar_7,	   // 7
		drawChar_8,	   // 8
		drawChar_9,	   // 9
		drawChar_coln, // :
		drawChar_smcl, // ;
		drawChar_less, // <
		drawChar_equl, // =
		drawChar_grtr, // >
		drawChar_qstn, // ?
		drawChar_at,   // @
		drawChar_A,    // A
		drawChar_B,    // B
		drawChar_C,    // C
		drawChar_D,    // D
		drawChar_E,    // E
		drawChar_F,    // F
		drawChar_G,    // G
		drawChar_H,    // H
		drawChar_I,    // I
		drawChar_J,    // J
		drawChar_K,    // K
		drawChar_L,    // L
		drawChar_M,    // M
		drawChar_N,    // N
		drawChar_O,    // O
		drawChar_P,    // P
		drawChar_Q,    // Q
		drawChar_R,    // R
		drawChar_S,    // S
		drawChar_T,    // T
		drawChar_U,    // U
		drawChar_V,    // V
		drawChar_W,    // W
		drawChar_X,    // X
		drawChar_Y,    // Y
		drawChar_Z,    // Z
		drawChar_sqob, // [
		drawChar_bslh, // \ 
		drawChar_sqcb, // ]
		drawChar_chev, // ^
		drawChar_unds, // _
		drawChar_bqte, // `
		drawChar_a,    // a
		drawChar_b,    // b
		drawChar_c,    // c
		drawChar_d,    // d
		drawChar_e,    // e
		drawChar_f,    // f
		drawChar_g,    // g
		drawChar_h,    // h
		drawChar_i,    // i
		drawChar_j,    // j
		drawChar_k,    // k
		drawChar_l,    // l
		drawChar_m,    // m
		drawChar_n,    // n
		drawChar_o,    // o
		drawChar_p,    // p
		drawChar_q,    // q
		drawChar_r,    // r
		drawChar_s,    // s
		drawChar_t,    // t
		drawChar_u,    // u
		drawChar_v,    // v
		drawChar_w,    // w
		drawChar_x,    // x
		drawChar_y,    // y
		drawChar_z,    // z
		drawChar_cobr, // {
		drawChar_pipe, // |
		drawChar_ccbr, // }
		drawChar_tild, // ~
	};

	TextFunc ascii_dispatch(char c) {
		return funcs[c];
	}

	Pos<int32_t> ascii_dimensions(double scaleX, double scaleY) {
		return {
			rnd(baseSizeX * scaleX),
			rnd(baseSizeY * scaleY),
		};
	}
}

namespace shp {
	Character CharFactory::make(char c, int32_t x, int32_t y, double scaleX, double scaleY) {
		xyf.setParams(x, y, scaleX, scaleY);
		return dispatch(c);
	}

	Character CharFactory::dispatch(char c) {
		switch (c) {
			case '!': return make_excl();
			case '"': return make_quot();
			case '#': return make_hash();
			case '$': return make_dolr();
			case '%': return make_perc();
			case '&': return make_amps();
			case '\'':return make_apos();
			case '(': return make_robr();
			case ')': return make_rcbr();
			case '*': return make_astr();
			case '+': return make_plus();
			case ',': return make_comm();
			case '-': return make_mins();
			case '.': return make_peri();
			case '/': return make_slsh();
			case '0': return make_0();
			case '1': return make_1();
			case '2': return make_2();
			case '3': return make_3();
			case '4': return make_4();
			case '5': return make_5();
			case '6': return make_6();
			case '7': return make_7();
			case '8': return make_8();
			case '9': return make_9();
			case ':': return make_coln();
			case ';': return make_smcl();
			case '<': return make_less();
			case '=': return make_equl();
			case '>': return make_grtr();
			case '?': return make_qstn();
			case '@': return make_at();
			case 'A': return make_A();
			case 'B': return make_B();
			case 'C': return make_C();
			case 'D': return make_D();
			case 'E': return make_E();
			case 'F': return make_F();
			case 'G': return make_G();
			case 'H': return make_H();
			case 'I': return make_I();
			case 'J': return make_J();
			case 'K': return make_K();
			case 'L': return make_L();
			case 'M': return make_M();
			case 'N': return make_N();
			case 'O': return make_O();
			case 'P': return make_P();
			case 'Q': return make_Q();
			case 'R': return make_R();
			case 'S': return make_S();
			case 'T': return make_T();
			case 'U': return make_U();
			case 'V': return make_V();
			case 'W': return make_W();
			case 'X': return make_X();
			case 'Y': return make_Y();
			case 'Z': return make_Z();
			case '[': return make_sqob();
			case '\\':return make_bslh();
			case ']': return make_sqcb();
			case '^': return make_chev();
			case '_': return make_unds();
			case '`': return make_bqte();
			case 'a': return make_a();
			case 'b': return make_b();
			case 'c': return make_c();
			case 'd': return make_d();
			case 'e': return make_e();
			case 'f': return make_f();
			case 'g': return make_g();
			case 'h': return make_h();
			case 'i': return make_i();
			case 'j': return make_j();
			case 'k': return make_k();
			case 'l': return make_l();
			case 'm': return make_m();
			case 'n': return make_n();
			case 'o': return make_o();
			case 'p': return make_p();
			case 'q': return make_q();
			case 'r': return make_r();
			case 's': return make_s();
			case 't': return make_t();
			case 'u': return make_u();
			case 'v': return make_v();
			case 'w': return make_w();
			case 'x': return make_x();
			case 'y': return make_y();
			case 'z': return make_z();
			case '{': return make_cobr();
			case '|': return make_pipe();
			case '}': return make_ccbr();
			case '~': return make_tild();
			default: return { c,{} };
		}
	}


	Character CharFactory::make_excl() { return {'\0', {}}; }
	Character CharFactory::make_quot() { return {'\0', {}}; }
	Character CharFactory::make_hash() { return {'\0', {}}; }
	Character CharFactory::make_dolr() { return {'\0', {}}; }
	Character CharFactory::make_perc() { return {'\0', {}}; }
	Character CharFactory::make_amps() { return {'\0', {}}; }
	Character CharFactory::make_apos() { return {'\0', {}}; }
	Character CharFactory::make_robr() { return {'\0', {}}; }
	Character CharFactory::make_rcbr() { return {'\0', {}}; }
	Character CharFactory::make_astr() { return {'\0', {}}; }
	Character CharFactory::make_plus() { return {'\0', {}}; }
	Character CharFactory::make_comm() { return {'\0', {}}; }
	Character CharFactory::make_mins() { return {'\0', {}}; }
	Character CharFactory::make_peri() { return {'\0', {}}; }
	Character CharFactory::make_slsh() { return {'\0', {}}; }
	Character CharFactory::make_0() { return {'\0', {}}; }
	Character CharFactory::make_1() { return {'\0', {}}; }
	Character CharFactory::make_2() { return {'\0', {}}; }
	Character CharFactory::make_3() { return {'\0', {}}; }
	Character CharFactory::make_4() { return {'\0', {}}; }
	Character CharFactory::make_5() { return {'\0', {}}; }
	Character CharFactory::make_6() { return {'\0', {}}; }
	Character CharFactory::make_7() { return {'\0', {}}; }
	Character CharFactory::make_8() { return {'\0', {}}; }
	Character CharFactory::make_9() { return {'\0', {}}; }
	Character CharFactory::make_coln() { return {'\0', {}}; }
	Character CharFactory::make_smcl() { return {'\0', {}}; }
	Character CharFactory::make_less() { return {'\0', {}}; }
	Character CharFactory::make_equl() { return {'\0', {}}; }
	Character CharFactory::make_grtr() { return {'\0', {}}; }
	Character CharFactory::make_qstn() { return {'\0', {}}; }
	Character CharFactory::make_at() { return {'\0', {}}; }
	Character CharFactory::make_A() {
		xyf.setGrid(4, 20);
		Polyline s1{ { xyf.p(0,20), xyf.p(2,0), xyf.p(4,20) } };
		Polyline s2{ { xyf.p(1,11), xyf.p(3,11) } };
		return Character{ 'A', {s1,s2} };
		//Character ret = { 'A',{} };
		//ret.addShape(s1);
		//ret.addShape(s2);
		//return ret;
	}
	Character CharFactory::make_B() { return {'\0', {}}; }
	Character CharFactory::make_C() { return {'\0', {}}; }
	Character CharFactory::make_D() { return {'\0', {}}; }
	Character CharFactory::make_E() { return {'\0', {}}; }
	Character CharFactory::make_F() { return {'\0', {}}; }
	Character CharFactory::make_G() { return {'\0', {}}; }
	Character CharFactory::make_H() { return {'\0', {}}; }
	Character CharFactory::make_I() { return {'\0', {}}; }
	Character CharFactory::make_J() { return {'\0', {}}; }
	Character CharFactory::make_K() { return {'\0', {}}; }
	Character CharFactory::make_L() { return {'\0', {}}; }
	Character CharFactory::make_M() { return {'\0', {}}; }
	Character CharFactory::make_N() { return {'\0', {}}; }
	Character CharFactory::make_O() { return {'\0', {}}; }
	Character CharFactory::make_P() { return {'\0', {}}; }
	Character CharFactory::make_Q() { return {'\0', {}}; }
	Character CharFactory::make_R() { return {'\0', {}}; }
	Character CharFactory::make_S() { return {'\0', {}}; }
	Character CharFactory::make_T() { return {'\0', {}}; }
	Character CharFactory::make_U() { return {'\0', {}}; }
	Character CharFactory::make_V() { return {'\0', {}}; }
	Character CharFactory::make_W() { return {'\0', {}}; }
	Character CharFactory::make_X() { return {'\0', {}}; }
	Character CharFactory::make_Y() { return {'\0', {}}; }
	Character CharFactory::make_Z() { return {'\0', {}}; }
	Character CharFactory::make_sqob() { return {'\0', {}}; }
	Character CharFactory::make_bslh() { return {'\0', {}}; }
	Character CharFactory::make_sqcb() { return {'\0', {}}; }
	Character CharFactory::make_chev() { return {'\0', {}}; }
	Character CharFactory::make_unds() { return {'\0', {}}; }
	Character CharFactory::make_bqte() { return {'\0', {}}; }
	Character CharFactory::make_a() { return {'\0', {}}; }
	Character CharFactory::make_b() { return {'\0', {}}; }
	Character CharFactory::make_c() { return {'\0', {}}; }
	Character CharFactory::make_d() { return {'\0', {}}; }
	Character CharFactory::make_e() { return {'\0', {}}; }
	Character CharFactory::make_f() { return {'\0', {}}; }
	Character CharFactory::make_g() { return {'\0', {}}; }
	Character CharFactory::make_h() { return {'\0', {}}; }
	Character CharFactory::make_i() { return {'\0', {}}; }
	Character CharFactory::make_j() { return {'\0', {}}; }
	Character CharFactory::make_k() { return {'\0', {}}; }
	Character CharFactory::make_l() { return {'\0', {}}; }
	Character CharFactory::make_m() { return {'\0', {}}; }
	Character CharFactory::make_n() { return {'\0', {}}; }
	Character CharFactory::make_o() { return {'\0', {}}; }
	Character CharFactory::make_p() { return {'\0', {}}; }
	Character CharFactory::make_q() { return {'\0', {}}; }
	Character CharFactory::make_r() { return {'\0', {}}; }
	Character CharFactory::make_s() { return {'\0', {}}; }
	Character CharFactory::make_t() { return {'\0', {}}; }
	Character CharFactory::make_u() { return {'\0', {}}; }
	Character CharFactory::make_v() { return {'\0', {}}; }
	Character CharFactory::make_w() { return {'\0', {}}; }
	Character CharFactory::make_x() { return {'\0', {}}; }
	Character CharFactory::make_y() { return {'\0', {}}; }
	Character CharFactory::make_z() { return {'\0', {}}; }
	Character CharFactory::make_cobr() { return {'\0', {}}; }
	Character CharFactory::make_pipe() { return {'\0', {}}; }
	Character CharFactory::make_ccbr() { return {'\0', {}}; }
	Character CharFactory::make_tild() { return { '\0', {} }; }
}