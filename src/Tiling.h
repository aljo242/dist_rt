#ifndef TILING_H
#define TILING_H


struct TileInfo
{
	int numTiles;
	int tileWidth;
	int tileHeight;
	int tileSize;
};

void fillTileInfo(const int numTiles, const ConfigInfo& config, TileInfo& ti);


#endif // TILING_H