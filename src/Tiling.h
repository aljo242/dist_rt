#ifndef TILING_H
#define TILING_H


struct TileInfo
{
	uint32_t numTiles;
	uint32_t tileWidth;
	uint32_t tileHeight;
	uint32_t tileSize;
	std::pair<uint32_t, uint32_t> tileDims;
};

struct TileGrid
{
	TileGrid(const TileInfo& info);

	std::vector<std::pair<uint32_t, uint32_t>> indices;
};

void fillTileInfo(const uint32_t numTiles, const ConfigInfo& config, TileInfo& ti);


#endif // TILING_H