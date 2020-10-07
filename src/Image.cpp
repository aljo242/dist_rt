#include "Image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#include <spdlog/spdlog.h>

void writePNG(const char* filename, const int w, const int h, const int c, const std::vector<uint8_t>& image)
{
	spdlog::critical("Writing to file: {}", filename);
	stbi_write_png(filename, w, h, c, image.data(), w * c);
}
