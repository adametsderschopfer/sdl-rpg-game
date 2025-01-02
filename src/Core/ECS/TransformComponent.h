#pragma once

#include "./ECS.h"
#include "./Components.h"
#include "glm/vec2.hpp"

class TransformComponent : public Component {
public:
    explicit TransformComponent() = default;

    explicit TransformComponent(glm::vec2 _pos) {
        m_position = glm::vec2(_pos);
    }

    explicit TransformComponent(
            glm::vec2 _pos,
            float height,
            float width,
            glm::vec2 scale = glm::vec2(1.f)
    ) {
        m_position = glm::vec2(_pos);
        m_width = width;
        m_height = height;
        m_scale = scale;
    }

    void init() override {
        m_velocity.x = 0;
        m_velocity.y = 0;
    }

    void update() override {
        m_position.x += m_velocity.x * m_speed;
        m_position.y += m_velocity.y * m_speed;
    }

    [[nodiscard]] float getHeight() const { return m_height; }

    [[nodiscard]] float getScaledHeight() const { return m_height * m_scale.y; }

    [[nodiscard]] float getWidth() const { return m_width; }

    [[nodiscard]] float getScaledWidth() const { return m_width * m_scale.x; }

    [[nodiscard]] glm::vec2 getScale() const { return m_scale; }

    [[nodiscard]] float getSpeed() const { return m_speed; }

    [[nodiscard]] const glm::vec2 &getPosition() const { return m_position; }

    [[nodiscard]] const glm::vec2 &getVelocity() const { return m_velocity; }

    void setVelocity(const glm::vec2 &velocity) { m_velocity = velocity; }

    void setPosition(const glm::vec2 &position) { m_position = position; }

    void setSpeed(float speed) { m_speed = speed; }

    void setScale(glm::vec2 scale) { m_scale = scale; }

    void setWidth(float width) { m_width = width; }

    void setHeight(float height) { m_height = height; }

private:
    float m_height = 32.f; // todo magic number
    float m_width = 32.f; // todo magic number
    glm::vec2 m_scale = glm::vec2(2.f); // todo magic number

    float m_speed = 3.f; // todo magic number

    glm::vec2 m_position{};
    glm::vec2 m_velocity{};
};