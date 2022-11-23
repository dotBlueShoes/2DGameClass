#pragma once
#include "Framework.hpp"
#include "Window.hpp"
#include "Time.hpp"

#include "Object.hpp"
#include "Draw.hpp"

namespace Game {

	namespace Callback {

		enum class Events : int64 {
			Nothing = 1,
			Quit = 0
		};

		Events HandleEvents() {
			SDL_Event event;
			SDL_PollEvent(&event);
			switch (event.type) {
			case SDL_QUIT: return Events::Quit;
				default: return Events::Nothing;
			}
		}

	}

	block Create(
		const Window::WindowStruct& window,
		const int32& initilizeOnFirstSupportingDriver,
		const uint32& rendererFlags,
		/*out*/ MainWindow& mainWindow,
		/*out*/ Renderer& renderer
	) {
		

		// Initializes SDL Library with following components.
		//if (
		SDL_Init(SDL_INIT_EVERYTHING);// != 1) {
		//	SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		//	assert(true);
		//}

		if ((mainWindow = SDL_CreateWindow(window.title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, window.viewport.x, window.viewport.y, SDL_WINDOW_SHOWN)) == NULL) {
			SDL_Log("Unable to create SDL window");
			assert(true);
		}

		if ((renderer = SDL_CreateRenderer(mainWindow, initilizeOnFirstSupportingDriver, rendererFlags)) == NULL) {
			SDL_Log("Unable to create SDL renderer");
			assert(true);
		}
		
		// To enable alpha channel in drawings.
		SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

	}

	void LogicUpdate(const float& deltaTime, const size& objectsCount, Object::Object* objects) {

		const SDL_Rect boundry { 0, 0, 920, 360 };

		for (size i = 0; i < objectsCount; i++) {
			auto& object = objects[i];
			const Vector::Vector2 temp = object.calculateMove(object.transform, object.moveable, deltaTime);
			const float radius = 30;

			if (temp.x < boundry.x + radius || temp.x > boundry.w - radius) // If we're outside X boundry.
				object.moveable.direction.x *= -1;

			if (temp.y < boundry.y + radius || temp.y > boundry.h - radius)	// If we're outside Y boundry.
				object.moveable.direction.y *= -1;

			if (temp.x > boundry.x + radius && temp.y > boundry.y + radius &&		// If we're in boundry.
				temp.x < boundry.w - radius && temp.y < boundry.h - radius) {
				object.transform.position.x = temp.x;
				object.transform.position.y = temp.y;
			} else {
				//SDL_Log("temp: %f", object.moveable.direction.x);
				//SDL_Log("temp: %f", object.moveable.direction.y);
			}
			
		}

	}

	void RenderUpdate(const Renderer& renderer, const Color::Color& backgroundColor, const size& objectsCount, Object::Object* objects) {
		Draw::Background(renderer, backgroundColor);

		const float radius(30);

		for (size i = 0; i < objectsCount; i++) {
			const auto& object = objects[i];
			object.draw(renderer, object.transform.position, radius, object.color);
		}

		SDL_RenderPresent(renderer);
	}

	block MainLoop(const Renderer& renderer, const Color::Color& backgroundColor, const size& objectsCount, Object::Object* objects) {
		Time::Start();

		// FixedLogicUpdate(); ?
		// - if(deltaTime)
		// - some OS integration.... winapi ? yes
		// https://stackoverflow.com/questions/15683221/how-to-call-a-function-every-x-seconds

		while (Callback::HandleEvents() != Callback::Events::Quit) {
			//SDL_Log("Milliseconds: %f", Time::GetElapsedTime());
			 
			LogicUpdate(Time::GetElapsedTime(), objectsCount, objects);
			RenderUpdate(renderer, backgroundColor, objectsCount, objects);
		}
	}

	block Destroy(const MainWindow& mainWindow, const Renderer& mainRenderer) {
		SDL_DestroyWindow(mainWindow);
		SDL_DestroyRenderer(mainRenderer);
		SDL_Quit();
	}

}