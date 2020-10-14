#include "defs.h"
#include "utils.h"
#include <spdlog/spdlog.h>
#include "Tiling.h"

TileGrid::TileGrid(const TileInfo& info)
	:
	indices(info.numTiles)
{
	uint32_t xOffset{ 0 };
	uint32_t yOffset{ 0 };

	if (info.numTiles != info.tileDims.first * info.tileDims.second)
	{
		spdlog::error("tile dimension mismatch!");
		spdlog::error("Num Tiles: {}, timeDims: ({}, {})",
			info.numTiles, info.tileDims.first, info.tileDims.second);
	}

	for (uint32_t i = 0; i < info.tileDims.first; ++i)
	{
		for (uint32_t j = 0; j < info.tileDims.second; ++j)
		{
			spdlog::critical("TILE OFFSET: ({}, {})", i, j);
			const auto gridIndex = static_cast<size_t>(i) * info.tileDims.first + static_cast<size_t>(j);
			
			// assign to indices
			xOffset = i * info.tileWidth;
			yOffset = j * info.tileHeight;
			indices[gridIndex] = std::make_pair(xOffset, yOffset);
		}
	}
}

void fillTileInfo(const uint32_t numTiles, const ConfigInfo& config, TileInfo& ti)
{
	auto imagebufferSize = config.imagebufferSize;
	auto imagebufferHeight = config.imagebufferHeight;
	auto imagebufferWidth = config.imagebufferWidth;

	const auto remainder = imagebufferSize % numTiles;
	if (remainder != 0)
	{
		imagebufferSize = imagebufferSize - remainder;
	}

	const auto tileSize = imagebufferSize / numTiles;
	uint32_t tileWidth{ 0 };
	uint32_t tileHeight{ 0 };

	// easy decomposition if we have tiles as square
	if (isPerfectSquare(numTiles))
	{
		const auto SRnumTiles = static_cast<decltype(tileWidth)>(std::sqrt(numTiles));
		tileWidth = imagebufferWidth / SRnumTiles;
		tileHeight = imagebufferHeight / SRnumTiles;
		ti.tileDims.first = SRnumTiles;
		ti.tileDims.second = SRnumTiles;
	}

	if (tileSize != tileWidth * tileHeight)
	{
		spdlog::error("Failed to tile the image!");
		return;
	}

	ti.numTiles = static_cast<uint32_t>(numTiles);
	ti.tileWidth = tileWidth;
	ti.tileHeight = tileHeight;
	ti.tileSize = tileSize;
	spdlog::critical("\n---------- TILE INFO ----------\nTile size: {}\nTile width: {}\nTile height {}\nTile Dims: ({}, {})",
		ti.tileSize, ti.tileWidth, ti.tileHeight, ti.tileDims.first, ti.tileDims.second);
}


