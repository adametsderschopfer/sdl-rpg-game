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

    // GameObjects
    void createProjectTile(glm::vec2 position, int range, int speed, glm::vec2 velocity, const std::string &id);

    // Texture Management
    virtual void addTexture(const std::string &id, const std::string &path);

    SDL_Texture *getTexture(const std::string &id);

private:
    EntityManager *m_entityManager;

    std::map<std::string, SDL_Texture *> m_textures;
};

