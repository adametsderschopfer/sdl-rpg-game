#pragma once

#include "../Game/Game.h"

class TextureManager {
public:
    static SDL_Texture *loadTexture(const std::string &texturePath);

    static void draw(SDL_Texture *texture, SDL_FRect srcRect, SDL_FRect destRect);
    static void draw(SDL_Texture *texture, SDL_FRect srcRect, SDL_FRect destRect, SDL_FlipMode flip);
};
