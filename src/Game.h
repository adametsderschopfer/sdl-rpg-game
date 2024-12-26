#include "SDL3/SDL.h"
#include "SDL3_image/SDL_image.h"
#include "iostream"

class Game {
public:
    Game();

    ~Game();

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

private:
    bool m_isRunning;

    SDL_Window *m_window;
    SDL_Renderer *m_renderer;
};