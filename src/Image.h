#ifndef IMAGE_H
#define IMAGE_H

#include <vector>
#include "defs.h"

void writePNG(const char* filename, const uint32_t w, const uint32_t h, const uint32_t c, const std::vector<uint8_t>& image);

#endif