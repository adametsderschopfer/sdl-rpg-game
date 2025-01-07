#include "Map.h"

#include <utility>
#include "./Game.h"
#include "fstream"
#include "../Core/ECS/ECS.h"
#include "../Core/ECS/ColliderComponent.h"

extern EntityManager entityManager;

Map::Map(std::string mapTexturePath, float tileSize, float mapScale)
        : m_mapTexturePath(std::move(mapTexturePath)),
          m_mapScale(mapScale),
          m_tileSize(tileSize) {

}

Map::~Map() = default;

void Map::loadMap(const std::string &path, glm::ivec2 size) {
    char c;
    std::fstream mapFile;
    mapFile.open(path);

    glm::ivec2 source;

    for (int y = 0; y < size.y; y++) {
        for (int x = 0; x < size.x; x++) {
            mapFile.get(c);
            source.y = atoi(&c) * m_tileSize;
            mapFile.get(c);
            source.x = atoi(&c) * m_tileSize;

            Map::addTile(
                    source,
                    glm::vec2((float)x * getScaledTileSize(), (float)y * getScaledTileSize())
            );
            mapFile.ignore();
        }
    }

    mapFile.ignore();

    for (int y = 0; y < size.y; y++) {
        for (int x = 0; x < size.x; x++) {
            mapFile.get(c);
            if (c == '1') {
                auto &tCollider(entityManager.addEntity());
                tCollider.addComponent<ColliderComponent>(
                        "terrain",
                        glm::vec2((float) x * getScaledTileSize(), (float) y * getScaledTileSize()),
                        getScaledTileSize()
                );
                tCollider.addGroup(groupColliders);
            }
            mapFile.ignore();
        }
    }

    mapFile.close();
}

void Map::addTile(glm::vec2 source, glm::vec2 position) {
    auto &tile(entityManager.addEntity());
    tile.addComponent<TileComponent>(source, position, m_tileSize, m_mapScale, m_mapTexturePath);
    tile.addGroup(groupMap);
}
