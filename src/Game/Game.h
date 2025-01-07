#pragma once

#include "SDL3/SDL.h"
#include "SDL3_image/SDL_image.h"
#include "string"
#include "glm/vec2.hpp"

class ColliderComponent;
class AssetsManager;

enum groupLabels : std::size_t {
    groupMap,
    groupPlayers,
    groupColliders
};

class Game {
public:
    bool init(
            const char *title,
            int width,
            int height,
            bool fullScreen
    );

    void handleEvents();

    void update();

    void render();

    void destroy();

    static SDL_Renderer *renderer;
    static SDL_Event event;
    static bool isRunning;
    static SDL_FRect camera;
    static AssetsManager *assetsManager;

private:
    SDL_Window *m_window;
};