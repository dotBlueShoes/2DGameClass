#pragma once
#include "Framework.hpp"
#include "Color.hpp"
//#include "Math.hpp"

namespace Draw {

	// So that we can pass function pointers for functions in which we have defined colors.
	//using SetRendererDrawColor = ErrorCode(*)();

	block Background(const Renderer& renderer, const Color::Color& color) {
		// Set the color used for drawing operations. We need to do it every time so that inner ones doesn't override.
		SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
		// Clear the current rendering target with the drawing color.
		SDL_RenderClear(renderer);
	}

	//ErrorCode Square(SDL_Renderer* const renderer, const Vector2<float>& position, const Vector2<float>& transform, const Color& color) {
	//	SDL_Rect fillRect { ceil(position.x - (transform.x / 2)), ceil(position.y - (transform.y / 2)), transform.x, transform.y };
	//	SDL_SetRenderDrawColor(renderer, color.red, color.green, color.blue, color.alpha);
	//	SDL_RenderFillRect(renderer, &fillRect);
	//	return success;
	//};
	//

	block Circle(const Renderer& renderer, const Vector::Vector2<float>& position, const float& radius, const Color::Color& color) {
	
		SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
		for (int w = 0; w < radius * 2; w++) {
			for (int h = 0; h < radius * 2; h++) {
				float dx = radius - w; // horizontal offset
				float dy = radius - h; // vertical offset
				if ((dx*dx + dy * dy) <= (radius * radius)) {
					SDL_RenderDrawPoint(renderer, (int)(position.x + dx), (int)(position.y + dy));
				}
			}
		}
	};

};