#ifndef TEXTURE_H
#define TEXTURE_H

#include "vec3.h"
#include "Perlin.h"
#include <spdlog/spdlog.h>
#include <string>
using namespace mathLib;

namespace rtLib
{

class Texture
{
public:
	Texture() = default;

	virtual color3 Value(const double u, const double v, const point3& p) const = 0;

	virtual ~Texture() = default;
};


class Solid_Color : public Texture
{
public:
	Solid_Color() = default;
	Solid_Color(const color3& c) : col(c) {}

	Solid_Color(const double r, const double g, const double b)
		: col(color3(r,g,b)) {}

	virtual color3 Value(const double u, const double v, const point3& p) const override;

	//virtual ~Solid_Color() = default;

private:
	color3 col;
};


class CheckerBoard : public Texture
{
public:
	CheckerBoard() = default;
	CheckerBoard(std::shared_ptr<Texture> tex0, std::shared_ptr<Texture> tex1)
		: even(tex0), odd(tex1) {}

	virtual color3 Value(const double u, const double v, const point3& p) const override;

	//virtual ~CheckerBoard() = default;

private:	
	std::shared_ptr<Texture> even;
	std::shared_ptr<Texture> odd;
};


class Perlin_Noise : public Texture
{
public:
	Perlin_Noise() = default;
	Perlin_Noise(const double s) : scale(s) {}

	virtual color3 Value(const double u, const double v, const point3& p) const override;

	//virtual ~Perlin_Noise() = default;

private:
	Perlin noise;
	double scale = 1.0;
};


class Image_Tex : public Texture
{
public:
	constexpr static int bytesPerPixel {3};

	Image_Tex() : data(nullptr), width(0), height(0), bytesPerScanline(0) {}
	Image_Tex(const char* filename);

	virtual ~Image_Tex()
	{
		delete data;
	}

	virtual color3 Value(const double u, const double v, const point3& p) const override;

private:
	unsigned char* data;
	int width;
	int height;
	int bytesPerScanline;
};


} // namespace rtLib


#endif // TEXTURE_H