#include "Game.h"
#include "Manager/TextureManager.h"

SDL_Texture *playerTexture;
SDL_FRect *srcRect, *destRect = new SDL_FRect(0,0,0,0);

Game::Game() {
}

Game::~Game() {

}

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

    m_renderer = SDL_CreateRenderer(m_window, nullptr);
    if (!m_renderer) {
        SDL_Log("SDL_CreateRenderer failed (%s)", SDL_GetError());
        SDL_Quit();
        return false;
    }

    SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);

    /** EX*/

    playerTexture = Manager::TextureManager::LoadTexture("assets/player.jpg", m_renderer);

    /** EX*/

    m_isRunning = true;
    return true;
}

void Game::handleEvents() {
    SDL_Event event;
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
    // todo: update here

    /** EX*/

    destRect->h = 32;
    destRect->w = 32;

    /** EX*/
}

void Game::render() {
    SDL_RenderClear(m_renderer);

    /** EX*/

    SDL_RenderTexture(m_renderer, playerTexture, nullptr, destRect);

    /** EX*/

    SDL_RenderPresent(m_renderer);
}

void Game::destroy() {
    SDL_DestroyWindow(m_window);
    SDL_DestroyRenderer(m_renderer);
    SDL_Quit();
}
