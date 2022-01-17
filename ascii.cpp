#include <functional>
#include "bmp.hpp"
#include "ascii.hpp"

namespace bmp {
	constexpr int32_t baseSizeX = 16, baseSizeY = 20;
	using PosD = Pos<double>;

	void nonprintable(BMP &bmp, int32_t x, int32_t y, Color color, double scaleX, double scaleY) {}

	void drawChar_excl(BMP &bmp, int32_t x, int32_t y, Color color, double scaleX, double scaleY) {
		const int32_t
			x1 = round(x + baseSizeX * 0.5 * scaleX),
			y0 = y,
			y1 = round(y + baseSizeY * 1. * scaleY),
			ly = round(baseSizeY * 0.8 * scaleY);

		bmp.drawSimpleLine(x1, y0, 0, 1, ly, color);
		bmp.drawPixel(x1, y1, color);
	}

	void drawChar_quot(BMP &bmp, int32_t x, int32_t y, Color color, double scaleX, double scaleY) {
		const int32_t
			x1 = round(x + baseSizeX * 0.4 * scaleX),
			x2 = round(x + baseSizeX * 0.6 * scaleX),
			y0 = y,
			ly = round(baseSizeY * 0.2 * scaleY);

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
			x1 = round(x),
			x2 = round(x + baseSizeX * 0.25 * scaleX),
			x3 = round(x + baseSizeX * 0.5 * scaleX),
			x4 = round(x + baseSizeX * 0.75 * scaleX),
			x5 = round(x + baseSizeX * 1. * scaleX) - 1,
			y1 = round(y),
			y2 = round(y + baseSizeY * 0.55 * scaleY),
			y3 = round(y + baseSizeY * 1. * scaleY);

		bmp.drawLine(x1, y3, x3, y1, color);
		bmp.drawLine(x3, y1, x5, y3, color);
		bmp.drawLine(x2, y2, x4, y2, color);
	}

	void drawChar_B(BMP &bmp, int32_t x, int32_t y, Color color, double scaleX, double scaleY) {
		const int32_t
			x1 = round(x + baseSizeX * 0.1 * scaleX),
			x2 = round(x + baseSizeX * 1.05 * scaleX),
			x3 = round(x + baseSizeX * 1.25 * scaleX),
			y1 = round(y),
			y2 = round(y + baseSizeY * 0.47 * scaleY),
			y3 = round(y + baseSizeY * 0.5 * scaleY),
			y4 = round(y + baseSizeY * 0.53 * scaleY),
			y5 = round(y + baseSizeY * 1. * scaleY);

		bmp.drawSimpleLine(x1, y1, 0, 1, round(baseSizeY * scaleY), color);
		bmp.drawCubicBezier({ PosD(x1,y1), PosD(x2,y1), PosD(x2,y4), PosD(x1,y3) }, color);
		bmp.drawCubicBezier({ PosD(x1,y3), PosD(x3,y2), PosD(x3,y5), PosD(x1,y5) }, color);
	}

	void drawChar_C(BMP &bmp, int32_t x, int32_t y, Color color, double scaleX, double scaleY) {
		const int32_t
			rx = round(baseSizeX * 0.5 * scaleX),
			ry = round(baseSizeY * 0.5 * scaleY);

		bmp.drawArc(x + rx, y + ry, rx, ry, 0.5, 5.8, color);
	}

	void drawChar_D(BMP &bmp, int32_t x, int32_t y, Color color, double scaleX, double scaleY) {
		BMP::BezierArrayCubic arr{};
		const double
			x1 = x,
			y1 = y,
			x2 = round(x + baseSizeX * 1.2 * scaleX),
			y2 = round(y + baseSizeY * 1 * scaleY);


		bmp.drawSimpleLine(x, y, 0, 1, round(baseSizeY * scaleY), color);
		arr[0] = { x1,y1 }, arr[1] = { x2,y1 }, arr[2] = { x2,y2 }, arr[3] = { x1,y2 };
		bmp.drawCubicBezier(arr, color);
	}

