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
	shp::FilledRectangle poly1{ 0,0,800,50 };
	shp::FilledRectangle poly2{ 0,50,800,50 };
	shp::FilledCircle circle{ 400,400,400 };
	bmp::LinearGradient grad1{
		{colors::red, colors::orange, colors::yellow, colors::green,
		colors::cyan, colors::blue, colors::purple, colors::magenta},
		{ 400,400,0,-1 }, 19 };
	bmp::RadialGradient grad2{ {-1,0},{400,400,4,0}, 8 };

	//grad1.setRepeating();
	//grad1.setBlendMode(1);
	grad2.setBlendMode(1);
	bmp.drawShape(circle, grad2);


	bmp.writeTo("test.bmp");
	return 0;
}


/*
* 
* 
	class Surface {
	private:
		Matrix<Color> color_space;
		Matrix<bool> transparency;
	public:
		Surface(std::size_t width, std::size_t height);

		inline bool 

		inline Matrix<Color>::const_iterator operator[](std::size_t index) const {
			return color_space[index];
		}

		inline Matrix<Color>::iterator operator[](std::size_t index) {
			return color_space[index];
		}
	};

	const Poly penta = Poly::regular(100, 100, 100, 5).rearranged({0,3,1,4,2});

	BMP bmp{ 201,201,colors::black };
	bmp.drawFilledPolygon(penta, colors::maroon, colors::red);
	bmp.drawCircle(100, 100, 100, colors::maroon);




//bmp.drawFilledPolygon(Poly::interleaveMany({ p[0],p[1],p[2],p[3] }), colors::gray, colors::silver);
//bmp.drawFilledCircle(100, 100, 20, colors::gray, colors::white);


for (int32_t i = 0; i < 29; ++i)
	bmp.drawEllipse(i*i + 5*i + 8, 100, i + 1, 2 * i + 1, Colors::red);
bmp.floodFill(500, 100, 0x4FAA11);
bmp.floodFill(500, 0, 0x0055AA);



bmp.drawCircle(80, 80, 80, Colors::gray);
bmp.drawString("EE", 30, 30, Colors::red, 3, 3, 6);
bmp.drawString("EEEEE", 35, 100, Colors::blue, 1, 1, 3);

bmp.drawLine(100, 100, 150, 0, Colors::red);
bmp.drawLine(100, 100, 200, 50, Colors::orange);
bmp.drawLine(100, 100, 200, 150, Colors::yellow);
bmp.drawLine(100, 100, 150, 200, Colors::green);
bmp.drawLine(100, 100, 50, 200, Colors::cyan);
bmp.drawLine(100, 100, 0, 150, Colors::blue);
bmp.drawLine(100, 100, 0, 50, Colors::purple);
bmp.drawLine(100, 100, 50, 0, Colors::magenta);

bmp.floodFill(110, 90, Colors::red);
bmp.floodFill(110, 100, Colors::orange);
bmp.floodFill(110, 110, Colors::yellow);
bmp.floodFill(100, 110, Colors::green);
bmp.floodFill(90, 110, Colors::cyan);
bmp.floodFill(90, 100, Colors::blue);
bmp.floodFill(90, 90, Colors::purple);
bmp.floodFill(100, 90, Colors::magenta);

	//bmp.drawEllipse(100, 100, 40, 25, 0.5235987755982, Colors::silver);
	//bmp.floodFill(190, 100, Colors::orange);
	//bmp.drawFilledRect(30, 30, 110, 70, 1.0, Colors::black, Colors::green);
	bmp.drawFilledPolygon({ {50,50}, {100,30}, {60,90}, {110,100}, {10,30}, {30, 140}, {110, 90} },
		Colors::black, Colors::magenta);
	bmp.drawEllipse(70, 70, 50, 20, Colors::blue);
	bmp.floodFill(70, 70, Colors::orange);
*/
