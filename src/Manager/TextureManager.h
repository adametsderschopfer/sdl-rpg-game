#pragma once

#include "SDL3/SDL.h"
#include "SDL3_image/SDL_image.h"

#include "iostream"
#include "memory"

namespace Manager {
    class TextureManager {
    public:
        static SDL_Texture *LoadTexture(const std::string &texturePath, SDL_Renderer *renderer);
    };
}
