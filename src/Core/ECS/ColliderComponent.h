#pragma once

#include <utility>

#include "string"
#include "./ECS.h"
#include "./Components.h"
#include "glm/vec2.hpp"

class ColliderComponent : public Component {
public:
    explicit ColliderComponent(std::string mTag) : m_tag(std::move(mTag)) {}

    ColliderComponent(std::string mTag, glm::vec2 position, float size) : m_tag(std::move(mTag)) {
        m_collider.x = position.x;
        m_collider.y = position.y;
        m_collider.w = m_collider.h = size;
    }

    void init() override {
        if (!entity->hasComponent<TransformComponent>()) {
            entity->addComponent<TransformComponent>();
        }

        m_transform = &entity->getComponent<TransformComponent>();

        m_borderTexture = TextureManager::loadTexture("assets/ColTex.png");
        m_borderSrcRect = {0, 0, 32, 32};
        m_borderDestRect = {m_collider.x, m_collider.y, m_collider.w, m_collider.h};
    }

    void update() override {
        if (m_tag != "terrain") {
            m_collider.x = m_transform->getPosition().x;
            m_collider.y = m_transform->getPosition().y;

            m_collider.w = m_transform->getScaledWidth();
            m_collider.h = m_transform->getScaledHeight();
        }

        m_borderDestRect.x = m_collider.x - Game::camera.x;
        m_borderDestRect.y = m_collider.y - Game::camera.y;
    }

    void draw() override {
        // todo: add debugger flag
//        TextureManager::draw(m_borderTexture, m_borderSrcRect, m_borderDestRect);
    }

    [[nodiscard]] const SDL_FRect &getCollider() const {
        return m_collider;
    }

    [[nodiscard]] const std::string &getTag() const { return m_tag; }

private:
    SDL_FRect m_collider{};
    std::string m_tag;

    SDL_Texture *m_borderTexture{};
    SDL_FRect m_borderSrcRect{}, m_borderDestRect{};

    TransformComponent *m_transform{};
};