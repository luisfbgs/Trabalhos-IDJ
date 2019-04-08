#include <string>
#include <memory>
#include "TileSet.h"
#include "Sprite.h"

TileSet::TileSet(int tileWidth, int tileHeight, std::shared_ptr<Sprite> tileSet) : tileSet(tileSet) {
    this->tileWidth = tileWidth;
    this->tileHeight = tileHeight;
    this->rows = this->tileSet->GetHeight() / this->tileHeight;
    this->columns = this->tileSet->GetWidth() / this->tileWidth;
}

void TileSet::RenderTile(unsigned int index, float x, float y) {
    if(index < rows * columns) {
        int row = index / columns;
        int column = index % columns;
        float clipX, clipY;
        clipX = column * this->tileWidth;
        clipY = row * this->tileHeight;
        this->tileSet->SetClip(clipX, clipY, this->tileWidth, this->tileHeight);
        this->tileSet->Render(x, y);
    }
}

int TileSet::GetTileWidth() {
    return this->tileWidth;
}

int TileSet::GetTileHeight() {
    return this->tileHeight;
}