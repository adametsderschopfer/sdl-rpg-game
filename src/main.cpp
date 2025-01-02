#include "Game/Game.h"

Game *g_game = nullptr;

int main(int argc, char *argv[]) {
    const int FPS = 60;
    const int frameDelay = 1000 / FPS;

    Uint32 frameStart;
    int frameTime;

    g_game = new Game();

    if (!g_game->init("sdl_rpg_game", 1280, 720, false)) {
        return -1;
    }

    while (g_game->isRunning()) {
        frameStart = SDL_GetTicks();

        g_game->handleEvents();
        g_game->update();
        g_game->render();

        frameTime = SDL_GetTicks() - frameStart;

        if (frameDelay > frameTime) {
            SDL_Delay(frameDelay - frameTime);
        }
    }

    g_game->destroy();

    return 0;
}