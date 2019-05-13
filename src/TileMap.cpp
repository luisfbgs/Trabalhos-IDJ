#include <string>
#include <memory>
#include "TileMap.h"
#include "TileSet.h"
#include "GameObject.h"
#include "Camera.h"

TileMap::TileMap(GameObject& associated, std::string file, std::shared_ptr<TileSet> tileSet) : Component(associated) {
    this->tileSet = tileSet;
    this->Load(file);
}

void TileMap::Load(std::string file) {
    FILE *fp = fopen(file.c_str(), "r");
    fscanf(fp, "%d,", &this->mapWidth);   
    fscanf(fp, "%d,", &this->mapHeight);   
    fscanf(fp, "%d,", &this->mapDepth);

    int matrixSize = this->mapHeight * this->mapWidth * this->mapDepth;
    this->tileMatrix.resize(matrixSize);
    for(int i = 0; i < matrixSize; i++) {
        fscanf(fp, "%d,", &this->tileMatrix[i]);
        --this->tileMatrix[i];
    }
}

void TileMap::SetTileSet(std::shared_ptr<TileSet> tileSet) {
    this->tileSet = tileSet;
}

int& TileMap::At(int x, int y, int z) {
    return this->tileMatrix[this->mapWidth * this->mapHeight * z + this->mapWidth * y + x];
}

void TileMap::RenderLayer(int layer, int cameraX, int cameraY) {
    cameraX = Camera::pos.x * layer;
    cameraY = Camera::pos.y * layer;
    for(int y = 0; y < this->mapHeight; y++) {
        for(int x = 0; x < this->mapWidth; x++) {
            int tileId = this->At(x, y, layer);
            float tileX = x * this->tileSet->GetTileWidth();
            float tileY = y * this->tileSet->GetTileHeight();
            this->tileSet->RenderTile(tileId, tileX - cameraX, tileY - cameraY);
        }
    }
}

void TileMap::Render() {
    for(int z = 0; z < mapDepth; z++) {
        this->RenderLayer(z);
    }
}

int TileMap::GetWidth() {
    return this->mapWidth;
}

int TileMap::GetHeight() {
    return this->mapHeight;
}

int TileMap::GetDepth() {
    return this->mapDepth;
}

void TileMap::Update(int dt) {
    (void)dt;
}

bool TileMap::Is(const std::string &type) {
    return type == "TileMap";
}