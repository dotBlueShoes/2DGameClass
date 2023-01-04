#pragma once
#include "Framework.hpp"
#include "Window.hpp"
#include "Time.hpp"

#include "SceneGraph.hpp"
#include "CollisionLogic.hpp"
#include "Draw.hpp"
#include "Log.hpp"

namespace Game {

	//void CollideCircle(
	//	const float& deltaTime,
	//	const size& objectsCount,
	//	/* out */ Object::Object* objects,
	//	const size& current,
	//	/* out */ vector<Vector::Vector2<float>>& calculatedPositions
	//) {
	//	auto& object = objects[current];
	//	auto& calculatedPosition = calculatedPositions[current];
	//	const auto& type = (Surface::Circle*)(object.surface.type);
	//	const auto& radius = type->radius;
	//
	//
	//	// COLLISION [ IN BOUNDRY CHECKS ]
	//	const Rectangle boundry{ 0, 0, 920, 360 }; // It will be outside later
	//	if (calculatedPosition.x < boundry.x + radius || calculatedPosition.x > boundry.w - radius)		// If we're outside X boundry.
	//		object.moveData.velocity.x *= -1;
	//
	//	if (calculatedPosition.y < boundry.y + radius || calculatedPosition.y > boundry.h - radius)		// If we're outside Y boundry.
	//		object.moveData.velocity.y *= -1;
	//
	//	if (calculatedPosition.x > boundry.x + radius && calculatedPosition.y > boundry.y + radius &&	// If we're in boundry.
	//		calculatedPosition.x < boundry.w - radius && calculatedPosition.y < boundry.h - radius
	//		) {
	//
	//		// COLLISION [ WITH OTHER CHECKS ]
	//		for (size i = 0; i < objectsCount; i++) {
	//			auto& other = objects[i];
	//			const auto& otherType = (Surface::Circle*)(other.surface.type);
	//
	//			if (object.identifier != other.identifier) {
	//
	//				if (Object::IsType(object.identifier, other.identifier, Object::Type::Circle)) {
	//					const auto& otherRadius = otherType->radius;
	//					auto& otherCalculatedPosition = calculatedPositions[i];
	//
	//					const Vector::Vector2<float>& center1 = calculatedPosition;
	//					const Vector::Vector2<float>& center2 = otherCalculatedPosition;
	//					const float lengthBetween = (float)Vector::LengthBetween(center1, center2);
	//
	//					Vector::Vector2<float> separation{ // simple normalization
	//						(center1.x - center2.x) / (float)lengthBetween,
	//						(center1.y - center2.y) / (float)lengthBetween
	//					};
	//
	//					// Collision Detected !
	//					if (lengthBetween < radius + otherRadius) {
	//
	//						if (Collision::isSeperationOn) {
	//							calculatedPosition = Vector::Addition(
	//								object.transform.position, {
	//									separation.x * (float)(otherRadius - lengthBetween * 0.5f),
	//									separation.y * (float)(otherRadius - lengthBetween * 0.5f)
	//								}
	//							);
	//
	//							otherCalculatedPosition = Vector::Subtract(
	//								other.transform.position, {
	//									separation.x * (float)(radius - lengthBetween * 0.5f),
	//									separation.y * (float)(radius - lengthBetween * 0.5f)
	//								}
	//							);
	//						}
	//
	//						if (Collision::isReflectionOn) {
	//							const auto offset1 = Vector::MultiplyByScalar(separation, (float)Vector::DotProduct(object.moveData.velocity, separation) * 2.0f);
	//							object.moveData.velocity = Vector::Subtract(object.moveData.velocity, offset1);
	//							separation = Vector::Vector2<float>{ separation.x * -1.0f, separation.y * -1.0f };
	//							const auto offset2 = Vector::MultiplyByScalar(separation, (float)Vector::DotProduct(other.moveData.velocity, separation) * 2.0f);
	//							other.moveData.velocity = Vector::Subtract(other.moveData.velocity, offset2);
	//						}
	//					}
	//				} 
	//			}
	//		}
	//	} 
	//	object.transform.position.x = Math::Clamp(object.transform.position.x, boundry.x + radius, boundry.w - radius);
	//	object.transform.position.y = Math::Clamp(object.transform.position.y, boundry.y + radius, boundry.h - radius);
	//
	//}
	//
	//void CollideSquare(
	//	const float& deltaTime,
	//	const size& objectsCount,
	//	/* out */ Object::Object* objects,
	//	const size& current,
	//	/* out */ vector<Vector::Vector2<float>>& calculatedPositions
	//) {
	//	auto& object = objects[current];
	//	auto& calculatedPosition = calculatedPositions[current];
	//	const auto& type = (Surface::Square*)(object.surface.type);
	//	const auto& area = type->size;
	//
	//	// COLLISION [ IN BOUNDRY CHECKS ]
	//	const Rectangle boundry{ 0, 0, 920, 360 }; // It will be outside later
	//	if (calculatedPosition.x < boundry.x + area.x / 2 || calculatedPosition.x > boundry.w - area.x / 2)		// If we're outside X boundry.
	//		object.moveData.velocity.x *= -1;
	//
	//	if (calculatedPosition.y < boundry.y + area.y / 2 || calculatedPosition.y > boundry.h - area.y / 2)		// If we're outside Y boundry.
	//		object.moveData.velocity.y *= -1;
	//
	//	if (calculatedPosition.x > boundry.x + area.x / 2 && calculatedPosition.y > boundry.y + area.y / 2 &&	// If we're in boundry.
	//		calculatedPosition.x < boundry.w - area.x / 2 && calculatedPosition.y < boundry.h - area.y / 2
	//		) {
	//		// COLLISION [ WITH OTHER CHECKS ]
	//		for (size i = 0; i < objectsCount; i++) {
	//			auto& other = objects[i];
	//			const auto& otherType = (Surface::Circle*)(other.surface.type);
	//
	//			if (object.identifier != other.identifier) {
	//				if (Object::IsType(object.identifier, other.identifier, Object::Type::Square)) {
	//					auto& otherCalculatedPosition = calculatedPositions[i];
	//					const auto& otherArea = type->size; // object.collision.boundry instead should be used...
	//
	//					const Vector::Vector2<float>& center1 = calculatedPosition;
	//					const Vector::Vector2<float>& center2 = otherCalculatedPosition;
	//					const double lengthBetween = Vector::LengthBetween(center1, center2);
	//					const float left = (object.collision.boundry.w + center1.x) - (other.collision.boundry.x + center2.x);
	//					const float right = (other.collision.boundry.w + center2.x) - (object.collision.boundry.x + center1.x);
	//					const float top = (object.collision.boundry.h + center1.y) - (other.collision.boundry.y + center2.y);
	//					const float bottom = (other.collision.boundry.h + center2.y) - (object.collision.boundry.y + center1.y);
	//
	//					// Wektro separacji w tej formie to opdowiednio wartoœci: left, right, top, bottom.
	//					Vector::Vector2<float> separation;
	//					left < right ? separation.x = -left : separation.x = right;
	//					top < bottom ? separation.y = -top : separation.y = bottom;
	//					abs(separation.x) < abs(separation.y) ? separation.y = 0 : separation.x = 0;
	//
	//					// Collision Detected
	//					if (left > 0 && right > 0 && top > 0 && bottom > 0) {
	//						//SDL_Log("1: %f, %f, %f, %f", left, right, top, bottom);
	//						//SDL_Log("2: %f, %f", separation.x, separation.y);
	//
	//						// Zmianiamy pozycje obiektu.
	//						if (Collision::isSeperationOn) {
	//							calculatedPosition = Vector::Addition(
	//								object.transform.position, {
	//									separation.x,
	//									separation.y
	//								}
	//							);
	//
	//							otherCalculatedPosition = Vector::Subtract(
	//								other.transform.position, {
	//									separation.x,
	//									separation.y
	//								}
	//							);
	//
	//						}
	//
	//						// Mówimy obiektowi ¿eby porusza³ siê teraz w innym torze.
	//						if (Collision::isReflectionOn) {
	//							if (separation.x == 0) {
	//								object.moveData.velocity.x *= 1;
	//								other.moveData.velocity.x *= 1;
	//								object.moveData.velocity.y *= -1;
	//								other.moveData.velocity.y *= -1;
	//							} else {
	//								object.moveData.velocity.x *= -1;
	//								other.moveData.velocity.x *= -1;
	//								object.moveData.velocity.y *= 1;
	//								other.moveData.velocity.y *= 1;
	//							}
	//						}
	//					}
	//				} else if (Object::IsType(object.identifier, Object::Type::Square) &&
	//					Object::IsType(other.identifier, Object::Type::Circle)
	//				) {
	//					const auto& otherType = (Surface::Circle*)(object.surface.type);
	//					const auto& otherRadius = otherType->radius; // object.collision.boundry instead should be used...
	//					auto& otherCalculatedPosition = calculatedPositions[i];
	//					SDL_Log("HERE");
	//
	//					const Vector::Vector2<float>& objectCenter = calculatedPosition;
	//					const Vector::Vector2<float>& otherCenter = otherCalculatedPosition;
	//					//const double lengthBetween = Vector::LengthBetween(center1, center2);
	//					const float left = (object.collision.boundry.w + objectCenter.x) - (other.collision.boundry.x + otherCenter.x);
	//					const float right = (other.collision.boundry.w + otherCenter.x) - (object.collision.boundry.x + objectCenter.x);
	//					const float top = (object.collision.boundry.h + objectCenter.y) - (other.collision.boundry.y + otherCenter.y);
	//					const float bottom = (other.collision.boundry.h + otherCenter.y) - (object.collision.boundry.y + objectCenter.y);
	//
	//					// Punkt na prostokacie najblizszy srodkowi okregu.
	//					Vector::Vector2<float> point;
	//					point.x = Math::Clamp(object.transform.position.x, left, right);
	//					point.x = Math::Clamp(object.transform.position.x, top, bottom);
	//
	//					// d³ugoœæ ró¿nicy
	//					const Vector::Vector2<float> differnce = Vector::Subtract(otherCenter, point);
	//					
	//
	//				} else {
	//					SDL_Log("UNKNOWN TYPE !");
	//				}
	//			}
	//		}
	//	}
	//
	//	object.transform.position.x = Math::Clamp(object.transform.position.x, boundry.x + area.x, boundry.w - area.x);
	//	object.transform.position.y = Math::Clamp(object.transform.position.y, boundry.y + area.x, boundry.h - area.x);
	//}

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

