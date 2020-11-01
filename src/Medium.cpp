#include "Medium.h"

MediumInterface::MediumInterface(const Medium* medium)
	:
	inside(medium), outside(medium)
{}

MediumInterface::MediumInterface(const Medium* in, const Medium* out)
	:
	inside(in), outside(out)
{}

bool MediumInterface::IsTransition() const
{
	return inside != outside;
}
