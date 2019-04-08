#ifndef TILEMAP
#define TILEMAP

#include <string>
#include "Component.h"
#include "GameObject.h"
#include "TileSet.h"

class TileMap : public Component {
public:
    TileMap(GameObject& associated, std::string file, TileSet* tileSet);
    void Load(std::string file);
    void SetTileSet(TileSet* tileSet);
    int& At(int x, int y, int z = 0);
    void RenderLayer(int layer, int cameraX = 0, int cameraY = 0);
    void Render();
    int GetWidth();
    int GetHeight();
    int GetDepth();
    void Update(float dt);
    bool Is(std::string type);

private:
    std::vector<int> tileMatrix;
    TileSet* tileSet;
    int mapWidth;
    int mapHeight;
    int mapDepth;
};

#endif