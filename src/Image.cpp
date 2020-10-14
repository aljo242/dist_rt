#include "Image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#include <spdlog/spdlog.h>

void writePNG(const char* filename, const uint32_t w, const uint32_t h, const uint32_t c, const std::vector<uint8_t>& image)
{
	spdlog::critical("Writing to file: {}", filename);
	stbi_write_png(filename, static_cast<int>(w), static_cast<int>(h), static_cast<int>(c), image.data(), static_cast<int>(w * c));
}
