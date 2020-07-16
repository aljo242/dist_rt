#include "casting.h"
#include "hittable_list.h"

using namespace mathLib;



vec3 rtLib::RandInUnitDisk()
{
	while(true)
	{
		const auto p {vec3(RandDouble(-1.0, 1.0), RandDouble(-1.0, 1.0), 0.0)};
		if (p.SquaredLength() >= 1.0) {continue;}
		return p;
	}
}


vec3 rtLib::RandUnitVec()
{
	const auto a {RandDouble(0.0, 2*pi)};
	const auto z {RandDouble(-1.0, 1.0)};
	const auto r {std::sqrt(1.0 - z*z)};
	return {r*std::cos(a), r*std::sin(a), z};
}


vec3 rtLib::RandInUnitSphere()
{
	while(true)
	{
		const auto p {vec3::Random(-1.0, 1.0)};
		if (p.SquaredLength() >= 1.0) {continue;}
		return p;
	}
}

vec3 rtLib::RandInHemiSphere(const vec3& normal)
{
	const auto inUnitSphere {RandInUnitSphere()};
	if (Dot(inUnitSphere, normal) > 0.0)
	{
		return inUnitSphere;
	}
	else
	{
		return -inUnitSphere;
	}
}


vec3 rtLib::Reflect(const vec3& vec, const vec3& normal)
{
	return {vec - (2.0 * Dot(vec, normal) * normal)};
}


vec3 rtLib::Refract(const vec3& uv, const vec3& normal, const double refRatio)
{
	const auto cosTheta {std::fmin(Dot(-uv, normal), 1.0)};
	const auto rOutPar {refRatio * (uv + cosTheta * normal)};
	const auto rOutPerp {-std::sqrt(1.0 - rOutPar.SquaredLength()) * normal};
	return {rOutPar + rOutPerp};
}

