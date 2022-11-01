#pragma once
#include "Framework.hpp"
#include "Time.hpp"
#include "Color.hpp"

#include "Camera.hpp"
#include "Player.hpp"
#include "Key.hpp"
#include "Draw.hpp"
#include "Map.hpp"

#include "Player1.hpp"
#include "Player2.hpp"

namespace Game {

	SDL_Renderer* mainRenderer;
	SDL_Window* mainWindow;

	Color backgroundColor;

	Camera::Camera camera { { 0, 0 }, { 920 , 360 } };

	// Input
	Vector2<Sint32> mousePosition;
	const Uint8* keyboard;
	Uint32 mouseBitMask;

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

	ErrorCode RenderUpdate(SDL_Renderer* const renderer, Camera::Camera& camera) {

		Draw::Background(renderer, backgroundColor);

		// This will be an array of functions to call through later.
		Map::RenderUpdate(renderer, camera);
		//Player::RenderUpdate(renderer);
		//Key::RenderUpdate(renderer);
		Player1::RenderUpdate(renderer, camera);
		Player2::RenderUpdate(renderer, camera);
		

		// Update the screen with any rendering performed since the previous call.
		SDL_RenderPresent(renderer);
		return success;
	}

	// Game logic
	ErrorCode LogicUpdate(const float& deltaTime) {

		// Input
		SDL_PumpEvents();
		{
			mouseBitMask = SDL_GetMouseState(&mousePosition.x, &mousePosition.y);
			keyboard = SDL_GetKeyboardState(nullptr);

			//if (keyboard[SDL_SCANCODE_RETURN]) {
			//	printf("<RETURN> is pressed.\n");
			//}

			//Player::LogicUpdate(frame);
			//Camera::LogicUpdate(deltaTime, camera, keyboard);
			Player1::LogicUpdate(deltaTime, mousePosition, mouseBitMask, keyboard);
			Player2::LogicUpdate(deltaTime, mousePosition, mouseBitMask, keyboard);
		}
		

		return success;
	}

	ErrorCode MainLoop() {

		Clock::Start();

		// FixedLogicUpdate(); ?
		// - if(deltaTime)
		// - some OS integration.... winapi ? yes
		// https://stackoverflow.com/questions/15683221/how-to-call-a-function-every-x-seconds

		while (HandleEvents() != failure) {
			//SDL_Log("Milliseconds: %f", Clock::GetElapsedTime());
			LogicUpdate(Clock::GetElapsedTime());
			RenderUpdate(mainRenderer, camera);
		}

		return success;
	}

	ErrorCode Create(const Vector2<int>& windowSize, const char* gameTitle, const size& gameTitleSize) {

		// Initializes SDL Library with following components.
		if (SDL_Init(SDL_INIT_EVERYTHING) != success) {
			SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
			return failure;
		}

		{
			const int64_t initilizeOnFirstSupportingDriver(-1);
			const Uint32 rendererFlags(SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

			if ((mainWindow = SDL_CreateWindow(gameTitle, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowSize.x, windowSize.y, SDL_WINDOW_SHOWN)) == NULL) {
				SDL_Log("Unable to create SDL window");
				return failure;
			}

			if ((mainRenderer = SDL_CreateRenderer(mainWindow, initilizeOnFirstSupportingDriver, rendererFlags)) == NULL) {
				SDL_Log("Unable to create SDL renderer");
				return failure;
			}

			// To enable alpha channel in drawings.
			SDL_SetRenderDrawBlendMode(mainRenderer, SDL_BLENDMODE_BLEND);

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