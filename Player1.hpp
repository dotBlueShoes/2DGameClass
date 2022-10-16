#pragma once
#include "Framework.hpp"
#include "Math.hpp"

namespace Player1 {

	const Color color { 255, 0, 0, 255 };
	const Vector2<float> transform { 100, 100 };

	Vector2<float> position { 400, 100 };

	// LERP !

	ErrorCode LogicUpdate(const float& deltaTime, const Vector2<Sint32>& mousePosition, const Uint32& mouseBitMask, const Uint8* const keyboard) {

		if (keyboard[SDL_SCANCODE_UP]) position.y -= 1;
		if (keyboard[SDL_SCANCODE_RIGHT]) position.x += 1;
		if (keyboard[SDL_SCANCODE_DOWN]) position.y += 1;
		if (keyboard[SDL_SCANCODE_LEFT]) position.x -= 1;

		return success;
	}

	ErrorCode RenderUpdate(SDL_Renderer* const renderer) {
		Draw::Square(renderer, position, transform, color);
		return success;
	}

};