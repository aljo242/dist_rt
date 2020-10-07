#ifndef IMAGE_H
#define IMAGE_H

#include <vector>
#include "defs.h"

void writePNG(const char* filename, const int w, const int h, const int c, const std::vector<uint8_t>& image);

#endif