	void drawChar_E(BMP &bmp, int32_t x, int32_t y, Color color, double scaleX, double scaleY) {
		const int32_t
			y1 = round(y + baseSizeY * 0.5 * scaleY),
			y2 = round(y + baseSizeY * 1. * scaleY),
			lx1 = round(baseSizeX * 1. * scaleX) - 2,
			lx2 = round(baseSizeX * 0.75 * scaleX) - 2,
			ly = round(baseSizeY * 1. * scaleY);

		bmp.drawSimpleLine(x, y, 0, 1, ly, color);
		bmp.drawSimpleLine(x, y, 1, 0, lx1, color);
		bmp.drawSimpleLine(x, y1, 1, 0, lx2, color);
		bmp.drawSimpleLine(x, y2, 1, 0, lx1, color);
	}

	void drawChar_F(BMP &bmp, int32_t x, int32_t y, Color color, double scaleX, double scaleY) {
		const int32_t
			y1 = round(y + baseSizeY * 0.5 * scaleY),
			lx1 = round(baseSizeX * 1. * scaleX) - 2,
			lx2 = round(baseSizeX * 0.75 * scaleX) - 2,
			ly = round(baseSizeY * 1. * scaleY);

		bmp.drawSimpleLine(x, y, 0, 1, ly, color);
		bmp.drawSimpleLine(x, y, 1, 0, lx1, color);
		bmp.drawSimpleLine(x, y1, 1, 0, lx2, color);
	}

	void drawChar_G(BMP &bmp, int32_t x, int32_t y, Color color, double scaleX, double scaleY) {
		const int32_t
			x1 = round(x + baseSizeX * 0.55 * scaleX),
			rx = round(baseSizeX * 0.5 * scaleX) - 1,
			ry = round(baseSizeY * 0.5 * scaleY);

		bmp.drawArc(x + rx, y + ry, rx, ry, 0.6, 6.2831, color);
		bmp.drawSimpleLine(x1, y + ry, 1, 0, round(baseSizeX * 0.3 * scaleX), color);
	}

	void drawChar_H(BMP &bmp, int32_t x, int32_t y, Color color, double scaleX, double scaleY) {
		const int32_t
			x1 = round(x + baseSizeX * 1. * scaleX) - 1,
			y1 = round(y + baseSizeY * 0.5 * scaleY),
			y2 = round(y + baseSizeY * 1. * scaleY);

		bmp.drawSimpleLine(x, y, 0, 1, y2 - y, color);
		bmp.drawSimpleLine(x1, y, 0, 1, y2 - y, color);
		bmp.drawSimpleLine(x, y1, 1, 0, x1 - x, color);
	}

	void drawChar_I(BMP &bmp, int32_t x, int32_t y, Color color, double scaleX, double scaleY) {
		const int32_t
			x1 = round(x + baseSizeX * 0.3 * scaleX),
			x2 = round(x + baseSizeX * 0.5 * scaleX),
			y1 = round(y + baseSizeY * 1. * scaleY),
			lx = round(baseSizeX * 0.4 * scaleX),
			ly = round(baseSizeY * 1. * scaleY);

		bmp.drawSimpleLine(x1, y, 1, 0, lx, color);
		bmp.drawSimpleLine(x1, y1, 1, 0, lx, color);
		bmp.drawSimpleLine(x2, y, 0, 1, ly, color);
	}

	void drawChar_J(BMP &bmp, int32_t x, int32_t y, Color color, double scaleX, double scaleY) {
		const int32_t
			x1 = round(x + baseSizeX * 1. * scaleX) - 1,
			ly = round(baseSizeY * 0.6 * scaleY),
			xm = round(x + baseSizeX * 0.5 * scaleX) - 1,
			ym = round(y + baseSizeY * 0.6 * scaleY),
			rx = round(baseSizeX * 0.5 * scaleX),
			ry = round(baseSizeY * 0.4 * scaleY);

		bmp.drawSimpleLine(x1, y, 0, 1, ly, color);
		bmp.drawArc(xm, ym, rx, ry, 3.5, 6.2831, color);
	}

