#include "Texture.h"

#include "image.h"

#include "Perlin.h"
using namespace mathLib;

color3 rtLib::Solid_Color::Value(const double u, const double v, const point3& p) const
{
	return this->col;
}


color3 rtLib::CheckerBoard::Value(const double u, const double v, const point3& p) const
{
	const auto sines 	{std::sin(10.0 * p.x()) * std::sin(10.0 * p.y()) * std::sin(10.0 * p.z())};
	if (sines < 0.0)
	{
		return odd->Value(u, v, p);
	}
	else
	{
		return even->Value(u, v, p);
	}
}


color3 rtLib::Perlin_Noise::Value(const double u, const double v, const point3& p) const
{
	return color3(1.0, 1.0, 1.0) * 0.5 * (1.0 + std::sin(scale*p.z() + 10.0*noise.Turbulence(p)));
}




rtLib::Image_Tex::Image_Tex(const std::string& filename)
{
	auto componentsPerPixel 	{bytesPerPixel};

	data = stbi_load(
		filename.c_str(), &width, &height, &componentsPerPixel, componentsPerPixel);

	if (!data)
	{
		spdlog::error("Could not load texture image file: {}", filename.c_str());
		width = 0;
		height = 0;
	}

	bytesPerScanline = bytesPerPixel * width;
}


color3 rtLib::Image_Tex::Value(const double u, const double v, const point3& p) const
{
	if (!data)
	{
		return {0.0, 1.0, 1.0};
	}

	// clamp input texcoords to [0,1] x [1,0]
	const auto s 	{mathLib::Clamp(u, 0.0, 1.0)};
	const auto t 	{1.0 - mathLib::Clamp(v, 1.0, 0.0)};

	auto i 	{ static_cast<int>(s * width) }; 
	auto j 	{ static_cast<int>(t * height) }; 

	// clamp integer mapping, since coords should be less than 1.0
	if (i >= width) i = width - 1;
	if (j >= height) j = height - 1;

	constexpr auto COLOR_SCALE		{1.0 / 255.0};
	auto pixel 	{data + j * bytesPerScanline + i * bytesPerPixel};

	return {(COLOR_SCALE * pixel[0]), (COLOR_SCALE * pixel[1]), (COLOR_SCALE * pixel[2])};
}