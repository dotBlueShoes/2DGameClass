#pragma once
#include "Framework.hpp"
#include "Math.hpp"

namespace Player1 {

	const float stepSize = 1;
	const float speed = stepSize * 5;

	const Color color { 255, 0, 0, 255 };
	const Vector2<float> transform { 100, 100 };

	// Represents the top-left corner of the square
	Vector2<float> position { 400, 100 };

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
		/*
			0 < screen.x / 2
			zoom(0) = -inf
			zoom(1) = 0
			zoom(inf) = screen.x / 2
		*/



		// camera.zoom = 01: + newPosition(0, 0)
		// camera.zoom = 10: + newPosition(screenSize.x, screenSize.y)

		const Vector2 centralPosition { position.x - (transform.x / 2), position.y - (transform.y / 2) };

		const Vector2<float> renderedPosition { (centralPosition.x + camera.position.x) * camera.zoom, (centralPosition.y + camera.position.y) * camera.zoom };
		const Vector2<float> renderedTransform { transform.x * camera.zoom, transform.y * camera.zoom };

		//Camera::CameraMoveBoundry(camera, renderedPosition);
		//Camera::CameraFollowBoundry(camera, renderedPosition, renderedTransform.x, speed);
		//Camera::CameraBothBoundry(camera, renderedPosition, renderedTransform.x, speed);

		Draw::Square(renderer, renderedPosition, renderedTransform, color);

		return success;
	}

};