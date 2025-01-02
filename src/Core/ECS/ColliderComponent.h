#pragma once

#include <utility>

#include "string"
#include "./ECS.h"
#include "./Components.h"
#include "glm/vec2.hpp"

class ColliderComponent : public Component {
public:
    explicit ColliderComponent(std::string mTag) : m_tag(std::move(mTag)) {}

    void init() override {
        if (!entity->hasComponent<TransformComponent>()) {
            entity->addComponent<TransformComponent>();
        }

        m_transform = &entity->getComponent<TransformComponent>();
    }

    void update() override {
        m_collider.x = m_transform->getPosition().x;
        m_collider.y = m_transform->getPosition().y;

        m_collider.w = m_transform->getScaledWidth();
        m_collider.h = m_transform->getScaledHeight();
    }

    [[nodiscard]] const SDL_FRect &getCollider() const {
        return m_collider;
    }

private:
    SDL_FRect m_collider{};
    std::string m_tag;

    TransformComponent *m_transform{};
};