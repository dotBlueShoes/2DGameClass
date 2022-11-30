#pragma once
#include "Framework.hpp"
#include "Window.hpp"
#include "Time.hpp"

#include "Object.hpp"
#include "Draw.hpp"
#include "Math.hpp"

namespace Game {

	const bool isCollisionOn(true);
	const bool isSeperationOn(true);
	const bool isReflectionOn(true);

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

		const Rectangle boundry { 0, 0, 920, 360 };
		vector<Vector::Vector2<float>> calculatedPositions;
		//vector<Vector::Vector2<float>> finalPositions;

		// Calculate their new position.
		for (size i = 0; i < objectsCount; i++) {
			auto& object = objects[i];
			const Vector::Vector2 temp = object.calculateMove(object.transform, object.moveable, deltaTime);
			calculatedPositions.push_back(temp);
		}

		// We do that so we can operate on calculatedPositions without interupting with values
		//  calculated after collision check.
		//finalPositions = calculatedPositions;

		// Collision Detection
		for (size i = 0; i < objectsCount; i++) {
			auto& object = objects[i];
			const float radius = 30;

			if (calculatedPositions[i].x < boundry.x + radius || calculatedPositions[i].x > boundry.w - radius)		// If we're outside X boundry.
				object.moveable.velocity.x *= -1;

			if (calculatedPositions[i].y < boundry.y + radius || calculatedPositions[i].y > boundry.h - radius)		// If we're outside Y boundry.
				object.moveable.velocity.y *= -1;

			if (calculatedPositions[i].x > boundry.x + radius && calculatedPositions[i].y > boundry.y + radius &&	// If we're in boundry.
				calculatedPositions[i].x < boundry.w - radius && calculatedPositions[i].y < boundry.h - radius) {

				// COLLISION CHECK & LOGIC
				if constexpr (isCollisionOn) {

					// When collision is detected i do the same as with boundry.

					// without seperation they shouldnt collide 
					// without bouncing they should slide

					// 1. TRY Enumerate through all other objects.
					for (size j = 0; j < objectsCount; j++) {
						auto& other = objects[j];
						if (object.collision.id != other.collision.id) {

							{ // Circle Collision
								const Vector::Vector2<float> center1 = calculatedPositions[i];
								const Vector::Vector2<float> center2 = calculatedPositions[j];
								//const Vector::Vector2<float> collisionPoint { center1 - center2 };
								const double lengthBetween = Vector::LengthBetween(center1, center2);
								const double radius1 = radius;
								const double radius2 = radius;
								Vector::Vector2<float> separation { // simple normalization
									(center1.x - center2.x) / (float)lengthBetween, // *(radius1 + radius2 - lengthBetween),
									(center1.y - center2.y) / (float)lengthBetween  // *(radius1 + radius2 - lengthBetween)
								};
								
								if (lengthBetween < radius1 + radius2) {
									//SDL_Log("Separation: %f, %f", separation.x, separation.y);
									//SDL_Log("Velocity1: %f, %f", object.moveable.velocity.x, object.moveable.velocity.y);
									//SDL_Log("Velocity2: %f, %f", other.moveable.velocity.x, other.moveable.velocity.y);

									// Separate balls
									if (isSeperationOn) {
										//finalPositions[i] = Vector::Addition(calculatedPositions[i], { separation.x * (float)(radius2 - lengthBetween * 0.5f), separation.y * (float)(radius2 - lengthBetween * 0.5f) });
										//finalPositions[j] = Vector::Subtract(calculatedPositions[j], { separation.x * (float)(radius1 - lengthBetween * 0.5f), separation.y * (float)(radius1 - lengthBetween * 0.5f) });
										object.transform.position = Vector::Addition(object.transform.position, { separation.x * (float)(radius2 - lengthBetween * 0.5f), separation.y * (float)(radius2 - lengthBetween * 0.5f) });
										other.transform.position = Vector::Subtract(other.transform.position, { separation.x * (float)(radius1 - lengthBetween * 0.5f), separation.y * (float)(radius1 - lengthBetween * 0.5f) });
									}

									// Reflect balls
									if (isReflectionOn) {

										//velocity = velocity - collisionPoint * Vector2::DotProduct(velocity, collisionPoint) * 2.0;
										//collisionPoint *= -1.0f;
										//b.velocity = b.velocity - collisionPoint * Vector2::DotProduct(b.velocity, collisionPoint) * 2.0;

										const auto offset1 = Vector::MultiplyByScalar(separation, (float)Vector::DotProduct(object.moveable.velocity, separation) * 2.0f);
										object.moveable.velocity = Vector::Subtract(object.moveable.velocity, offset1);

										separation = Vector::Vector2<float>{ separation.x * -1.0f, separation.y * -1.0f };

										const auto offset2 = Vector::MultiplyByScalar(separation, (float)Vector::DotProduct(other.moveable.velocity, separation) * 2.0f);
										other.moveable.velocity = Vector::Subtract(other.moveable.velocity, offset2);
									}

									//object.moveable.velocity.x *= -1;
									//object.moveable.velocity.y *= -1;
									calculatedPositions[i] = object.calculateMove(object.transform, object.moveable, deltaTime);
								}
							}

							//{ // Rectangular Collision
							//	const float left = (object.collision.boundry.w + positions[i].x) - (other.collision.boundry.x + positions[j].x);
							//	const float right = (other.collision.boundry.w + positions[j].x) - (object.collision.boundry.x + positions[i].x);
							//	const float top = (object.collision.boundry.h + positions[i].y) - (other.collision.boundry.y + positions[j].y);
							//	const float bottom = (other.collision.boundry.h + positions[j].y) - (object.collision.boundry.y + positions[i].y);
							//	// Wektro separacji w tej formie to opdowiednio wartoœci: left, right, top, bottom.
							//	if (left > 0 && right > 0 && top > 0 && bottom > 0) {
							//		SDL_Log("1: %f, %f, %f, %f", left, right, top, bottom);
							//	}
							//}
							
						}
					}

				}

				//object.transform.position.x = finalPositions[i].x;
				//object.transform.position.y = finalPositions[i].y;
			} else { // We're outside! hit the boundry
				// if we somehow end up here we should make it back with some logic to the boundry
				// Structure overall could be better theres no need for some objects to fall through this if statement..
				SDL_Log("We're HERE !!!!");
				object.transform.position.x = Math::Clamp(object.transform.position.x, boundry.x + radius, boundry.w - radius);
				object.transform.position.y = Math::Clamp(object.transform.position.y, boundry.y + radius, boundry.h - radius);
				return;
			}

			object.transform.position.x = calculatedPositions[i].x;
			object.transform.position.y = calculatedPositions[i].y;
			
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