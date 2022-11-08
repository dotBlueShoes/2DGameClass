#pragma once
#include "Framework.hpp"
#include "Math.hpp"

namespace Player2 {

	const Color color { 255, 255, 0, 50 };
	const float radius(50);

	Vector2<float> position { 100, 100 };

	// Frame dependent.
	Vector2<float> moveDirection { 0, 0 };
	const float errorEdge(0.5);

	// Frame independent.
	Vector2<float> lastPosition { 0, 0 };
	bool isMoving(false);
	const float duration(1);
	float elapsedTime(0);

	ErrorCode Create() {
		moveDirection = position; // So we don't start moving to { 0, 0 } at start.
		lastPosition = position;
		return success;
	}

	ErrorCode LogicUpdate(const float& deltaTime, const Vector2<float>& mousePosition, const Uint32& mouseBitMask, const Uint8* const keyboard) {

		// // FRAME DEPENDANT SIMPLE
		// if ((mouseBitMask & SDL_BUTTON_LMASK) != 0) {
		// 	moveDirection.x = mousePosition.x;
		// 	moveDirection.y = mousePosition.y;
		// }
		// if ( // Meaning we're moving. Unit we're close enough it counts as done.
		// 	Math::Absolute(position.x - moveDirection.x) > errorEdge ||
		// 	Math::Absolute(position.y - moveDirection.y) > errorEdge
		// ) {
		// 	position = Math::Lerp(position, moveDirection, 0.1);
		// }

		// FRAME DEPENDANT COMPLEX
		if ((mouseBitMask & SDL_BUTTON_LMASK) != 0) {
			moveDirection.x = mousePosition.x;
			moveDirection.y = mousePosition.y;
			lastPosition = position;
			elapsedTime = 0;
		}
		if ( // Meaning we're moving. Unit we're close enough it counts as done.
			Math::Absolute(position.x - moveDirection.x) > errorEdge ||
			Math::Absolute(position.y - moveDirection.y) > errorEdge
		) {
			SDL_Log("We're moving!.");
			position = Math::Lerp(lastPosition, moveDirection, Math::EasingFunctions::EaseOut(elapsedTime / duration));
			elapsedTime += 0.01f;
		} else {
			elapsedTime = 0;
		}

		

		// // FRAME INDEPENDANT / TIME DEPENDANT
		// if ( !isMoving && (mouseBitMask & SDL_BUTTON_LMASK) != 0) {
		// 	isMoving = true;
		// 	moveDirection.x = mousePosition.x;
		// 	moveDirection.y = mousePosition.y;
		// 	lastPosition = position;
		// }
		// if (isMoving) {
		// 	elapsedTime += deltaTime;
		// 	position = Math::Lerp(lastPosition, moveDirection, Math::EasingFunctions::EaseInOut(elapsedTime / duration));
		// 	if ( // It's hard to hit exaclly 'moveDirection' instead it's prefered to have a close enough.
		// 		Math::Absolute(position.x - moveDirection.x) <= errorEdge && 
		// 		Math::Absolute(position.y - moveDirection.y) <= errorEdge)
		// 	{ 
		// 		isMoving = false;
		// 		elapsedTime = 0;
		// 	}
		// }

		// // Mouse Events !
		// SDL_Log("Mouse cursor is at %d, %d", mousePosition.x, mousePosition.y);
		// if ((mouseBitMask & SDL_BUTTON_RMASK) != 0) SDL_Log("Mouse Button 3 (middle) is pressed.");
		// if ((mouseBitMask & SDL_BUTTON_MMASK) != 0) SDL_Log("Mouse Button 2 (right) is pressed.");
		// if ((mouseBitMask & SDL_BUTTON_LMASK) != 0) SDL_Log("Mouse Button 1 (left) is pressed.");
		// if ((mouseBitMask & SDL_MOUSEBUTTONDOWN) != 0)
		// if ((mouseBitMask & SDL_MOUSEBUTTONUP) != 0)

		return success;
	}


	ErrorCode FixedLogicUpdate() {
		return success;
	}

	ErrorCode RenderUpdate(SDL_Renderer* const renderer, const Camera::Camera& camera) {
		const Vector2<float> renderedPosition { (position.x + camera.position.x) * camera.zoom , (position.y + camera.position.y) * camera.zoom };
		const float renderedRadious(radius * camera.zoom);
		// (mousePosition.x / camera.zoom) - camera.position.x

		Draw::Circle(renderer, renderedPosition, renderedRadious, color);
		return success;
	}

};