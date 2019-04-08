#ifndef TILESET
#define TILESET

#include <string>
#include <vector>
#include "Sprite.h"

class TileSet {
public:
    TileSet(int tileWidth, int tileHeight, Sprite tileSet);
    void RenderTile(unsigned int index, float x, float y);
    int GetTileWidth();
    int GetTileHeight();

private:
    std::vector<int> tileMatrix;
    Sprite tileSet;
    unsigned int rows;
    unsigned int columns;
    int tileWidth;
    int tileHeight;
};

#endif