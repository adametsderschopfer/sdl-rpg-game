#pragma once

#include "ECS.h"
#include "TransformComponent.h"
#include "SDL3/SDL.h"

class TileComponent : public Component {
public:
    TileComponent() = default;

    TileComponent(glm::vec2 source, glm::vec2 position, float tSize, float tScale, const std::string &textureId) {
        m_texture = Game::assetsManager->getTexture(textureId);

        m_position = position;

        m_srcRect.x = source.x;
        m_srcRect.y = source.y;
        m_srcRect.w = m_srcRect.h = tSize;

        m_destRect.x = position.x;
        m_destRect.y = position.y;
        m_destRect.w = m_destRect.h = (tSize * tScale);
    }

    ~TileComponent() {
        SDL_DestroyTexture(m_texture);
    }

    void update() override {
        m_destRect.x = m_position.x - Game::camera.x;
        m_destRect.y = m_position.y - Game::camera.y;
    }

    void draw() override {
        TextureManager::draw(m_texture, m_srcRect, m_destRect, SDL_FLIP_NONE);
    }

    glm::vec2 &getPosition() { return m_position; };

private:
    SDL_Texture *m_texture{};
    SDL_FRect m_srcRect{}, m_destRect{};

    glm::vec2 m_position{};
};