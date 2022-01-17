#pragma once
#include <functional>
#include "positions.hpp"

namespace bmp {
	class BMP;

	using TextFunc = std::function<void(BMP &, int32_t, int32_t, Color, double, double)>;

	TextFunc ascii_dispatch(char c);
	Pos<int32_t> ascii_dimensions(double scaleX, double scaleY);
}
