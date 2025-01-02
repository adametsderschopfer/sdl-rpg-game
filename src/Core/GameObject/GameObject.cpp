#include "GameObject.h"

GameObject::GameObject(const std::string &textureSheet)
        : m_objTexture(TextureManager::loadTexture(textureSheet)) {
}

GameObject::~GameObject() = default;

void GameObject::update() {
    m_destRect.w = 32 * 2;
    m_destRect.h = 32 * 2;
}

void GameObject::render() {
    SDL_RenderTexture(Game::renderer, m_objTexture, nullptr, &m_destRect);
}
