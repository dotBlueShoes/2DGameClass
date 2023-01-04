#pragma once
#include "Framework.hpp"
#include "Window.hpp"
#include "Time.hpp"

#include "SceneGraph.hpp"
#include "CollisionLogic.hpp"
#include "Draw.hpp"
#include "Log.hpp"

namespace Game {

	namespace Callback {

		enum class Events : int64 {
			Nothing = 0,
			Quit = 1
		};

		Events HandleEvents() {
			SDL_Event event;
			SDL_PollEvent(&event);
			switch (event.type) {
				case SDL_KEYDOWN:
					switch (event.key.keysym.scancode) {
						case SDL_SCANCODE_1:
							DEBUG Collision::isSeperationOn ? Collision::isSeperationOn = false : Collision::isSeperationOn = true;
							return Events::Nothing;
						case SDL_SCANCODE_2:
							DEBUG Collision::isReflectionOn ? Collision::isReflectionOn = false : Collision::isReflectionOn = true;
							return Events::Nothing;
						case SDL_SCANCODE_ESCAPE:
							DEBUG Log::Info("Quit key pressed");
							return Events::Quit;
						default: return Events::Nothing;
					}
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
		DEBUG { /* Initializes SDL Library with following components. */
			if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
				Log::Error("Unable to initialize SDL: %s", SDL_GetError());
				assert(false);
			}
			if ((mainWindow = SDL_CreateWindow(window.title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, window.viewport.x, window.viewport.y, SDL_WINDOW_SHOWN)) == NULL) {
				Log::Error("Unable to create SDL window");
				assert(false);
			}
			if ((renderer = SDL_CreateRenderer(mainWindow, initilizeOnFirstSupportingDriver, rendererFlags)) == NULL) {
				Log::Error("Unable to create SDL renderer");
				assert(false);
			}
		} else {
			SDL_Init(SDL_INIT_EVERYTHING);
			mainWindow = SDL_CreateWindow(window.title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, window.viewport.x, window.viewport.y, SDL_WINDOW_SHOWN);
			renderer = SDL_CreateRenderer(mainWindow, initilizeOnFirstSupportingDriver, rendererFlags);
		}

		/* To enable alpha channel in drawings. */
		SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	}

	namespace Update {

		// NextFramePositions.
		vector<Vector::Vector2<float>> calculatedCirclePositions;
		vector<Vector::Vector2<float>> calculatedSquarePositions;

		// Input
		const Uint8* keyboard;
		Vector::Vector2<sint32> mousePosition;
		uint32 mouseBitMask;

		void Logic (
			/* chg */ SceneGraph::SceneGraph& sceneGraph,
			const float& deltaTime
		) {


			SDL_PumpEvents();
			mouseBitMask = SDL_GetMouseState(&mousePosition.x, &mousePosition.y);
			keyboard = SDL_GetKeyboardState(nullptr);
			//const Vector2<float> cameraMoveToCenter = Camera::GetCameraScaleMovePosition(camera);
			//const Vector::Vector2<float> mousePositionToWorld{ ((mousePosition.x - cameraMoveToCenter.x) / camera.zoom) - camera.position.x, ((mousePosition.y - cameraMoveToCenter.y) / camera.zoom) - camera.position.y };


			/* Calculate their new position. Circle */
			for (size i = 0; i < sceneGraph.circleObjectsCount; i++) {
				auto& object = sceneGraph.circleObjects[i];

				const Vector::Vector2<float> newPosition = object.logic(deltaTime, object, {0, 0}, mouseBitMask, keyboard);

				// OLD RIGIDBODY MOVEMENT need's to pe placed inside object.logic function.
				//const Vector::Vector2<float> newPosition = object.calculateMove(object.transform, object.rigidbody, deltaTime);
				calculatedCirclePositions.push_back(newPosition);
			}

			/* Square */
			for (size i = 0; i < sceneGraph.squareObjectsCount; i++) {
				auto& object = sceneGraph.squareObjects[i];

				const Vector::Vector2<float> newPosition = object.logic(deltaTime, object, { 0, 0 }, mouseBitMask, keyboard);

				// OLD RIGIDBODY MOVEMENT need's to pe placed inside object.logic function.
				//const Vector::Vector2<float> newPosition = object.calculateMove(object.transform, object.rigidbody, deltaTime);
				calculatedSquarePositions.push_back(newPosition);
			}

			Collision::Circle::CheckCollisionCircle(sceneGraph, calculatedCirclePositions, deltaTime);
			Collision::Square::CheckCollisionSquare(sceneGraph, calculatedSquarePositions, deltaTime);
			Collision::BetweenTypes::CheckCollisionCircleSquare(sceneGraph, calculatedCirclePositions, calculatedSquarePositions, deltaTime);
			Collision::BounceOutsideBoundry(sceneGraph, calculatedCirclePositions, calculatedSquarePositions, deltaTime);

			/* Update for new positions. Circle */
			for (size i = 0; i < sceneGraph.circleObjectsCount; i++) {
				auto& object = sceneGraph.circleObjects[i];
				object.transform.position.x = calculatedCirclePositions[i].x;
				object.transform.position.y = calculatedCirclePositions[i].y;
			}

			/* Update for new positions. Square */
			for (size i = 0; i < sceneGraph.squareObjectsCount; i++) {
				auto& object = sceneGraph.squareObjects[i];
				object.transform.position.x = calculatedSquarePositions[i].x;
				object.transform.position.y = calculatedSquarePositions[i].y;
			}

			calculatedCirclePositions.clear();
			calculatedSquarePositions.clear();

		}

		void Render (
			/* chg */ SceneGraph::SceneGraph& sceneGraph,
			const Renderer& renderer
		) {
			Draw::Background(renderer, *sceneGraph.backgroundColor);

			GameObjects::MazeMap::Render(renderer, sceneGraph.map);
			

			for (size i = 0; i < sceneGraph.circleObjectsCount; i++) {
				auto& object = sceneGraph.circleObjects[i];
				object.render(renderer, object);
			}

			for (size i = 0; i < sceneGraph.squareObjectsCount; i++) {
				auto& object = sceneGraph.squareObjects[i];
				object.render(renderer, object);
			}

			{ // GIZMOS ARE FRAME OBJECTS ONLY ! ATLEAST FOR NOW !
				for (size i = 0; i < sceneGraph.gizmoLines.size(); i++) {
					auto& gizmoLine = sceneGraph.gizmoLines[i];
					Draw::Line(renderer, gizmoLine.originPosition, gizmoLine.destinPosition, gizmoLine.color);
				}

				sceneGraph.gizmoLines.clear();
				//sceneGraph.gizmoLinesCount = 0;
				//delete[] sceneGraph.gizmoLines;
			}
				
			SDL_RenderPresent(renderer);
		}
	}

	block MainLoop(
		/* chg */ SceneGraph::SceneGraph& sceneGraph,
		const Renderer& renderer
	) {
		DEBUG Log::Info("Entering Main Loop");

		Time::Start();
	
		while (Callback::HandleEvents() != Callback::Events::Quit) {
			//Log::Info("Milliseconds Since Last Frame: %f", Time::GetElapsedTime());
			Update::Logic(sceneGraph, Time::GetFrameTime());
			Update::Render(sceneGraph, renderer);
		}

		DEBUG Log::Info("Out of Main Loop");
	}

	block Destroy(const MainWindow& mainWindow, const Renderer& mainRenderer) {
		SDL_DestroyWindow(mainWindow);
		SDL_DestroyRenderer(mainRenderer);
		SDL_Quit();
	}

}