		void Logic (
			/* chg */ SceneGraph::SceneGraph& sceneGraph,
			const float& deltaTime
		) {
			vector<Vector::Vector2<float>> calculatedCirclePositions;
			vector<Vector::Vector2<float>> calculatedSquarePositions;

			/* Calculate their new position.Circle */
			for (size i = 0; i < sceneGraph.circleObjectsCount; i++) {
				auto& object = sceneGraph.circleObjects[i];
				const Vector::Vector2 newPosition = object.calculateMove(object.transform, object.rigidbody, deltaTime);
				calculatedCirclePositions.push_back(newPosition);
			}

			/* Square */
			for (size i = 0; i < sceneGraph.squareObjectsCount; i++) {
				auto& object = sceneGraph.squareObjects[i];
				const Vector::Vector2 newPosition = object.calculateMove(object.transform, object.rigidbody, deltaTime);
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

		}

		void Render (
			/* chg */ SceneGraph::SceneGraph& sceneGraph,
			const Renderer& renderer
		) {
			Draw::Background(renderer, *sceneGraph.backgroundColor);

			for (size i = 0; i < sceneGraph.circleObjectsCount; i++) {
				const auto& object = sceneGraph.circleObjects[i];
				const auto& type = (Surface::Circle*)(object.surface.type);
				auto& radius = type->radius;
				object.draw(renderer, object.transform.position, &radius, object.color);
			}

			for (size i = 0; i < sceneGraph.squareObjectsCount; i++) {
				const auto& object = sceneGraph.squareObjects[i];
				const auto& type = (Surface::Square*)(object.surface.type);
				auto& extent = type->extent;
				object.draw(renderer, object.transform.position, &extent, object.color);
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