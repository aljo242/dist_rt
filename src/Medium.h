#ifndef MEDIUM_H
#define MEDIUM_H

#include "defs.h"


class PhaseFunction
{
public:
	virtual ~PhaseFunction();
	virtual float p(const Vec3& outgoing, const Vec3& incoming) const = 0;
	virtual float Sample(const Vec3& outgoing, Vec3* incoming, const Point2& u) const = 0;
};

class Medium
{
public:
	virtual ~Medium() = default;
	virtual Spectrum Tr(const Ray3& ray, Sampler& sampler);
};

struct MediumInterface
{
	MediumInterface(const Medium* medium);
	MediumInterface(const Medium* in, const Medium* out);
	bool IsTransition() const;

	const Medium* inside;
	const Medium* outside;
};

#endif // MEDIUM_H