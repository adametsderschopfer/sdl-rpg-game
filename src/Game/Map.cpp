#include "Map.h"
#include "./Game.h"
#include "fstream"

Map::Map() {

}

Map::~Map() {

}

void Map::loadMap(const std::string &path, glm::ivec2 size) {
    char c;
    std::fstream mapFile;
    mapFile.open(path);

    glm::vec2 source;

    for (int y = 0; y < size.y; ++y) {
        for (int x = 0; x < size.x; ++x) {
            mapFile.get(c);
            source.x = atoi(&c) * 32; // todo magic number

            mapFile.get(c);
            source.y = atoi(&c) * 32; // todo magic number

            Game::addTile(source, glm::vec2(x * 64, y * 64)); // todo magic numbers
            mapFile.ignore();
        }
    }

    mapFile.close();
}