#pragma once

#include "../../Game/Game.h"

#include "../../Manager/TextureManager.h"
#include "glm/vec2.hpp"

class GameObject {
public:
    GameObject(const std::string &textureSheet);

    ~GameObject();

    void update();

    void render();

private:
    SDL_Texture *m_objTexture;
    SDL_FRect m_destRect = {0, 0, 0, 0};
};