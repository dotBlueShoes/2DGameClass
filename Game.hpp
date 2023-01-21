#pragma once
#include "Framework.hpp"
#include "Window.hpp"
#include "Time.hpp"

#include "SceneGraph.hpp"
#include "CollisionLogic.hpp"
#include "Draw.hpp"
#include "Log.hpp"

#include "GameObjects/Player1.hpp"
#include "GameObjects/Finish.hpp"

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
			SceneGraph::SceneGraph& scene,
			const float& deltaTime
		) {

			SDL_PumpEvents();
			mouseBitMask = SDL_GetMouseState(&mousePosition.x, &mousePosition.y);
			keyboard = SDL_GetKeyboardState(nullptr);

			GameObjects::Player1::Update::JumpInputProcess(deltaTime, scene.circleObjects[0], {0, 0}, mouseBitMask, keyboard);

			//const Vector2<float> cameraMoveToCenter = Camera::GetCameraScaleMovePosition(camera);
			//const Vector::Vector2<float> mousePositionToWorld{ ((mousePosition.x - cameraMoveToCenter.x) / camera.zoom) - camera.position.x, ((mousePosition.y - cameraMoveToCenter.y) / camera.zoom) - camera.position.y };

			//DEBUG {
			//	Log::Info("Logic");
			//	for (size i = 0; i < scene.circleObjectsCount; i++) {
			//		auto& object = scene.circleObjects[i];
			//		Log::Info("Object: %f", object.transform.position.y);
			//	}
			//}

			/* Calculate their new position. Circle */
			for (size i = 0; i < scene.circleObjectsCount; i++) {
				auto& object = scene.circleObjects[i];

				// Rigidbody logic
				Moveable::Accelerate(object.rigidbody, deltaTime);

				const Vector::Vector2<float> newPosition = object.logic(deltaTime, object, {0, 0}, mouseBitMask, keyboard);
				
				// OLD RIGIDBODY MOVEMENT need's to pe placed inside object.logic function.
				//const Vector::Vector2<float> newPosition = object.calculateMove(object.transform, object.rigidbody, deltaTime);
				calculatedCirclePositions.push_back(newPosition);

				//DEBUG Log::Info("NewPosition: %f", newPosition.y);
			}

			/* Square */
			for (size i = 0; i < scene.squareObjectsCount; i++) {
				auto& object = scene.squareObjects[i];

				// Rigidbody logic
				Moveable::Accelerate(object.rigidbody, deltaTime);

				const Vector::Vector2<float> newPosition = object.logic(deltaTime, object, { 0, 0 }, mouseBitMask, keyboard);

				// OLD RIGIDBODY MOVEMENT need's to pe placed inside object.logic function.
				//const Vector::Vector2<float> newPosition = object.calculateMove(object.transform, object.rigidbody, deltaTime);
				calculatedSquarePositions.push_back(newPosition);
			}

			Collision::Circle::CheckCollisionCircle(scene, calculatedCirclePositions, deltaTime);
			Collision::Square::CheckCollisionSquare(scene, calculatedSquarePositions, deltaTime);
			Collision::BetweenTypes::CheckCollisionCircleSquare(scene, calculatedCirclePositions, calculatedSquarePositions, deltaTime);
			Collision::BounceOutsideBoundry(scene, calculatedCirclePositions, calculatedSquarePositions, deltaTime);

			//DEBUG for (size i = 0; i < scene.circleObjectsCount; i++) {
			//	Log::Info("After: %f", calculatedCirclePositions[i].y);
			//}

			//Collision::Bounce(sceneGraph, calculatedCirclePositions, calculatedSquarePositions, deltaTime);
			Camera::MoveByStep(deltaTime, scene.mainCamera, { 0, 0 }, mouseBitMask, keyboard, 4);

			/* Update for new positions. Circle */
			for (size i = 0; i < scene.circleObjectsCount; i++) {
				auto& object = scene.circleObjects[i];

				//// Rigidbody logic
				//Moveable::Accelerate(object.rigidbody, deltaTime);

				object.transform.position.x = calculatedCirclePositions[i].x;
				object.transform.position.y = calculatedCirclePositions[i].y;
			}

			/* Update for new positions. Square */
			for (size i = 0; i < scene.squareObjectsCount; i++) {
				auto& object = scene.squareObjects[i];

				//// Rigidbody logic
				//Moveable::Accelerate(object.rigidbody, deltaTime);

				object.transform.position.x = calculatedSquarePositions[i].x;
				object.transform.position.y = calculatedSquarePositions[i].y;
			}

			/* Triggers can invoke special movement to all objects or other we want that close to the end ! */
			Collision::BounceInsideBoundry(scene, calculatedCirclePositions, calculatedSquarePositions, deltaTime);

			calculatedCirclePositions.clear();
			calculatedSquarePositions.clear();

		}

		void Render (
			SceneGraph::SceneGraph& scene,
			const Renderer& renderer
		) {
			Draw::Background(renderer, *scene.backgroundColor);

			GameObjects::MazeMap::Render(renderer, scene.mainCamera, scene.map);
			
			// Gizmos !!!!
			const Vector::Vector2<float> finishPosiiton { 96 , 96 };
			Finish::Render(renderer, scene.mainCamera, finishPosiiton);

			const Vector::Vector2<float> gizmoStart { 
				finishPosiiton.x,
				finishPosiiton.y
			};

			const Vector::Vector2<float> gizmoEnd1 {
				scene.circleObjects[0].transform.position.x,
				scene.circleObjects[0].transform.position.y
			};

			const Vector::Vector2<float> gizmoEnd2 {
				scene.squareObjects[0].transform.position.x,
				scene.squareObjects[0].transform.position.y
			};


			scene.gizmoLines.push_back( SceneGraph::Gizmo::Line { 
				gizmoStart, gizmoEnd1, { 255, 0, 255, 255 }
			});
			scene.gizmoLines.push_back( SceneGraph::Gizmo::Line { 
				gizmoStart, gizmoEnd2, { 255, 0, 255, 255 }
			});

			for (size i = 0; i < scene.circleObjectsCount; i++) {
				auto& object = scene.circleObjects[i];
				object.render(renderer, scene.mainCamera, object);
			}

			for (size i = 0; i < scene.squareObjectsCount; i++) {
				auto& object = scene.squareObjects[i];
				object.render(renderer, scene.mainCamera, object);
			}

			{ // GIZMOS ARE FRAME OBJECTS ONLY ! ATLEAST FOR NOW !
				for (size i = 0; i < scene.gizmoLines.size(); i++) {
					auto& gizmoLine = scene.gizmoLines[i];
					Draw::Line(renderer, scene.mainCamera, gizmoLine.originPosition, gizmoLine.destinPosition, gizmoLine.color);
				}

				scene.gizmoLines.clear();
				//sceneGraph.gizmoLinesCount = 0;
				//delete[] sceneGraph.gizmoLines;
			}
				
			SDL_RenderPresent(renderer);
		}
	}

	block MainLoop(
		const size& scenesCount,
		SceneGraph::SceneGraph* scenes,
		const Renderer& renderer
	) {
		DEBUG Log::Info("Entering Main Loop");

		Time::Start();

		SceneGraph::scenes = scenes;
		SceneGraph::currentScene = &scenes[0];
	
		while (Callback::HandleEvents() != Callback::Events::Quit) {
			//Log::Info("Milliseconds Since Last Frame: %f", Time::GetElapsedTime());
			//if (SceneGraph::isStopped) continue;
			Update::Logic(*SceneGraph::currentScene, Time::GetFrameTime());
			Update::Render(*SceneGraph::currentScene, renderer);
		}

		DEBUG Log::Info("Out of Main Loop");
	}

	block Destroy(const MainWindow& mainWindow, const Renderer& mainRenderer) {
		SDL_DestroyWindow(mainWindow);
		SDL_DestroyRenderer(mainRenderer);
		SDL_Quit();
	}

}