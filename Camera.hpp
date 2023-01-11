#pragma once
#include "Framework.hpp"
#include "Math/Vector.hpp"

namespace Camera {

	struct Camera {
		Vector::Vector2<float> position;
		Vector::Vector2<uint32> viewport;
	};

	block MoveXByStep(Camera& camera, const int& x) {
		camera.position.x += x;
	}

	block MoveYByStep(Camera& camera, const int& y) {
		camera.position.y += y;
	}

	block MoveByStep(
		const float& deltaTime,
		Camera& camera,
		const Vector::Vector2<float>& mousePosition,
		const Uint32& mouseBitMask,
		const Uint8* const keyboard,
		const int& step = 1.0f
	) {
		if (keyboard[SDL_SCANCODE_U]) camera.position.y -= step;
		if (keyboard[SDL_SCANCODE_K]) camera.position.x += step;
		if (keyboard[SDL_SCANCODE_J]) camera.position.y += step;
		if (keyboard[SDL_SCANCODE_H]) camera.position.x -= step;
	}

	block MoveByStepIfContains(
		const float& deltaTime,
		Camera& camera,
		const Vector::Vector2<float>& mousePosition,
		const Uint32& mouseBitMask,
		const Uint8* const keyboard
		//const size& objectsCount,
		//const Object::Object* objects
	) {
		//const float stepAmount = 1.0f;
		//if (keyboard[SDL_SCANCODE_U]) camera.position.y -= stepAmount;
		//if (keyboard[SDL_SCANCODE_J]) camera.position.x += stepAmount;
		//if (keyboard[SDL_SCANCODE_H]) camera.position.y += stepAmount;
		//if (keyboard[SDL_SCANCODE_K]) camera.position.x -= stepAmount;
	}

}