	void drawChar_K(BMP &bmp, int32_t x, int32_t y, Color color, double scaleX, double scaleY) {
		const int32_t
			x1 = round(x + baseSizeX * 1. * scaleX) - 1,
			y1 = round(y + baseSizeY * 0.5 * scaleY),
			y2 = round(y + baseSizeY * 1. * scaleY),
			ly = round(baseSizeY * 1. * scaleY);

		bmp.drawSimpleLine(x, y, 0, 1, ly, color);
		bmp.drawLine(x + 1, y1, x1, y, color);
		bmp.drawLine(x + 1, y1, x1, y2, color);
	}

	void drawChar_L(BMP &bmp, int32_t x, int32_t y, Color color, double scaleX, double scaleY) {
		const int32_t
			lx = round(baseSizeX * 0.9 * scaleX) - 1,
			ly = round(baseSizeY * 1. * scaleY);

		bmp.drawSimpleLine(x, y, 0, 1, ly, color);
		bmp.drawSimpleLine(x, y + ly, 1, 0, lx, color);
	}

	void drawChar_M(BMP &bmp, int32_t x, int32_t y, Color color, double scaleX, double scaleY) {
		const int32_t
			x1 = round(x + baseSizeX * 0.5 * scaleX),
			x2 = round(x + baseSizeX * 1. * scaleX) - 1,
			y1 = round(y + baseSizeY * 0.55 * scaleY),
			ly = round(baseSizeY * 1. * scaleY);

		bmp.drawSimpleLine(x, y, 0, 1, ly, color);
		bmp.drawSimpleLine(x2, y, 0, 1, ly, color);
		bmp.drawLine(x, y, x1, y1, color);
		bmp.drawLine(x2, y, x1, y1, color);
	}

	void drawChar_N(BMP &bmp, int32_t x, int32_t y, Color color, double scaleX, double scaleY) {
		const int32_t
			x1 = round(x + baseSizeX * 1. * scaleX) - 1,
			y1 = round(y + baseSizeY * 1. * scaleY),
			ly = round(baseSizeY * 1. * scaleY);

		bmp.drawSimpleLine(x, y, 0, 1, ly, color);
		bmp.drawSimpleLine(x1, y, 0, 1, ly, color);
		bmp.drawLine(x, y, x1, y1, color);
	}

	void drawChar_O(BMP &bmp, int32_t x, int32_t y, Color color, double scaleX, double scaleY) {
		const int32_t
			rx = round(baseSizeX * 0.5 * scaleX) - 1,
			ry = round(baseSizeY * 0.5 * scaleY);

		bmp.drawEllipse(x + rx, y + ry, rx, ry, color);
	}

	void drawChar_P(BMP &bmp, int32_t x, int32_t y, Color color, double scaleX, double scaleY) {
		const int32_t
			x1 = round(x + baseSizeX * 1.05 * scaleX),
			y1 = round(y + baseSizeY * 0.55 * scaleY),
			ly = round(baseSizeY * 1. * scaleY);

		bmp.drawSimpleLine(x, y, 0, 1, ly, color);
		bmp.drawCubicBezier({ PosD(x,y), PosD(x1,y), PosD(x1,y1), PosD(x,y1) }, color);
	}

	void drawChar_Q(BMP &bmp, int32_t x, int32_t y, Color color, double scaleX, double scaleY) {
		const int32_t
			x1 = round(x + baseSizeX * 0.65 * scaleX),
			y1 = round(y + baseSizeY * 0.7 * scaleY),
			x2 = round(x + baseSizeX * 1. * scaleX) - 1,
			y2 = round(y + baseSizeY * 1. * scaleY);

		drawChar_O(bmp, x, y, color, scaleX, scaleY);
		bmp.drawLine(x1, y1, x2, y2, color);
	}

	void drawChar_R(BMP &bmp, int32_t x, int32_t y, Color color, double scaleX, double scaleY) {
		const int32_t
			x1 = round(x + baseSizeX * 0.9 * scaleX),
			y1 = round(y + baseSizeY * 0.55 * scaleY),
			y2 = round(y + baseSizeY * 1. * scaleY);

		drawChar_P(bmp, x, y, color, scaleX, scaleY);
		bmp.drawLine(x, y1, x1, y2, color);
	}

