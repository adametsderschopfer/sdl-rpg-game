#pragma once

#include "string"
#include "glm/vec2.hpp"
#include "SDL3/SDL.h"

class GameObject {
public:
    GameObject(
            const std::string &textureSheet,
            SDL_Renderer *renderer,
            const glm::vec2 &position
    );

    ~GameObject();

    void update();

    void render();

private:
    SDL_Renderer *m_renderer;

    glm::vec2 m_position;

    SDL_Texture *m_objTexture;
    SDL_FRect m_srcRect = {0, 0, 0, 0}, m_destRect = {0, 0, 0, 0};
};