#include "Perlin.h"


#include "common.h"
#include <utility>

using namespace mathLib;

mathLib::Perlin::Perlin()
{
	for (auto& elem : ranFloat)
	{
		elem = RandDouble();
	}
	
	GenPerms();
}


double mathLib::Perlin::Noise(const point3& p) const 
{
	constexpr size_t PIXEL_RANGE {255};
	auto u 	{p.x() - std::floor(p.x())};
	auto v 	{p.y() - std::floor(p.y())};
	auto w 	{p.z() - std::floor(p.z())};
	// Hermetian Smoothing
	u = (u*u) * (3.0 - 2.0*u);
	v = (v*v) * (3.0 - 2.0*v);
	w = (w*w) * (3.0 - 2.0*w);


	const auto i 	{static_cast<size_t>(std::floor(p.x()))};
	const auto j 	{static_cast<size_t>(std::floor(p.y()))};
	const auto k 	{static_cast<size_t>(std::floor(p.z()))};

	double c[2][2][2];

	for (size_t di = 0; di < 2; ++di)
	{
		for (size_t dj = 0; dj < 2; ++dj)
		{
			for (size_t dk = 0; dk < 2; ++dk)
			{
				c[di][dj][dk] = ranFloat[
									permX[(i+di) & PIXEL_RANGE] ^ 
									permY[(j+dj) & PIXEL_RANGE] ^ 
									permZ[(k+dk) & PIXEL_RANGE]
								];
			}
		}
	}

	return TrilinearInterp(c, u, v, w);
}


double mathLib::Perlin::Turbulence(const point3& p, const size_t depth) const
{
	constexpr auto WEIGHT_SCALE {0.5};
	constexpr auto FREQ_SCALE	{2.0};

	auto accum		{0.0};
	auto temp_p 	{p};
	auto weight 	{1.0};

	for (size_t i = 0; i < depth; ++i)
	{
		accum +=	weight*Noise(temp_p);
		weight *=	WEIGHT_SCALE;
		temp_p *= 	FREQ_SCALE; 	
	}

	return std::fabs(accum);
}


void mathLib::Perlin::GenPerms()
{
	GenX();
	GenY();
	GenZ();
}

void mathLib::Perlin::GenX()
{
	for (size_t i = 0; i < permX.size(); ++i)
	{
		permX[i] = i;
	}

	for (size_t i = 0; i < permX.size(); ++i)
	{
		const size_t target {static_cast<size_t>(RandInt(0, static_cast<int>(i)))};
		std::swap(permX[i], permX[target]);
	}
}

void mathLib::Perlin::GenY()
{
	for (size_t i = 0; i < permY.size(); ++i)
	{
		permY[i] = i;
	}
	
	for (size_t i = 0; i < permX.size(); ++i)
	{
		const size_t target {static_cast<size_t>(RandInt(0, static_cast<int>(i)))};
		std::swap(permY[i], permY[target]);
	}
}

void mathLib::Perlin::GenZ()
{
	for (size_t i = 0; i < permZ.size(); ++i)
	{
		permZ[i] = i;
	}
	
	for (size_t i = 0; i < permZ.size(); ++i)
	{
		const size_t target {static_cast<size_t>(RandInt(0, static_cast<int>(i)))};
		std::swap(permZ[i], permZ[target]);
	}
}


