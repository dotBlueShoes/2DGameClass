#pragma once
#include "Framework.hpp"
#include "Time.hpp"
#include "Color.hpp"

#include "Camera.hpp"

#include "Draw.hpp"
#include "Map.hpp"

#include "Player.hpp"
#include "Player1.hpp"
#include "Player2.hpp"
#include "Player3.hpp"

#include "Key.hpp"

namespace Game {

	SDL_Renderer* mainRenderer;
	SDL_Window* mainWindow;

	Color backgroundColor;

	Camera::Camera camera { { 0, 0 }, { 920 , 360 }, /*{ 920 / 2, 360 / 2},*/ 1};

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
		const SDL_Rect actor1 = Player::RenderUpdate(renderer, camera);
		//Key::RenderUpdate(renderer);
		//Player1::RenderUpdate(renderer, camera);
		//Player2::RenderUpdate(renderer, camera);
		const SDL_Rect actor2 = Player3::RenderUpdate(renderer, camera);

		Camera::Camera2ActorsBoundry(camera, actor1, Player::canMoveUp, Player::canMoveDown, actor2, Player3::canMoveUp, Player3::canMoveDown);

		// Render Debug ScreenCenter
		const Vector2<float> position { Camera::screenSize.x / 2, Camera::screenSize.y / 2 };
		const Color color { 255, 255, 255, 100 };
		const float radius(5);
		Draw::Circle(renderer, position, radius, color);
		
		//SDL_RenderSetScale(renderer, 1.5f, 1.5f);
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

			Camera::LogicUpdate(deltaTime, camera, keyboard);

			const Vector2<float> cameraMoveToCenter = Camera::GetCameraScaleMovePosition(camera);
			const Vector2 mousePositionToWorld { ((mousePosition.x - cameraMoveToCenter.x) / camera.zoom) - camera.position.x, ((mousePosition.y - cameraMoveToCenter.y) / camera.zoom) - camera.position.y };

			Player::LogicUpdate(deltaTime, mousePositionToWorld, mouseBitMask, keyboard);
			//Player1::LogicUpdate(deltaTime, mousePositionToWorld, mouseBitMask, keyboard);
			//Player2::LogicUpdate(deltaTime, mousePositionToWorld, mouseBitMask, keyboard);
			Player3::LogicUpdate(deltaTime, mousePositionToWorld, mouseBitMask, keyboard);
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