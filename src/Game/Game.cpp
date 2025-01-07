#include "Game.h"
#include "Map.h"

#include "../Core/ECS/Components.h"
#include "../Core/Collision.h"

Map* map;

EntityManager entityManager;
auto &playerEntity(entityManager.addEntity());

SDL_Renderer *Game::renderer = nullptr;
SDL_Event Game::event;
SDL_FRect Game::camera = {0,0,800,640};
bool Game::isRunning = false;

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

	map = new Map("assets/terrain_ss.png", 32.f, 2.f);
    map->loadMap("assets/map.map", glm::ivec2(25, 20));

    playerEntity.addComponent<TransformComponent>(2.f);
    playerEntity.addComponent<SpriteComponent>("assets/player_anims.png", true);
    playerEntity.addComponent<PlayerController>();
    playerEntity.addComponent<ColliderComponent>("Player");
    playerEntity.addGroup(groupPlayers);

    /* DEVELOPMENT ... */

    isRunning = true;
    return true;
}

auto &tiles(entityManager.getGroup(groupMap));
auto &players(entityManager.getGroup(groupPlayers));
auto &colliders(entityManager.getGroup(groupColliders));

void Game::handleEvents() {
    SDL_PollEvent(&event);

    switch (event.type) {
        case SDL_EVENT_QUIT:
            isRunning = false;
            break;

        default:
            break;
    }
}

void Game::update() {
    TransformComponent *pTrs = &playerEntity.getComponent<TransformComponent>();
    SDL_FRect playerCol = playerEntity.getComponent<ColliderComponent>().getCollider();
    glm::vec2 playerPos = pTrs->getPosition();

    entityManager.refresh();
    entityManager.update();

    for (const auto &collider: colliders) {
        SDL_FRect cCol = collider->getComponent<ColliderComponent>().getCollider();
        if (Collision::AABB(cCol, playerCol)) {
            pTrs->setPosition(playerPos);
        }
    }

    // Todo: camera class
    camera.x = pTrs->getPosition().x - 400;
    camera.y = pTrs->getPosition().y - 320;

    if (camera.x < 0) {
        camera.x = 0;
    }

    if (camera.y < 0) {
        camera.y = 0;
    }

    if (camera.x > camera.w) {
        camera.x = camera.w;
    }

    if (camera.y > camera.h) {
        camera.y = camera.h;
    }
}

void Game::render() {
    SDL_RenderClear(Game::renderer);

    for (auto &tile: tiles) {
        tile->draw();
    }

    for (auto &c: colliders) {
        c->draw();
    }

    for (auto &player: players) {
        player->draw();
    }

    SDL_RenderPresent(Game::renderer);
}

void Game::destroy() {
    SDL_DestroyWindow(m_window);
    SDL_DestroyRenderer(Game::renderer);
    SDL_Quit();
}
