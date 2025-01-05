#pragma once

#include "string"
#include "glm/vec2.hpp"

class Map {
public:
    Map();

    ~Map();

    static void loadMap(const std::string &path, glm::ivec2 size);
};