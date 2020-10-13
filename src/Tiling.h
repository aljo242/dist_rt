#ifndef TILING_H
#define TILING_H


struct TileInfo
{
	int numTiles;
	int tileWidth;
	int tileHeight;
	int tileSize;
	std::pair<int, int> tileDims;
};

struct TileGrid
{
	TileGrid(const TileInfo& info);

	std::vector<std::pair<int, int>> indices;
};

void fillTileInfo(const int numTiles, const ConfigInfo& config, TileInfo& ti);


#endif // TILING_H