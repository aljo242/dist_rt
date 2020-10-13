#include "defs.h"
#include "utils.h"
#include <spdlog/spdlog.h>
#include "Tiling.h"

TileGrid::TileGrid(const TileInfo& info)
	:
	indices(info.numTiles)
{
	int counter{ 0 };
	int xOffset{ 0 };
	int yOffset{ 0 };

	if (info.numTiles != info.tileDims.first * info.tileDims.second)
	{
		spdlog::error("tile dimension mismatch!");
		spdlog::error("Num Tiles: {}, timeDims: ({}, {})",
			info.numTiles, info.tileDims.first, info.tileDims.second);
	}

	for (int i = 0; i < info.tileDims.first; ++i)
	{
		for (int j = 0; j < info.tileDims.second; ++j)
		{
			spdlog::critical("TILE OFFSET: ({}, {})", i, j);
			const auto gridIndex = static_cast<size_t>(i * info.tileDims.first + j);
			
			// assign to indices
			xOffset = i * info.tileWidth;
			yOffset = j * info.tileHeight;
			indices[gridIndex] = std::make_pair(xOffset, yOffset);
		}
	}
}

void fillTileInfo(const int numTiles, const ConfigInfo& config, TileInfo& ti)
{
	int imagebufferSize = config.imagebufferSize;
	int imagebufferHeight = config.imagebufferHeight;
	int imagebufferWidth = config.imagebufferWidth;

	const int remainder = imagebufferSize % numTiles;
	if (remainder != 0)
	{
		imagebufferSize = imagebufferSize - remainder;
	}

	const int tileSize = imagebufferSize / numTiles;
	int tileWidth{ 0 };
	int tileHeight{ 0 };

	// easy decomposition if we have tiles as square
	if (isPerfectSquare(numTiles))
	{
		const auto SRnumTiles = static_cast<int>(std::sqrt(numTiles));
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

	ti.numTiles = numTiles;
	ti.tileWidth = tileWidth;
	ti.tileHeight = tileHeight;
	ti.tileSize = tileSize;
	spdlog::critical("\n---------- TILE INFO ----------\nTile size: {}\nTile width: {}\nTile height {}\nTile Dims: ({}, {})",
		ti.tileSize, ti.tileWidth, ti.tileHeight, ti.tileDims.first, ti.tileDims.second);
}


