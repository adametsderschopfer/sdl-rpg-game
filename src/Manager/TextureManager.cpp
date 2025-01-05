#include "TextureManager.h"
#include "iostream"

SDL_Texture *TextureManager::loadTexture(const std::string &texturePath) {
    SDL_Surface *tempSurface = IMG_Load(texturePath.c_str());

    if (!tempSurface) {
        throw std::runtime_error("\nFailed to load surface: " + texturePath);
    }

    SDL_Texture *rawTexture = SDL_CreateTextureFromSurface(Game::renderer, tempSurface);
    SDL_DestroySurface(tempSurface);
    if (!rawTexture) {
        throw std::runtime_error("\nFailed to create texture from surface: " + texturePath);
    }

    return rawTexture;
}

void TextureManager::draw(SDL_Texture *texture, const SDL_FRect *srcRect, const SDL_FRect *destRect) {
    SDL_RenderTexture(Game::renderer, texture, srcRect, destRect);
}

void
TextureManager::draw(SDL_Texture *texture, const SDL_FRect *srcRect, const SDL_FRect *destRect, SDL_FlipMode flip) {
    SDL_RenderTextureRotated(Game::renderer, texture, srcRect, destRect, 0, nullptr, flip);
}
