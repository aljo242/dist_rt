#ifndef PERLIN_H
#define PERLIN_H

#include <array>
#include "vec3.h"

namespace mathLib
{


inline double TrilinearInterp(const double c[2][2][2], const double u, const double v, const double w)
{
	auto accum {0.0};
	for (double i = 0; i < 2.0; i+=1.0)
	{
		for (double j = 0; j < 2.0; j+=1.0)
		{
			for (double k = 0; k < 2.0; k+=1.0)
			{
				accum += 	(i*u + (1.0-i)*(1.0-u))*
							(j*v + (1.0-j)*(1.0-v))*
							(k*w + (1.0-k)*(1.0-w))*
							c[static_cast<size_t>(i)][static_cast<size_t>(j)][static_cast<size_t>(k)];
			}
		}
	}
	return accum;
}


class Perlin
{
public:
	Perlin();

	~Perlin() = default;

	double Noise(const point3& p) const;
	double Turbulence(const point3& p, const size_t depth = 7) const;

private:
	static constexpr int pointCount {256};

	std::array<double, pointCount>			ranFloat;	
	std::array<size_t, pointCount>			permX;
	std::array<size_t, pointCount>			permY;
	std::array<size_t, pointCount>			permZ;

private:
	void GenPerms();
	void GenX();
	void GenY();
	void GenZ();

};

} // namespace mathLib


#endif // PERLIN_H