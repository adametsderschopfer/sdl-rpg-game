#include "GameObject.h"
#include "../../Manager/TextureManager.h"

GameObject::GameObject(
        const std::string &textureSheet,
        SDL_Renderer *renderer,
        const glm::vec2 &position
) :
        m_renderer(renderer),
        m_position(position) {
    m_objTexture = TextureManager::LoadTexture(textureSheet, renderer);
}

GameObject::~GameObject() = default;

void GameObject::update() {
    m_position.x += 1;
    m_position.y += 1;

//    m_srcRect.w = 32;
//    m_srcRect.h = 32;
//    m_srcRect.x = 0;
//    m_srcRect.y = 0;

    m_destRect.x = m_position.x;
    m_destRect.y = m_position.y;
    m_destRect.w = m_srcRect.w * 2;
    m_destRect.h = m_srcRect.h * 2;
}

void GameObject::render() {
    SDL_RenderTexture(m_renderer, m_objTexture, nullptr, &m_destRect);
}
