#pragma once

#include "ECS.h"
#include "TransformComponent.h"
#include "TransformComponent.h"
#include "SDL3/SDL.h"

class TileComponent : public Component {
public:
    TileComponent() = default;

    TileComponent(glm::vec2 source, glm::vec2 position, const std::string &path) {
        m_texture = TextureManager::loadTexture(path);

        m_srcRect.x = source.x;
        m_srcRect.y = source.y;
        m_srcRect.w = m_srcRect.h = 32.f; // todo magic number

        m_destRect.x = position.x;
        m_destRect.y = position.y;
        m_destRect.w = m_destRect.h = 64.f; // todo magic number
    }

    ~TileComponent() {
        SDL_DestroyTexture(m_texture);
    }

    void draw() override {
        TextureManager::draw(m_texture, &m_srcRect, &m_destRect, SDL_FLIP_NONE);
    }

private:
    SDL_Texture *m_texture;
    SDL_FRect m_srcRect{}, m_destRect{};
};