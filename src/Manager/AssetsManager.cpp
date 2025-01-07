#include "AssetsManager.h"

AssetsManager::AssetsManager(EntityManager *entityManager) {

}

AssetsManager::~AssetsManager() {

}

void AssetsManager::addTexture(const std::string &id, const std::string &path) {
    m_textures.emplace(id, TextureManager::loadTexture(path));
}

SDL_Texture *AssetsManager::getTexture(const std::string &id) {
    return m_textures[id];
}