	void drawChar_S(BMP &bmp, int32_t x, int32_t y, Color color, double scaleX, double scaleY) {
		const int32_t
			rx = round(baseSizeX * 0.5 * scaleX) - 1,
			ry = round(baseSizeY * 0.5 * scaleY);
		const BMP::ParamFunc xfunc = [=](double t) { return rx * sin(2 * t); };
		const BMP::ParamFunc yfunc = [=](double t) { return ry * cos(t) * abs(cos(t)); };

		bmp.drawParametric(x + rx, y + ry, xfunc, yfunc, color, -0.7, 3.8, 4. * std::max(rx, ry));
	}

	void drawChar_T(BMP &bmp, int32_t x, int32_t y, Color color, double scaleX, double scaleY) {
		const int32_t
			x1 = round(x + baseSizeX * 0.5 * scaleX),
			lx = round(baseSizeX * 1. * scaleX) - 1,
			ly = round(baseSizeY * 1. * scaleY);

		bmp.drawSimpleLine(x, y, 1, 0, lx, color);
		bmp.drawSimpleLine(x1, y, 0, 1, ly, color);
	}

	void drawChar_U(BMP &bmp, int32_t x, int32_t y, Color color, double scaleX, double scaleY) {
		const int32_t
			ly = round(baseSizeY * 0.6 * scaleY),
			xm = round(x + (baseSizeX) * 0.5 * scaleX) - 1,
			ym = y + ly,
			rx = round((baseSizeX - 1.) * 0.5 * scaleX) - 1,
			ry = round(baseSizeY * 0.4 * scaleY);

		bmp.drawSimpleLine(x, y, 0, 1, ly, color);
		bmp.drawSimpleLine(x + 2 * rx, y, 0, 1, ly, color);
		bmp.drawArc(xm, ym, rx, ry, 3.1416, 6.2831, color);
	}

	void drawChar_V(BMP &bmp, int32_t x, int32_t y, Color color, double scaleX, double scaleY) {
		const int32_t
			x1 = round(x + baseSizeX * 0.5 * scaleX),
			x2 = round(x + baseSizeX * 1. * scaleX) - 1,
			y1 = round(y + baseSizeY * 1. * scaleY);

		bmp.drawLine(x, y, x1, y1, color);
		bmp.drawLine(x2, y, x1, y1, color);
	}

	void drawChar_W(BMP &bmp, int32_t x, int32_t y, Color color, double scaleX, double scaleY) {
		const int32_t
			x1 = round(x + baseSizeX * 0.25 * scaleX),
			x2 = round(x + baseSizeX * 0.5 * scaleX),
			x3 = round(x + baseSizeX * 0.75 * scaleX),
			x4 = round(x + baseSizeX * 1. * scaleX) - 1,
			y1 = round(y + baseSizeY * 0.4 * scaleY),
			y2 = round(y + baseSizeY * 1. * scaleY);

		bmp.drawPolyline({ {x,y},{x1,y2},{x2,y1},{x3,y2},{x4,y} }, color);
	}

	void drawChar_X(BMP &bmp, int32_t x, int32_t y, Color color, double scaleX, double scaleY) {
		const int32_t
			x1 = round(x + baseSizeX * 1. * scaleX) - 1,
			y1 = round(y + baseSizeY * 1. * scaleY);

		bmp.drawLine(x, y, x1, y1, color);
		bmp.drawLine(x1, y, x, y1, color);
	}

	void drawChar_Y(BMP &bmp, int32_t x, int32_t y, Color color, double scaleX, double scaleY) {
		const int32_t
			x1 = round(x + baseSizeX * 0.5 * scaleX),
			y1 = round(y + baseSizeY * 0.4 * scaleY),
			ly = round(baseSizeY * 0.6 * scaleY);

		drawChar_V(bmp, x, y, color, scaleX, scaleY * 0.4);
		bmp.drawSimpleLine(x1, y1, 0, 1, ly, color);
	}

	void drawChar_Z(BMP &bmp, int32_t x, int32_t y, Color color, double scaleX, double scaleY) {
		const int32_t
			lx = round(baseSizeX * 1. * scaleX) - 1,
			x1 = x + lx,
			y1 = round(y + baseSizeY * 1. * scaleY);

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
			round(baseSizeX * scaleX),
			round(baseSizeY * scaleY),
		};
	}
}