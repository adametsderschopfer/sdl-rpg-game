#include "Game.h"
#include "Map.h"

#include "../Core/ECS/Components.h"
#include "../Core/Collision.h"

/* DEVELOPMENT ... */
EntityManager entityManager;
auto &playerEntity(entityManager.addEntity());
/* DEVELOPMENT ... */

SDL_Renderer *Game::renderer = nullptr;
SDL_Event Game::event;
std::vector<ColliderComponent *> Game::colliders;

bool Game::init(const char *title, int width, int height, bool fullScreen) {
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("SDL_Init(SDL_INIT_VIDEO) failed (%s)", SDL_GetError());
        return false;
    }

    int flags = 0;

    if (fullScreen) {
        flags = SDL_WINDOW_FULLSCREEN;
    }

    m_window = SDL_CreateWindow(title, width, height, flags);
    if (!m_window) {
        SDL_Log("SDL_CreateWindow failed (%s)", SDL_GetError());
        SDL_Quit();
        return false;
    }

    Game::renderer = SDL_CreateRenderer(m_window, nullptr);
    if (!Game::renderer) {
        SDL_Log("SDL_CreateRenderer failed (%s)", SDL_GetError());
        SDL_Quit();
        return false;
    }

    SDL_SetRenderDrawColor(Game::renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);

    /* DEVELOPMENT ... */
    playerEntity.addComponent<TransformComponent>(glm::vec2(100, 500));
    playerEntity.addComponent<SpriteComponent>("assets/player_anims.png", true);
    playerEntity.addComponent<PlayerController>();
    playerEntity.addComponent<ColliderComponent>("Player");
    playerEntity.addGroup(groupPlayers);

    Map::loadMap("assets/map_test.csv", glm::vec2(30, 10));
    /* DEVELOPMENT ... */

    m_isRunning = true;
    return true;
}

void Game::handleEvents() {
    SDL_PollEvent(&event);

    switch (event.type) {
        case SDL_EVENT_QUIT:
            m_isRunning = false;
            break;

        default:
            break;
    }
}

void Game::update() {
    entityManager.refresh();
    entityManager.update();

    for (const auto &_collider: colliders) {
        Collision::AABB(playerEntity.getComponent<ColliderComponent>(), *_collider);
    }
}

auto &tiles(entityManager.getGroup(groupMap));
auto &players(entityManager.getGroup(groupPlayers));
auto &enemies(entityManager.getGroup(groupEnemies));

void Game::render() {
    SDL_RenderClear(Game::renderer);

    for (const auto &tile: tiles) {
        tile->draw();
    }

    for (const auto &enemy: enemies) {
        enemy->draw();
    }

    for (const auto &player: players) {
        player->draw();
    }

    SDL_RenderPresent(Game::renderer);
}

void Game::destroy() {
    SDL_DestroyWindow(m_window);
    SDL_DestroyRenderer(Game::renderer);
    SDL_Quit();
}

void Game::addTile(glm::vec2 source, glm::vec2 position) {
    auto &tile(entityManager.addEntity());
    tile.addComponent<TileComponent>(source, position, "assets/map_ss.png"); // todo magic number
    tile.addGroup(groupMap);
}
