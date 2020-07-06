#ifndef HITABLE_LIST_H
#define HITABLE_LIST_H

#include "hitable.h"

using namespace mathLib;

namespace rtLib
{
	
class hitable_list : public hitable
{
public:
	hitable_list() = default;
	hitable_list(hitable **l, const int n) :  list(l), list_size(n) {}
	

	virtual bool hit(const ray& r, const float t_min, 
		const float t_max, hit_record& rec) const override;

protected:
	virtual ~hitable_list() {}

private:
	hitable **list;
	int list_size;
};

}

#endif