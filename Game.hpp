#pragma once
#include "Framework.hpp"
#include "Color.hpp"

#include "Player.hpp"
#include "Key.hpp"

namespace Game {

	SDL_Renderer* mainRenderer;
	SDL_Window* mainWindow;

	ErrorCode HandleEvents() {
		SDL_Event event;

		SDL_PollEvent(&event);
		switch (event.type) {
			case SDL_QUIT:
				return failure;
			default:
				break;
		}

		return success;
	}

	ErrorCode RenderUpdate(SDL_Renderer* const renderer) {

		// Clear the current rendering target with the drawing color.
		SDL_RenderClear(renderer);

		// This will be an array of functions to call through later.
		Player::RenderUpdate(renderer);
		Key::RenderUpdate(renderer);

		// Update the screen with any rendering performed since the previous call.
		SDL_RenderPresent(renderer);

		return success;
	}

	// Game logic
	ErrorCode LogicUpdate(float& frame) {
		frame++;

		Player::LogicUpdate(frame);

		return success;
	}

	ErrorCode MainLoop() {
		float frame(0);
		while (HandleEvents() != failure) {
			LogicUpdate(frame);
			RenderUpdate(mainRenderer);
		}

		return success;
	}

	ErrorCode Initialize(const char* gameTitle, const size& gameTitleSize, const Color& backgroundColor) {

		// Initializes SDL Library with following components.
		if (SDL_Init(SDL_INIT_EVERYTHING) != success) {
			SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
			return failure;
		}

		{
			const int64_t initilizeOnFirstSupportingDriver(-1);
			const uint64_t windowSizeX(920), windowSizeY(360);
			const Uint32 rendererFlags(SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

			if ((mainWindow = SDL_CreateWindow(gameTitle, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowSizeX, windowSizeY, SDL_WINDOW_SHOWN)) == NULL) {
				SDL_Log("Unable to create SDL window");
				return failure;
			}

			if ((mainRenderer = SDL_CreateRenderer(mainWindow, initilizeOnFirstSupportingDriver, rendererFlags)) == NULL) {
				SDL_Log("Unable to create SDL renderer");
				return failure;
			}

			// Set the color used for drawing operations.
			SDL_SetRenderDrawColor(mainRenderer, backgroundColor.red, backgroundColor.green, backgroundColor.blue, backgroundColor.alpha);

			return success;
		}

	}

	ErrorCode Destroy() {
		SDL_DestroyWindow(mainWindow);
		SDL_DestroyRenderer(mainRenderer);
		SDL_Quit();
		return success;
	}

};