#pragma once

#include "map"
#include "string"
#include "TextureManager.h"
#include "glm/vec2.hpp"
#include "../Core/ECS/ECS.h"

class AssetsManager {
public:
    explicit AssetsManager(EntityManager *entityManager);

    ~AssetsManager();

    virtual void addTexture(const std::string &id, const std::string &path);

    SDL_Texture *getTexture(const std::string &id);

private:
    std::map<std::string, SDL_Texture *> m_textures;
};

