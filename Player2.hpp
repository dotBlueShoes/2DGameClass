#pragma once
#include "Framework.hpp"
#include "Math.hpp"

namespace Player2 {

	const Color color { 255, 255, 0, 50 };
	const float radius(50);

	Vector2<float> position { 100, 100 };

	Vector2<float> moveDirection { 0, 0 };
	const float errorEdge(0.5);

	// const float duration(5);
	// float elapsedTime(0);

	ErrorCode Create() {
		moveDirection = position; // So we don't start moving to { 0, 0 } at start.
		return success;
	}

	ErrorCode LogicUpdate(const float& deltaTime, const Vector2<Sint32>& mousePosition, const Uint32& mouseBitMask, const Uint8* const keyboard) {

		if ((mouseBitMask & SDL_BUTTON_LMASK) != 0) {
			moveDirection.x = mousePosition.x;
			moveDirection.y = mousePosition.y;
		}

		// FRAME DEPENDANT
		// Meaning we're moving. Unit we're close enough it counts as done.
		if (Math::Absolute(position.x - moveDirection.x) > errorEdge ||
			Math::Absolute(position.y - moveDirection.y) > errorEdge) {
			position = Math::Lerp(position, moveDirection, 0.1);
			//SDL_Log("here %d, %d", ++counter, Math::Absolute<float>(position.x - moveDirection.x));
		}

		// // FRAME INDEPENDANT / TIME DEPENDANT
		// https://www.febucci.com/2018/08/easing-functions/
		// elapsedTime += deltaTime;
		// if (elapsedTime <= duration) {
		// 	position = Math::Lerp(position, moveDirection, elapsedTime / duration);
		// 	//position = Math::Lerp(position, moveDirection, Lerp::EaseIn(elapsedTime / duration));
		// 	// few things
		// 	// 1. implement deltaTime
		// 	// 2. elapsedTime = 0 somewhere
		// 	// 3. if it equals 0 then this code segment needs to not trigger unless we're in fact moving
		// }

		//SDL_Log("Mouse cursor is at %d, %d", mousePosition.x, mousePosition.y);
		//if ((mouseBitMask & SDL_BUTTON_RMASK) != 0) SDL_Log("Mouse Button 3 (middle) is pressed.");
		//if ((mouseBitMask & SDL_BUTTON_MMASK) != 0) SDL_Log("Mouse Button 2 (right) is pressed.");
		//if ((mouseBitMask & SDL_BUTTON_LMASK) != 0) SDL_Log("Mouse Button 1 (left) is pressed.");
		//if ((mouseBitMask & SDL_MOUSEBUTTONDOWN) != 0)
		//if ((mouseBitMask & SDL_MOUSEBUTTONUP) != 0)

		return success;
	}


	ErrorCode FixedLogicUpdate() {
		return success;
	}

	ErrorCode RenderUpdate(SDL_Renderer* const renderer) {
		Draw::Circle(renderer, position, radius, color);
		return success;
	}

};