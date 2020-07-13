#include "color.h"
#include "common.h"

using namespace mathLib;

void mathLib::WriteColor(std::ostream& os, const color3 pixCol, const int samplesPerPixel)
{
	auto r = pixCol.r();
	auto g = pixCol.g();
	auto b = pixCol.b();

	// divide the color total byy the number of samples
	const double scale			{ 1.0 / samplesPerPixel };
	r = std::sqrt(scale * r);
	b = std::sqrt(scale * b);
	g = std::sqrt(scale * g);

	constexpr int pixelRange 	{256};

	// write translated [0,255] to  each color component
	const int ir { static_cast<int>(pixelRange * Clamp(r, 0.0, 0.999))};
	const int ig { static_cast<int>(pixelRange * Clamp(g, 0.0, 0.999))};
	const int ib { static_cast<int>(pixelRange * Clamp(b, 0.0, 0.999))};

	os << ir << ' ' << ig << ' ' << ib << '\n';
}

