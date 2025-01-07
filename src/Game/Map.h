#pragma once

#include "string"
#include "glm/vec2.hpp"

class Map {
public:
    Map(std::string textureId, float tileSize, float mapScale);

    ~Map();

    void loadMap(const std::string &path, glm::ivec2 size);

    void addTile(glm::vec2 source, glm::vec2 position);

    [[nodiscard]] float getScaledTileSize() const { return m_tileSize * m_mapScale; }

private:
    const std::string m_textureId;
    float m_mapScale;
    float m_tileSize;
};