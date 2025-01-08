#include "AssetsManager.h"
#include "../Core/ECS/Components.h"

AssetsManager::AssetsManager(EntityManager *entityManager) : m_entityManager(entityManager) {

}

AssetsManager::~AssetsManager() = default;

void AssetsManager::addTexture(const std::string &id, const std::string &path) {
    m_textures.emplace(id, TextureManager::loadTexture(path));
}

SDL_Texture *AssetsManager::getTexture(const std::string &id) {
    return m_textures[id];
}

void AssetsManager::createProjectTile(glm::vec2 position, int range, int speed, glm::vec2 velocity, const std::string &id) {
    auto &projectile(m_entityManager->addEntity());
    projectile.addComponent<TransformComponent>(position, 32, 32);  // todo magic numbers us DEFINE TILE_WIDTH
    projectile.addComponent<SpriteComponent>(id);
    projectile.addComponent<ProjectileComponent>(range, speed, velocity);
    projectile.addComponent<ColliderComponent>("projectile");
    projectile.addGroup(groupProjectiles);
}
