#include "Game.h"

Game *g_game = nullptr;

int main(int argc, char *argv[]) {
    (void) argc;
    (void) argv;

    g_game = new Game();

    if (!g_game->init("sdl_rpg_game", 1280, 720, false)) {
        return -1;
    }

    while (g_game->isRunning()) {
        g_game->handleEvents();
        g_game->update();
        g_game->render();
    }

    g_game->destroy();

    return 0;
}