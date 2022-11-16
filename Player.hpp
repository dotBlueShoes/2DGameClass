#pragma once
#include "Framework.hpp"

namespace Player {

    // TODO: Modules/classes/namespaces!

    // Position
    SDL_Rect screenPosition { 16, 32, 64, 64 }; // left screen corner
    const float stepSize = 2;
    const float speed = stepSize * 2;
    bool canMoveDown = true, canMoveUp = true;

    // TEXTURES
    SDL_Texture* textureAtlas;

    // ANIMATION
    const int animationFrames(4);
    SDL_Rect spriteClips[animationFrames];
    int animationFrameInterval(5);           // TODO: in frames for now later as time/float.
    int animationFrame(0);
    float counter(0);                         // TODO: in frames later in time/float.

    const int IncrementAnimationFrame() {
        ++animationFrame;
        if (animationFrame == animationFrames) animationFrame = 0;
        return animationFrame;
        //return animationFrame |= animationFrames;
    }

    ErrorCode Create(SDL_Renderer* renderer) {

        SDL_Surface* tempSurface(IMG_Load("assets/player_atlas.png"));
        textureAtlas = SDL_CreateTextureFromSurface(renderer, tempSurface);
        SDL_FreeSurface(tempSurface);

        if (textureAtlas == nullptr) SDL_Log("Unable to load Player Texture");

        // 192x192 sprite_atlas
        // 64x64 sprite

        spriteClips[0].x = 0;
        spriteClips[0].y = 0;
        spriteClips[0].w = 32;
        spriteClips[0].h = 32;

        spriteClips[1].x = 32;
        spriteClips[1].y = 0;
        spriteClips[1].w = 32;
        spriteClips[1].h = 32;

        spriteClips[2].x = 64;
        spriteClips[2].y = 0;
        spriteClips[2].w = 32;
        spriteClips[2].h = 32;

        spriteClips[3].x = 0;
        spriteClips[3].y = 32;
        spriteClips[3].w = 32;
        spriteClips[3].h = 32;

        return success;
    }

    ErrorCode Destroy() {
        SDL_DestroyTexture(textureAtlas);
        return success;
    }

    ErrorCode LogicUpdate(const float& frame, const Vector2<float>& mousePosition, const Uint32& mouseBitMask, const Uint8* const keyboard) {

        // Player Aniamtion
        ++counter;
        if (counter > animationFrameInterval) {
            counter = 0;
            IncrementAnimationFrame();
        }

            // screenPosition.x = (int)(frame * 2.0f);
        if (canMoveUp && keyboard[SDL_SCANCODE_UP]) screenPosition.y -= speed;
        if (keyboard[SDL_SCANCODE_RIGHT]) screenPosition.x += speed;
        if (canMoveDown && keyboard[SDL_SCANCODE_DOWN]) screenPosition.y += speed;
        if (keyboard[SDL_SCANCODE_LEFT]) screenPosition.x -= speed;
        return success;
    }

    SDL_Rect RenderUpdate(SDL_Renderer* const renderer, Camera::Camera& camera) {
        const Vector2<float> cameraMoveToCenter = Camera::GetCameraScaleMovePosition(camera);
        const Vector2<float> renderedPosition { ceil((screenPosition.x + camera.position.x) * camera.zoom + cameraMoveToCenter.x), ceil((screenPosition.y + camera.position.y) * camera.zoom + cameraMoveToCenter.y) };
        const Vector2<float> renderedTransform { ceil(screenPosition.w * camera.zoom), ceil(screenPosition.h * camera.zoom) };
        const SDL_Rect rect { renderedPosition.x, renderedPosition.y, renderedTransform.x, renderedTransform.y };

        SDL_RenderCopy(renderer, textureAtlas, &spriteClips[animationFrame], &rect);

        return rect;
    }

};