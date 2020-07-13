#ifndef VEC3_H
#define VEC3_H

#include <cmath>
#include <cstdlib>
#include <iostream>
#include <array>

#include "common.h"

namespace mathLib
{

class vec3
{
public:
	vec3() : e{0.0, 0.0, 0.0} {}
	vec3(const double e0, const double e1, const double e2);


	inline double x() const {return e[0];}
	inline double y() const {return e[1];}
	inline double z() const {return e[2];}

	inline double r() const {return e[0];}
	inline double g() const {return e[1];}
	inline double b() const {return e[2];}

	inline const vec3& operator+() const {return *this;}
	inline vec3 operator-() const {return vec3(-e[0], -e[1], -e[2]);}
	inline double operator[](const size_t i) const { return e[i]; }
	inline double& operator[](const size_t i) { return e[i]; }

	inline vec3& operator+=(const vec3& b)
	{
		e[0] += b[0];
		e[1] += b[1];
		e[2] += b[2];
		return *this;
	}

	inline vec3& operator-=(const vec3& b)
	{
		e[0] -= b[0];
		e[1] -= b[1];
		e[2] -= b[2];
		return *this;
	}

	inline vec3& operator*=(const vec3& b)
	{
		e[0] *= b[0];
		e[1] *= b[1];
		e[2] *= b[2];
		return *this;
	}

	inline vec3& operator/=(const vec3& b)
	{
		e[0] /= b[0];
		e[1] /= b[1];
		e[2] /= b[2];
		return *this;	
	}

	inline vec3& operator+=(const double t)
	{
		e[0] += t;
		e[1] += t;
		e[2] += t;
		return *this;		
	}

	inline vec3& operator-=(const double t)
	{	
		e[0] -= t;
		e[1] -= t;
		e[2] -= t;
		return *this;	
	}

	inline vec3& operator*=(const double t)
	{
		e[0] *= t;
		e[1] *= t;
		e[2] *= t;
		return *this;		
	}
	inline vec3& operator/=(const double t)
	{
		e[0] /= t;
		e[1] /= t;
		e[2] /= t;
		return *this;	
	}


	inline double Length() const
	{
		return std::sqrt((e[0] * e[0]) + (e[1] * e[1]) + (e[2] * e[2]));
	}

	inline double SquaredLength() const
	{
		return ((e[0] * e[0]) + (e[1] * e[1]) + (e[2] * e[2]));
	}

	inline void MakeUnit()
	{
		double k {1.0 / Length()};
		e[0] *= k;
		e[1] *= k;
		e[2] *= k;
	}

	inline static vec3 Random()
	{
		return {RandDouble(), RandDouble(), RandDouble()};
	}

	inline static vec3 Random(const double min, const double max)
	{
		return {RandDouble(min, max), RandDouble(min, max), RandDouble(min, max)};
	}

private:
	std::array<double, 3> e;
};


// type aliases
using point3 = vec3;
using color3 = vec3;


// non class operations

inline std::istream& operator>>(std::istream& is, vec3& t)
{
	is >> t[0] >> t[1] >> t[2];
	return is;
}

inline std::ostream& operator<<(std::ostream& os, const vec3& t)
{
	os << t.x() << " " << t.y() << " " << t.z();
	return os;
}


inline vec3 operator+(const vec3& v1, const vec3& v2)
{
	return vec3((v1.x() + v2.x()), (v1.y() + v2.y()), (v1.z() + v2.z()));
}

inline vec3 operator-(const vec3& v1, const vec3& v2)
{
	return vec3((v1.x() - v2.x()), (v1.y() - v2.y()), (v1.z() - v2.z()));	
}

inline vec3 operator*(const vec3& v1, const vec3& v2)
{
	return vec3((v1.x() * v2.x()), (v1.y() * v2.y()), (v1.z() * v2.z()));	
}

inline vec3 operator/(const vec3& v1, const vec3& v2)
{
	return vec3((v1.x() / v2.x()), (v1.y() / v2.y()), (v1.z() / v2.z()));	
}

inline vec3 operator*(const double t, const vec3& v)
{
	return vec3((v.x() * t), (v.y() * t), (v.z() * t));	
}

inline vec3 operator*(const vec3& v, const double t)
{
	return vec3((v.x() * t), (v.y() * t), (v.z() * t));	
}

inline vec3 operator/(const vec3& v, const double t)
{
	return vec3((v.x() / t), (v.y() / t), (v.z() / t));	
}

inline double Dot(const vec3& v1, const vec3& v2)
{
	return (v1.x() * v2.x()) + (v1.y() * v2.y()) + (v1.z() * v2.z());
}

inline vec3 Cross(const vec3& v1, const vec3& v2)
{
	return vec3( 	((v1.y() * v2.z()) - (v1.z() * v2.y())),
					((v1.x() * v2.z()) - (v1.z() * v2.x())),
					((v1.x() * v2.y()) - (v1.y() * v2.x()))
				);
}


inline vec3 UnitVector(const vec3& v)
{
	return v / v.Length();
}


} // namespace mathLib

#endif