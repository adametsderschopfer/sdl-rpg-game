#include "TextureManager.h"

SDL_Texture *TextureManager::LoadTexture(const std::string &texturePath, SDL_Renderer *renderer) {
    SDL_Surface *tempSurface = IMG_Load(texturePath.c_str());

    if (!tempSurface) {
        throw std::runtime_error("\nFailed to load surface: " + texturePath);
    }

    SDL_Texture *rawTexture = SDL_CreateTextureFromSurface(renderer, tempSurface);
    SDL_DestroySurface(tempSurface);
    if (!rawTexture) {
        throw std::runtime_error("\nFailed to create texture from surface: " + texturePath);
    }

    return rawTexture;
}
