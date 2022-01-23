#include <iostream>
#include <fstream>
#include "bmp.hpp"
#include "shapes.hpp"
using namespace bmp;

void drawGear(BMP &bmp) {
	constexpr uint32_t count = 16;
	constexpr double angle_base = 3.141593 / (2. * count);
	const Poly gear = Poly::interleaveMany({
		Poly::regular(100, 100, 100, count),
		Poly::regular(100, 100, 80,  count, angle_base),
		Poly::regular(100, 100, 80,  count, angle_base * 2),
		Poly::regular(100, 100, 100, count, angle_base * 3),
	});

	bmp.drawFilledPolygon(gear, colors::gray, colors::silver);
	bmp.drawFilledCircle(100, 100, 20, colors::gray, bmp.bgcolor());
}

int main() {
	bmp::BMP bmp{ 801,801 };
	shp::FilledCircle circle{ 400,400,400 };
	shp::FilledPolygon poly{ { {1,1},{50,50},{1,50} } };
	bmp::RadialGradient grad1{
		{colors::red, colors::orange, colors::yellow, colors::green,
		colors::cyan, colors::blue, colors::purple, colors::magenta},
		{ 400,400,0,-1 }, 3 };
	grad1.setBlendMode();
	grad1.setRepeating();

	bmp.drawShape(poly, colors::magenta);


	bmp.writeTo("test.bmp");
	return 0;
}

