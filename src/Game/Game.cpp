#include "Game.h"
#include "memory"
#include "Map.h"

#include "../Core/ECS/Components.h"
#include "../Core/Collision.h"

std::shared_ptr<Map> testMap;

EntityManager entityManager;
auto &playerEntity(entityManager.addEntity());
auto &wallEntity(entityManager.addEntity());

SDL_Renderer *Game::renderer = nullptr;
SDL_Event Game::event;

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

    /** EX*/
    testMap = std::make_shared<Map>();

    playerEntity.addComponent<TransformComponent>(glm::vec2(100, 500));
    playerEntity.addComponent<SpriteComponent>("assets/player.png");
    playerEntity.addComponent<PlayerController>();
    playerEntity.addComponent<ColliderComponent>("Player");

    wallEntity.addComponent<TransformComponent>(glm::vec2(200, 300), 150.f, 75.f);
    wallEntity.addComponent<SpriteComponent>("assets/dirt.jpg");
    wallEntity.addComponent<ColliderComponent>("wall");


    /** EX*/

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
    /** EX */
    entityManager.update();

    if (Collision::AABB(playerEntity.getComponent<ColliderComponent>().getCollider(), wallEntity.getComponent<ColliderComponent>().getCollider())) {
        std::cout << "wall hit!" << std::endl;
    }

    /** EX */
}

void Game::render() {
    SDL_RenderClear(Game::renderer);

    /** EX */
    testMap->drawMap();
    entityManager.draw();
    /** EX */

    SDL_RenderPresent(Game::renderer);
}

void Game::destroy() {
    SDL_DestroyWindow(m_window);
    SDL_DestroyRenderer(Game::renderer);
    SDL_Quit();
}
