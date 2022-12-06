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

	block Square(const Renderer& renderer, const Vector::Vector2<float>& position, void* nArea, const Color::Color& color) {
		const auto& area = *(Vector::Vector2<float>*)(nArea);
		const Rectangle fillRect { ceil(position.x - (area.x / 2)), ceil(position.y - (area.y / 2)), area.x, area.y };
		SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
		SDL_RenderFillRect(renderer, &fillRect);
	};

	block Circle(const Renderer& renderer, const Vector::Vector2<float>& position, void* nRadius, const Color::Color& color) {
		const auto& radius = *(float*)(nRadius);
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