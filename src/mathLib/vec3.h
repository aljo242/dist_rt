#ifndef VEC3_H
#define VEC3_H

#include <cmath>
#include <cstdlib>
#include <iostream>
#include <array>

namespace mathLib
{

class vec3
{
public:
	vec3() = default;
	vec3(const float e0, const float e1, const float e2);


	inline float x() const {return e[0];}
	inline float y() const {return e[1];}
	inline float z() const {return e[2];}

	inline float r() const {return e[0];}
	inline float g() const {return e[1];}
	inline float b() const {return e[2];}

	inline const vec3& operator+() const {return *this;}
	inline vec3 operator-() const {return vec3(-e[0], -e[1], -e[2]);}
	inline float operator[](const size_t i) const { return e[i]; }
	inline float& operator[](const size_t i) { return e[i]; }

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

	inline vec3& operator+=(const float t)
	{
		e[0] += t;
		e[1] += t;
		e[2] += t;
		return *this;		
	}

	inline vec3& operator-=(const float t)
	{	
		e[0] -= t;
		e[1] -= t;
		e[2] -= t;
		return *this;	
	}

	inline vec3& operator*=(const float t)
	{
		e[0] *= t;
		e[1] *= t;
		e[2] *= t;
		return *this;		
	}
	inline vec3& operator/=(const float t)
	{
		e[0] /= t;
		e[1] /= t;
		e[2] /= t;
		return *this;	
	}


	inline float length() const
	{
		return std::sqrt((e[0] * e[0]) + (e[1] * e[1]) + (e[2] * e[2]));
	}

	inline float squared_length() const
	{
		return ((e[0] * e[0]) + (e[1] * e[1]) + (e[2] * e[2]));
	}

	inline void make_unit()
	{
		float k {1.0f / length()};
		e[0] *= k;
		e[1] *= k;
		e[2] *= k;
	}

private:
	std::array<float, 3> e;
};

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

inline vec3 operator*(const float t, const vec3& v)
{
	return vec3((v.x() * t), (v.y() * t), (v.z() * t));	
}

inline vec3 operator*(const vec3& v, const float t)
{
	return vec3((v.x() * t), (v.y() * t), (v.z() * t));	
}

inline vec3 operator/(const vec3& v, const float t)
{
	return vec3((v.x() / t), (v.y() / t), (v.z() / t));	
}

inline float dot(const vec3& v1, const vec3& v2)
{
	return (v1.x() * v2.x()) + (v1.y() * v2.y()) + (v1.z() * v2.z());
}

inline vec3 cross(const vec3& v1, const vec3& v2)
{
	return vec3( 	((v1.y() * v2.z()) - (v1.z() * v2.y())),
					((v1.x() * v2.z()) - (v1.z() * v2.x())),
					((v1.x() * v2.y()) - (v1.y() * v2.x()))
				);
}


inline vec3 unit_vector(const vec3& v)
{
	return v / v.length();
}


} // namespace mathLib

#endif