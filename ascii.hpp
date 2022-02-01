#pragma once
#include "common.hpp"
#include "shapes.hpp"

namespace bmp {
	class BMP;

	using TextFunc = std::function<void(BMP &, int32_t, int32_t, Color, double, double)>;

	TextFunc ascii_dispatch(char c);
	Pos<int32_t> ascii_dimensions(double scaleX, double scaleY);
}

namespace shp {
	class XYFactory {
	public:
		static constexpr int32_t baseSizeX = 16, baseSizeY = 20;
		int32_t baseX = 0, baseY = 0, gridXSize = 1, gridYSize = 1;
		double scaleX = 1., scaleY = 1.;

		inline void setParams(int32_t bx, int32_t by, double sx, double sy) {
			baseX = bx;	baseY = by;	scaleX = sx; scaleY = sy;
		}
		inline void setGrid(int32_t sizeX, int32_t sizeY) {
			gridXSize = sizeX; gridYSize = sizeY;
		}

		inline double x(double frac) const { return baseX + baseSizeX * scaleX * frac; }
		inline double y(double frac) const { return baseY + baseSizeY * scaleY * frac; }
		inline double lx(double frac) const { return baseSizeX * scaleX * frac; }
		inline double ly(double frac) const { return baseSizeY * scaleY * frac; }
		inline double lx(double frac1, double frac2) const { return lx(frac2 - frac1); }
		inline double ly(double frac1, double frac2) const { return ly(frac2 - frac1); }
		inline double gx(double gridX) const { return x(gridX / gridXSize); }
		inline double gy(double gridY) const { return y(gridY / gridYSize); }
		inline double glx(double gridX) const { return lx(gridX / gridXSize); }
		inline double gly(double gridY) const { return ly(gridY / gridYSize); }
		inline double glx(double gridX1, double gridX2) const { return glx(gridX2 - gridX1); }
		inline double gly(double gridY1, double gridY2) const { return gly(gridY2 - gridY1); }

		inline Pos<double> topleft()	 { return { x(0.), y(0.) }; }
		inline Pos<double> topright()	 { return { x(1.), y(0.) }; }
		inline Pos<double> bottomleft()	 { return { x(0.), y(1.) }; }
		inline Pos<double> bottomright() { return { x(1.), y(1.) }; }
		inline Pos<double> middle()		 { return { x(.5), y(.5) }; }

		inline Pos<double> p(double gridX, double gridY) {
			return { x(gridX / gridXSize), y(gridY / gridXSize) };
		}
	};

	class CharFactory {
	private:
		XYFactory xyf{};
	public:
		Character make(char c, int32_t x, int32_t y, double scaleX, double scaleY);
		String make(std::string_view str, int32_t x, int32_t y, double scaleX, double scaleY);
	private:
		Character dispatch(char c) ;

		Character make_excl() ;
		Character make_quot() ;
		Character make_hash() ;
		Character make_dolr() ;
		Character make_perc() ;
		Character make_amps() ;
		Character make_apos() ;
		Character make_robr() ;
		Character make_rcbr() ;
		Character make_astr() ;
		Character make_plus() ;
		Character make_comm() ;
		Character make_mins() ;
		Character make_peri() ;
		Character make_slsh() ;
		Character make_0() ;
		Character make_1() ;
		Character make_2() ;
		Character make_3() ;
		Character make_4() ;
		Character make_5() ;
		Character make_6() ;
		Character make_7() ;
		Character make_8() ;
		Character make_9() ;
		Character make_coln() ;
		Character make_smcl() ;
		Character make_less() ;
		Character make_equl() ;
		Character make_grtr() ;
		Character make_qstn() ;
		Character make_at() ;
		Character make_A() ;
		Character make_B() ;
		Character make_C() ;
		Character make_D() ;
		Character make_E() ;
		Character make_F() ;
		Character make_G() ;
		Character make_H() ;
		Character make_I() ;
		Character make_J() ;
		Character make_K() ;
		Character make_L() ;
		Character make_M() ;
		Character make_N() ;
		Character make_O() ;
		Character make_P() ;
		Character make_Q() ;
		Character make_R() ;
		Character make_S() ;
		Character make_T() ;
		Character make_U() ;
		Character make_V() ;
		Character make_W() ;
		Character make_X() ;
		Character make_Y() ;
		Character make_Z() ;
		Character make_sqob() ;
		Character make_bslh() ;
		Character make_sqcb() ;
		Character make_chev() ;
		Character make_unds() ;
		Character make_bqte() ;
		Character make_a() ;
		Character make_b() ;
		Character make_c() ;
		Character make_d() ;
		Character make_e() ;
		Character make_f() ;
		Character make_g() ;
		Character make_h() ;
		Character make_i() ;
		Character make_j() ;
		Character make_k() ;
		Character make_l() ;
		Character make_m() ;
		Character make_n() ;
		Character make_o() ;
		Character make_p() ;
		Character make_q() ;
		Character make_r() ;
		Character make_s() ;
		Character make_t() ;
		Character make_u() ;
		Character make_v() ;
		Character make_w() ;
		Character make_x() ;
		Character make_y() ;
		Character make_z() ;
		Character make_cobr() ;
		Character make_pipe() ;
		Character make_ccbr() ;
		Character make_tild() ;

	};
}