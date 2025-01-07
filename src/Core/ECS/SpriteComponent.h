#pragma once

#include "./ECS.h"
#include "./Components.h"
#include "Animation.h"
#include "map"
#include "glm/vec2.hpp"

#include "SDL3/SDL.h"
#include "../../Manager/TextureManager.h"

class SpriteComponent : public Component {
public:
    SpriteComponent() = default;

    explicit SpriteComponent(const std::string &path) {
        setTexture(path);
    };

    explicit SpriteComponent(const std::string &path, bool isAnimated) {
        m_animated = isAnimated;

        Animation idle = Animation(0, 3, 100);
        Animation walk = Animation(1, 8, 100);

        animations.emplace("Idle", idle);
        animations.emplace("Walk", walk);

        play("Idle");

        setTexture(path);
    };

    ~SpriteComponent() {
        SDL_DestroyTexture(m_texture);
    }

    void init() override {
        m_transform = &entity->getComponent<TransformComponent>();

        m_srcRect.x = m_srcRect.y = 0;
        m_srcRect.w = m_transform->getWidth();
        m_srcRect.h = m_transform->getHeight();
    }

    void play(const std::string &animName) {
        m_frames = animations[animName].frames;
        m_animIndex = animations[animName].index;
        m_speed = animations[animName].speed;
    }

    void update() override {
        if (m_animated) {
            m_srcRect.x = m_srcRect.w * (float)(SDL_GetTicks() / m_speed % m_frames);
        }

        m_srcRect.y = (float)m_animIndex * m_transform->getHeight();

        m_destRect.x = m_transform->getPosition().x - Game::camera.x;
        m_destRect.y = m_transform->getPosition().y - Game::camera.y;

        m_destRect.w = m_transform->getScaledWidth();
        m_destRect.h = m_transform->getScaledHeight();
    }

    void draw() override {
        TextureManager::draw(m_texture, m_srcRect, m_destRect, m_spriteFlip);
    }

    void setTexture(const std::string &path) {
        m_texture = TextureManager::loadTexture(path);
    }

    void setSpriteFlip(SDL_FlipMode mSpriteFlip) {
        m_spriteFlip = mSpriteFlip;
    }

private:
    TransformComponent *m_transform{};

    SDL_Texture *m_texture{};
    SDL_FRect m_destRect{}, m_srcRect{};

    int m_animIndex = 0;
    std::map<const std::string, Animation> animations;

    SDL_FlipMode m_spriteFlip = SDL_FLIP_NONE;

    bool m_animated = false;
    int m_frames = 0;
    int m_speed = 100;
};