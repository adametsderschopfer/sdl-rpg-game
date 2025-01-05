#pragma once

#include "SDL3/SDL.h"
#include "SDL3_image/SDL_image.h"
#include "string"
#include "glm/vec2.hpp"

class ColliderComponent;

enum groupLabels : std::size_t {
    groupMap,
    groupPlayers,
    groupEnemies,
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

    [[nodiscard]]
    bool isRunning() const { return m_isRunning; }

    static void addTile(glm::vec2 source, glm::vec2 position);

    static SDL_Renderer *renderer;
    static SDL_Event event;
    static std::vector<ColliderComponent *> colliders;

private:
    bool m_isRunning;

    SDL_Window *m_window;
    SDL_Renderer *m_renderer;
};