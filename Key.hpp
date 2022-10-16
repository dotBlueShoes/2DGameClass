#pragma once
#include "Framework.hpp"

namespace Key {

	// Position
	SDL_Rect screenPosition { 0, 0, 64, 64 }; // left screen corner

	// TEXTURES
	SDL_Texture* texture;
    SDL_Rect spriteRect;

    ErrorCode Create(SDL_Renderer* renderer) {

        SDL_Surface* tempSurface(IMG_Load("assets/key.png"));
        texture = SDL_CreateTextureFromSurface(renderer, tempSurface);
        SDL_FreeSurface(tempSurface);

        if (texture == nullptr) SDL_Log("Unable to load Key Texture");

        // 64x64 sprite

        spriteRect.x = 0;
        spriteRect.y = 0;
        spriteRect.w = 32;
        spriteRect.h = 32;

        return success;
    }

    ErrorCode Destroy() {
        SDL_DestroyTexture(texture);
        return success;
    }

    ErrorCode RenderUpdate(SDL_Renderer* const renderer) {
        SDL_RenderCopy(renderer, texture, &spriteRect, &screenPosition);
        return success;
    }

}