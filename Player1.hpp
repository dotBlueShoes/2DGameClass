#pragma once
#include "Framework.hpp"
#include "Math.hpp"

namespace Player1 {

	const float stepSize = 1;
	const float speed = stepSize * 5;

	const Color color { 255, 0, 0, 255 };
	const Vector2<float> transform { 100, 100 };

	Vector2<float> position { 400, 100 };

	// LERP !

	ErrorCode LogicUpdate(const float& deltaTime, const Vector2<Sint32>& mousePosition, const Uint32& mouseBitMask, const Uint8* const keyboard) {

		//position.x = 

		if (keyboard[SDL_SCANCODE_UP]) position.y -= speed;
		if (keyboard[SDL_SCANCODE_RIGHT]) position.x += speed;
		if (keyboard[SDL_SCANCODE_DOWN]) position.y += speed;
		if (keyboard[SDL_SCANCODE_LEFT]) position.x -= speed;

		return success;
	}

	ErrorCode RenderUpdate(SDL_Renderer* const renderer, Camera::Camera& camera) {
		Vector2<float> renderedPosition { position.x + camera.position.x, position.y + camera.position.y };

		Camera::CameraMoveBoundry(camera, renderedPosition);
		Camera::CameraFollowBoundry(camera, renderedPosition, transform.x, speed);

		Draw::Square(renderer, renderedPosition, transform, color);

		

		return success;
	}

};