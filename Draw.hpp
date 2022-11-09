#pragma once
#include "Framework.hpp"
#include "Color.hpp"
#include "Math.hpp"

namespace Draw {

	// So that we can pass function pointers for functions in which we have defined colors.
	using SetRendererDrawColor = ErrorCode(*)();

	ErrorCode Background(SDL_Renderer* const renderer, const Color& color) {
		// Set the color used for drawing operations. We need to do it every time so that inner ones doesn't override.
		SDL_SetRenderDrawColor(renderer, color.red, color.green, color.blue, color.alpha);
		// Clear the current rendering target with the drawing color.
		SDL_RenderClear(renderer);
		return success;
	}

	ErrorCode Square(SDL_Renderer* const renderer, const Vector2<float>& position, const Vector2<float>& transform, const Color& color) {
		SDL_Rect fillRect { ceil(position.x - (transform.x / 2)), ceil(position.y - (transform.y / 2)), transform.x, transform.y };
		SDL_SetRenderDrawColor(renderer, color.red, color.green, color.blue, color.alpha);
		SDL_RenderFillRect(renderer, &fillRect);
		return success;
	};

	ErrorCode Circle(SDL_Renderer* const renderer, const Vector2<float>& position, const float& radius, const Color& color) {

		SDL_SetRenderDrawColor(renderer, color.red, color.green, color.blue, color.alpha);
		for (int w = 0; w < radius * 2; w++) {
			for (int h = 0; h < radius * 2; h++) {
				int dx = radius - w; // horizontal offset
				int dy = radius - h; // vertical offset
				if ((dx*dx + dy * dy) <= (radius * radius)) {
					SDL_RenderDrawPoint(renderer, position.x + dx, position.y + dy);
				}
			}
		}

		return success;
	};

};