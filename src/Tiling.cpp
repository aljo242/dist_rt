#include "defs.h"
#include "utils.h"
#include <spdlog/spdlog.h>
#include "Tiling.h"

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

}