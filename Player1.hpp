#pragma once
#include "Framework.hpp"
#include "Math.hpp"

namespace Player1 {

	const float stepSize = 2;
	const float speed = stepSize * 2;

	const Color color { 255, 0, 0, 255 };
	const Vector2<float> transform { 32, 32 };

	// Represents the center of the square.
	Vector2<float> position { transform.x/2, transform.y/2 };

	// LERP !

	ErrorCode LogicUpdate(const float& deltaTime, const Vector2<float>& mousePosition, const Uint32& mouseBitMask, const Uint8* const keyboard) {

		//position.x = 

		if (keyboard[SDL_SCANCODE_UP]) position.y -= speed;
		if (keyboard[SDL_SCANCODE_RIGHT]) position.x += speed;
		if (keyboard[SDL_SCANCODE_DOWN]) position.y += speed;
		if (keyboard[SDL_SCANCODE_LEFT]) position.x -= speed;

		return success;
	}

	ErrorCode RenderUpdate(SDL_Renderer* const renderer, Camera::Camera& camera) {
		const Vector2<float> cameraMoveToCenter = Camera::GetCameraScaleMovePosition(camera);
		const Vector2<float> renderedPosition { ceil((position.x  + camera.position.x ) * camera.zoom + cameraMoveToCenter.x), ceil((position.y + camera.position.y) * camera.zoom + cameraMoveToCenter.y) };
		//const Vector2 renderedPosition { ceil(position.x * camera.zoom), ceil(position.y * camera.zoom)};
		const Vector2<float> renderedTransform { ceil(transform.x * camera.zoom), ceil(transform.y * camera.zoom) };

		//printf("pl1: %f, %f\n", renderedPosition.x, renderedPosition.y);

		//Camera::CameraMoveBoundry(camera, renderedPosition);
		//Camera::CameraFollowBoundry(camera, renderedPosition, renderedTransform.x, speed);
		//Camera::CameraBothBoundry(camera, renderedPosition, renderedTransform.x, speed);

		Draw::Square(renderer, renderedPosition, renderedTransform, color);

		return success;
	}

};