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
