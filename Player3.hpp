#pragma once
#include "Framework.hpp"
#include "Math.hpp"
#include "Camera.hpp"

namespace Player3 {

    // TODO: Modules/classes/namespaces!

    // Position
    SDL_Rect screenPosition { 48, 112, 64, 64 }; // left screen corner

    Vector2<float> position { 48, 112 };
    const float stepSize = 2;
    const float speed = stepSize * 2;

    // TEXTURES
    SDL_Texture* textureAtlas;

    // ANIMATION
    const int animationFrames(4);
    SDL_Rect spriteClips[animationFrames];
    int animationFrameInterval(5);           // TODO: in frames for now later as time/float.
    int animationFrame(0);
    float counter(0);                         // TODO: in frames later in time/float.

    // Frame independent.
    Vector2<float> lastPosition { 0, 0 };
    bool isMoving(false);
    const float duration(1);
    float elapsedTime(0);

    // Frame dependent.
    Vector2<float> moveDirection { 0, 0 };
    const float errorEdge(0.5);

    ErrorCode Create() {
        moveDirection = { position.x, position.y }; // So we don't start moving to { 0, 0 } at start.
        lastPosition = { position.x, position.y };
        return success;
    }

    const int IncrementAnimationFrame() {
        ++animationFrame;
        if (animationFrame == animationFrames) animationFrame = 0;
        return animationFrame;
        //return animationFrame |= animationFrames;
    }

    ErrorCode Create(SDL_Renderer* renderer) {

        SDL_Surface* tempSurface(IMG_Load("assets/player2_atlas.png"));
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

        if ((mouseBitMask & SDL_BUTTON_LMASK) != 0) {
            moveDirection = mousePosition;
            lastPosition = position;
            elapsedTime = 0;
        }
        if ( // Meaning we're moving. Unit we're close enough it counts as done.
            Math::Absolute(position.x - moveDirection.x) > errorEdge ||
            Math::Absolute(position.y - moveDirection.y) > errorEdge
            ) {
            //SDL_Log("We're moving!.");
            position = (Math::Lerp(lastPosition, moveDirection, Math::EasingFunctions::EaseOut(elapsedTime / duration)));
            elapsedTime += 0.01f;
        } else {
            elapsedTime = 0;
        }

        return success;
    }

    SDL_Rect RenderUpdate(SDL_Renderer* const renderer, Camera::Camera& camera) {
        const Vector2<float> cameraMoveToCenter = Camera::GetCameraScaleMovePosition(camera);
        const Vector2<float> renderedPosition { ceil((position.x - 32 + camera.position.x) * camera.zoom + cameraMoveToCenter.x), ceil((position.y - 48 + camera.position.y) * camera.zoom + cameraMoveToCenter.y) };
        const Vector2<float> renderedTransform { ceil(screenPosition.w * camera.zoom), ceil(screenPosition.h * camera.zoom) };
        const SDL_Rect rect { renderedPosition.x, renderedPosition.y, renderedTransform.x, renderedTransform.y };

        SDL_RenderCopy(renderer, textureAtlas, &spriteClips[animationFrame], &rect);

        return rect;
    }

};