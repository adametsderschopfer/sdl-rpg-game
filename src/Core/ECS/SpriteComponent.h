#pragma once

#include "./ECS.h"
#include "./Components.h"
#include "glm/vec2.hpp"

#include "SDL3/SDL.h"
#include "../../Manager/TextureManager.h"

class SpriteComponent : public Component {
public:
    SpriteComponent() = default;

    explicit SpriteComponent(const std::string &path) {
        setTexture(path);
    };

    ~SpriteComponent() {
        SDL_DestroyTexture(m_texture);
    }

    void init() override {
        m_transform = &entity->getComponent<TransformComponent>();
    }

    void update() override {
        m_destRect.x = m_transform->getPosition().x;
        m_destRect.y = m_transform->getPosition().y;

        m_destRect.w = m_transform->getScaledWidth();
        m_destRect.h = m_transform->getScaledHeight();
    }

    void draw() override {
        TextureManager::draw(m_texture, m_destRect);
    }

    void setTexture(const std::string &path) {
        m_texture = TextureManager::loadTexture(path);
    }

private:
    TransformComponent *m_transform{};

    SDL_Texture *m_texture{};
    SDL_FRect m_destRect{};
};