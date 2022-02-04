#include <functional>
#include "bmp.hpp"
#include "ascii.hpp"
#include "common.hpp"

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
	Character CharFactory::make_slsh() { return { '\0', {} }; }
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
		LineSet s2{ { xyf.p(1,11), xyf.p(3,11) } };
		return {'A', {s1,s2}};
	}
	Character CharFactory::make_B() { 
		xyf.setGrid(10,2);
		LineSet s1{ { xyf.p(1,0), xyf.p(1,2) } };
		BezierCurve<3> s2{ { xyf.p(1,0), xyf.p(11,0), xyf.p(11,1), xyf.p(1,1) } };
		BezierCurve<3> s3{ { xyf.p(1,1), xyf.p(12,1), xyf.p(12,2), xyf.p(1,2) } };
		return {'B', {s1,s2,s3}};
	}
	Character CharFactory::make_C() { 
		xyf.setGrid(2, 2);
		Arc s1{ xyf.gxi(1), xyf.gyi(1), xyf.glxi(1), xyf.glyi(1), xyf.ang(0.1), xyf.ang(0.9) };
		return {'C', {s1}};
	}
	Character CharFactory::make_D() {
		xyf.setGrid(10, 1);
		LineSet s1{ { xyf.p(1,0), xyf.p(1,1) } };
		BezierCurve<3> s2{ { xyf.p(1,0), xyf.p(12,0), xyf.p(12,1), xyf.p(1,1) } };
		return {'D', {s1,s2}};
	}
	Character CharFactory::make_E() {
		xyf.setGrid(10, 2);
		Polyline s1{ { xyf.p(9,0), xyf.p(1,0), xyf.p(1,2), xyf.p(9,2) } };
		LineSet s2{ { xyf.p(1,1), xyf.p(7,1) } };
		return {'E', {s1,s2}};
	}
	Character CharFactory::make_F() {
		xyf.setGrid(10, 2);
		Polyline s1{ { xyf.p(9,0), xyf.p(1,0), xyf.p(1,2) } };
		LineSet s2{ { xyf.p(1,1), xyf.p(7,1) } };
		return {'F', {s1,s2}};
	}
	Character CharFactory::make_G() {
		xyf.setGrid(10,10);
		Arc s1{ xyf.gxi(5), xyf.gyi(5), xyf.glxi(5), xyf.glyi(5), xyf.ang(0.1), xyf.ang(0.9) };
		Polyline s2{ { xyf.p(5,5), xyf.p(9,5), xyf.p(9,8) } };
		return {'G', {s1,s2}};
	}
	Character CharFactory::make_H() {
		xyf.setGrid(10,2);
		LineSet s1{ { xyf.p(1,0), xyf.p(1,2), xyf.p(1,1), xyf.p(9,1), xyf.p(9,0), xyf.p(9,2) } };
		return {'H', {s1}};
	}
	Character CharFactory::make_I() {
		xyf.setGrid(4, 2);
		LineSet s1{ { xyf.p(1,0), xyf.p(3,0), xyf.p(2,0), xyf.p(2,2), xyf.p(1,2), xyf.p(3,2) } };
		return {'I', {s1}};
	}
	Character CharFactory::make_J() {
		xyf.setGrid(8, 6);
		LineSet s1{ { xyf.p(7,0), xyf.p(7,4) } };
		Arc s2{ xyf.gxi(4), xyf.gyi(4), xyf.glxi(3), xyf.glyi(2), xyf.ang(0.6), xyf.ang(1.0) };
		return {'J', {s1,s2}};
	}
	Character CharFactory::make_K() {
		xyf.setGrid(10, 2);
		LineSet s1{ { xyf.p(1,0), xyf.p(1,2) } };
		Polyline s2{ { xyf.p(9,0), xyf.p(1,1) + Pos<double>{1,0}, xyf.p(9,2) } };
		return {'K', {s1,s2}};
	}
	Character CharFactory::make_L() {
		xyf.setGrid(10, 1);
		Polyline s1{ { xyf.p(1,0), xyf.p(1,1), xyf.p(9,1) } };
		return {'L', {s1}};
	}
	Character CharFactory::make_M() {
		xyf.setGrid(10, 2);
		Polyline s1{ { xyf.p(0,2), xyf.p(2,0), xyf.p(5,1.2), xyf.p(8,0), xyf.p(10,2) } };
		return { 'M', {s1} };
	}
	Character CharFactory::make_N() {
		xyf.setGrid(10, 2);
		Polyline s1{ { xyf.p(1,2), xyf.p(1,0), xyf.p(9,2), xyf.p(9,0) } };
		return { 'N', {s1} };
	}
	Character CharFactory::make_O() {
		xyf.setGrid(2, 2);
		Ellipse s1{ xyf.gxi(1), xyf.gyi(1), xyf.glxi(0.9), xyf.glyi(1) };
		return { 'O', {s1} };
	}
	Character CharFactory::make_P() {
		xyf.setGrid(10, 2);
		LineSet s1{ { xyf.p(1,0), xyf.p(1,2) } };
		BezierCurve<3> s2{ { xyf.p(1,0), xyf.p(11,0), xyf.p(11,1), xyf.p(1,1) } };
		return { 'P', {s1,s2} };
	}
	Character CharFactory::make_Q() {
		xyf.setGrid(6, 6);
		Ellipse s1{ xyf.gxi(3), xyf.gyi(3), xyf.glxi(2.7), xyf.glyi(3) };
		LineSet s2{ { xyf.p(4,4), xyf.p(6,6) } };
		return { 'Q', {s1,s2} };
	}
	Character CharFactory::make_R() {
		xyf.setGrid(10, 2);
		LineSet s1{ { xyf.p(1,0), xyf.p(1,2), xyf.p(1,1), xyf.p(9,2) } };
		BezierCurve<3> s2{ { xyf.p(1,0), xyf.p(11,0), xyf.p(11,1), xyf.p(1,1) } };
		return { 'R', {s1,s2} };
	}
	Character CharFactory::make_S() {
		const double w = xyf.lx(0.5), h = xyf.ly(0.55);
		auto func = [w, h](double t)->Shape::PointF {
			return { -sin(2 * t) * w, cos(t) * abs(cos(t)) * h };
		};

		Parametric s1{ xyf.xi(0.5), xyf.yi(0.5), func,
			xyf.ang(0.4), xyf.ang(1.1), std::max(w,h) };
		return { 'S', {s1} };
	}
	Character CharFactory::make_T() {
		return { 'T', {} };
	}
	Character CharFactory::make_U() {
		return { 'U', {} };
	}
	Character CharFactory::make_V() {
		return { 'V', {} };
	}
	Character CharFactory::make_W() {
		return { 'W', {} };
	}
	Character CharFactory::make_X() {
		return { 'X', {} };
	}
	Character CharFactory::make_Y() {
		return { 'Y', {} };
	}
	Character CharFactory::make_Z() {
		return { 'Z', {} };
	}
	Character CharFactory::make_sqob() { return {'\0', {}}; }
	Character CharFactory::make_bslh() { return {'\0', {}}; }
	Character CharFactory::make_sqcb() { return {'\0', {}}; }
	Character CharFactory::make_chev() { return {'\0', {}}; }
	Character CharFactory::make_unds() { return {'\0', {}}; }
	Character CharFactory::make_bqte() { return {'\0', {}}; }
	Character CharFactory::make_a() {
		xyf.setGrid(8, 9);
		LineSet s1{ {xyf.p(7,3), xyf.p(7,9)} };
		Ellipse s2{ xyf.gxi(4), xyf.gyi(6), xyf.glxi(3), xyf.glyi(3) };
		return { 'a', {s1,s2} };
	}
	Character CharFactory::make_b() {
		xyf.setGrid(8, 9);
		LineSet s1{ {xyf.p(1,0), xyf.p(1,9)} };
		Ellipse s2{ xyf.gxi(4), xyf.gyi(6), xyf.glxi(3), xyf.glyi(3) };
		return {'b', {s1,s2}};
	}
	Character CharFactory::make_c() {
		xyf.setGrid(8, 9);
		Arc s1{ xyf.gxi(4), xyf.gyi(6), xyf.glxi(3), xyf.glyi(3), xyf.ang(0.1), xyf.ang(0.9) };
		return {'c', {s1}}; 
	}
	Character CharFactory::make_d() {
		xyf.setGrid(8, 9);
		LineSet s1{ {xyf.p(7,0), xyf.p(7,9)} };
		Ellipse s2{ xyf.gxi(4), xyf.gyi(6), xyf.glxi(3), xyf.glyi(3) };
		return {'d', {s1,s2}}; 
	}
	Character CharFactory::make_e() {
		xyf.setGrid(8, 9);
		Arc s1{ xyf.gxi(4), xyf.gyi(6), xyf.glxi(3), xyf.glyi(3), xyf.ang(0.0), xyf.ang(0.9) };
		LineSet s2{ {xyf.p(1,6), xyf.p(7,6)} };
		return { 'e', {s1,s2} };
	}
	Character CharFactory::make_f() {
		xyf.setGrid(8, 9);
		LineSet s1{ { xyf.p(4,2), xyf.p(4,9)} };
		LineSet s2{ { xyf.p(2,4), xyf.p(7,4)} };
		Arc s3{ xyf.gxi(7), xyf.gyi(3), xyf.glxi(3), xyf.glyi(3), xyf.ang(0.25), xyf.ang(0.5) };
		return {'f', {s1,s2,s3}}; 
	}
	Character CharFactory::make_g() {
		xyf.setGrid(8, 9);
		Ellipse s1{ xyf.gxi(4), xyf.gyi(6), xyf.glxi(3), xyf.glyi(3) };
		LineSet s2{ { xyf.p(7,3), xyf.p(7,11) } };
		Arc s3{ xyf.gxi(4), xyf.gyi(9), xyf.glxi(3), xyf.glyi(3), xyf.ang(0.6), xyf.ang(1.0) };
		return { 'g', {s1,s2,s3} };
	}
	Character CharFactory::make_h() {
		xyf.setGrid(8, 9);
		LineSet s1{ { xyf.p(1,0), xyf.p(1,9), xyf.p(7,5), xyf.p(7,9) } };
		Arc s2{ xyf.gxi(4), xyf.gyi(6), xyf.glxi(3), xyf.glyi(3), xyf.ang(0.0), xyf.ang(0.5) };
		return {'h', {s1,s2}}; 
	}
	Character CharFactory::make_i() {
		xyf.setGrid(8, 9);
		Polyline s1{ { xyf.p(2,3.5), xyf.p(4,3.5), xyf.p(4,9) } };
		LineSet s2{ { xyf.p(2,9), xyf.p(6,9) } };
		FilledEllipse s3{ xyf.gxi(4), xyf.gyi(1), xyf.glxi(.25), xyf.glyi(.25) };
		Pixel s4{ xyf.gxi(4), xyf.gyi(1) };
		return {'i', {s1,s2,s3,s4}};
	}
	Character CharFactory::make_j() {
		xyf.setGrid(8, 9);
		Polyline s1{ { xyf.p(2,3.5), xyf.p(6,3.5), xyf.p(6,9) } };
		Arc s2{ xyf.gxi(3.5), xyf.gyi(9), xyf.glxi(2.5), xyf.glyi(3), xyf.ang(0.6), xyf.ang(1.0) };
		FilledEllipse s3{ xyf.gxi(4), xyf.gyi(1), xyf.glxi(.25), xyf.glyi(.25) };
		Pixel s4{ xyf.gxi(4), xyf.gyi(1) };
		return {'j', {s1,s2,s3,s4}};
	}
	Character CharFactory::make_k() {
		xyf.setGrid(10, 9);
		LineSet s1{ { xyf.p(2,0), xyf.p(2,9) } };
		Polyline s2{ { xyf.p(8,4), xyf.p(2,6.5) + Pos<double>{1,0}, xyf.p(8,9) } };
		return { 'k', {s1,s2} };
	}
	Character CharFactory::make_l() {
		Polyline s1{ { xyf.p(2,0), xyf.p(4,0), xyf.p(4,9) } };
		LineSet s2{ { xyf.p(2,9), xyf.p(6,9) } };
		return { 'l', {s1,s2} };
	}
	Character CharFactory::make_m() {
		xyf.setGrid(8, 9);
		LineSet s1{ { xyf.p(0,9), xyf.p(0,4), xyf.p(4,9), xyf.p(4,5), xyf.p(8,9), xyf.p(8,5) } };
		BezierCurve<2> s2{ { xyf.p(0,5), xyf.p(2,3), xyf.p(4,5) } };
		BezierCurve<2> s3{ { xyf.p(4,5), xyf.p(6,3), xyf.p(8,5) } };
		return { 'm', {s1,s2,s3} };
	}
	Character CharFactory::make_n() {
		xyf.setGrid(8, 9);
		LineSet s1{ { xyf.p(1,9), xyf.p(1,4), xyf.p(7,9), xyf.p(7,5) } };
		BezierCurve<2> s2{ { xyf.p(1,5), xyf.p(4,2), xyf.p(7,5) } };
		return { 'n', {s1,s2} };
	}
	Character CharFactory::make_o() {
		xyf.setGrid(8, 9);
		Ellipse s1{ xyf.gxi(4), xyf.gyi(6), xyf.glxi(3), xyf.glyi(3) };
		return { 'o', {s1} };
	}
	Character CharFactory::make_p() {
		xyf.setGrid(8, 9);
		LineSet s1{ {xyf.p(1,3), xyf.p(1,13)} };
		Ellipse s2{ xyf.gxi(4), xyf.gyi(6), xyf.glxi(3), xyf.glyi(3) };
		return { 'p', {s1,s2} };
	}
	Character CharFactory::make_q() {
		xyf.setGrid(8, 9);
		LineSet s1{ {xyf.p(7,3), xyf.p(7,13)} };
		Ellipse s2{ xyf.gxi(4), xyf.gyi(6), xyf.glxi(3), xyf.glyi(3) };
		return { 'q', {s1,s2} };
	}
	Character CharFactory::make_r() {
		xyf.setGrid(8, 9);
		LineSet s1{ {xyf.p(1,3), xyf.p(1,9)} };
		BezierCurve<2> s2{ { xyf.p(1,5), xyf.p(1,3), xyf.p(7,3) } };
		return { 'r', {s1,s2} };
	}
	Character CharFactory::make_s() {
		xyf.setGrid(8, 9);
		const double w = xyf.glx(3), h = xyf.gly(3.3);
		auto func = [w, h](double t)->Shape::PointF {
			return { -sin(2 * t) * w, cos(t) * abs(cos(t)) * h };
		};

		Parametric s1{ xyf.gxi(4), xyf.gyi(6), func,
			xyf.ang(0.4), xyf.ang(1.1), std::max(w,h) };
		return { 's', {s1} };
	}
	Character CharFactory::make_t() {
		return { 't', {} };
	}
	Character CharFactory::make_u() { return {'u', {}}; }
	Character CharFactory::make_v() { return {'v', {}}; }
	Character CharFactory::make_w() { return {'w', {}}; }
	Character CharFactory::make_x() { return {'x', {}}; }
	Character CharFactory::make_y() { return {'y', {}}; }
	Character CharFactory::make_z() { return {'z', {}}; }
	Character CharFactory::make_cobr() { return {'\0', {}}; }
	Character CharFactory::make_pipe() { return {'\0', {}}; }
	Character CharFactory::make_ccbr() { return {'\0', {}}; }
	Character CharFactory::make_tild() { return { '\0', {} }; }
}
