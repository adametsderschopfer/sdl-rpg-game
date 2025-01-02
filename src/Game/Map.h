#include "Game.h"

class Map {
public:
    Map();

    ~Map();

    void loadMap(int loadMap[20][25]);

    void drawMap();

private:
    SDL_FRect m_destRect;

    SDL_Texture *m_dirt;
    SDL_Texture *m_grass;
    SDL_Texture *m_water;

    int m_map[20][25];
};