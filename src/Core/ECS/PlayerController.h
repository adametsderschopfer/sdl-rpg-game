#pragma once

#include "./ECS.h"
#include "./Components.h"
#include "../../Game/Game.h"

#include "glm/vec2.hpp"

class PlayerController : public Component {
public:
    void init() override {
        m_transform = &entity->getComponent<TransformComponent>();
    }

    void update() override {
        const glm::vec2 currentVelocity = m_transform->getVelocity();

        // todo: refactor
        setVelocityByEvent(SDL_SCANCODE_W, glm::vec2(currentVelocity.x, -1.f), glm::vec2(currentVelocity.x, 0));
        setVelocityByEvent(SDL_SCANCODE_S, glm::vec2(currentVelocity.x, 1.f), glm::vec2(currentVelocity.x, 0));
        setVelocityByEvent(SDL_SCANCODE_A, glm::vec2(-1.f, currentVelocity.y), glm::vec2(0, currentVelocity.y));
        setVelocityByEvent(SDL_SCANCODE_D, glm::vec2(1.f, currentVelocity.y), glm::vec2(0, currentVelocity.y));
    }

    void setVelocityByEvent(SDL_Scancode scancode, glm::vec2 velocityActive, glm::vec2 velocityNonActive) {
        if (Game::event.key.scancode != scancode) {
            return;
        }

        if (Game::event.type == SDL_EVENT_KEY_DOWN) {
            m_transform->setVelocity(velocityActive);
        } else if (Game::event.type == SDL_EVENT_KEY_UP) {
            m_transform->setVelocity(velocityNonActive);
        }
    }

private:
    TransformComponent *m_transform{};
};