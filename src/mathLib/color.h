#ifndef COLOR_H
#define COLOR_H

#include <iostream>

#include "vec3.h"

namespace mathLib
{

void WriteColor(std::ostream& os, color3 pixCol, const int samplesPerPixel);



} // namespace mathLib
 

#endif // COLOR_H