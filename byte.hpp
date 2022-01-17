#pragma once
#include <ostream>

class byte_t {
private:
	char val;
public:
	inline constexpr byte_t() : val(0) {}
	inline constexpr byte_t(char c) : val(c) {}
	inline constexpr byte_t(const byte_t &b) : val(b.val) {}

	inline operator char() const { return val; }
	//inline operator unsigned char() const { return static_cast<unsigned char>(val); }

	friend std::ostream& operator<<(std::ostream &ost, byte_t byte) {
		return ost << static_cast<short>(byte.val);
	}
};

class ubyte_t {
private:
	unsigned char val;
public:
	inline constexpr ubyte_t() : val(0) {}
	inline constexpr ubyte_t(unsigned char c) : val(c) {}
	inline constexpr ubyte_t(const ubyte_t &b) : val(b.val) {}

	//inline operator char() const { return static_cast<char>(val); }
	inline operator unsigned char() const { return val; }

	friend std::ostream& operator<<(std::ostream &ost, ubyte_t byte) {
		return ost << static_cast<unsigned short>(byte.val);
	}
};
