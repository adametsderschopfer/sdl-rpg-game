#pragma once

#include "ECS.h"
#include "Components.h"

class ProjectileComponent : public Component {
public:
    ProjectileComponent(int range, int speed, glm::vec2 velocity)
            : m_range(range),
              m_speed(speed),
              m_velocity(velocity) {};

    ~ProjectileComponent() = default;


    void init() override {
        m_transform = &entity->getComponent<TransformComponent>();
//        m_transform->setVelocity(m_velocity);
    }

    void update() override {
//        m_distance += m_speed;

        if (m_distance > m_range) {
            entity->destroy();
        } else if (
                m_transform->getPosition().x > Game::camera.x + Game::camera.w ||
                m_transform->getPosition().x < Game::camera.x ||
                m_transform->getPosition().y > Game::camera.y + Game::camera.h ||
                m_transform->getPosition().y < Game::camera.y
                ) {
            entity->destroy();
        }
    }

private:
    TransformComponent *m_transform{};

    int m_range = 0;
    int m_speed = 0;
    int m_distance = 0;

    glm::vec2 m_velocity{};
};