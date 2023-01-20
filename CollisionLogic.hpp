#pragma once
#include "Framework.hpp"
#include "SceneGraph.hpp"
#include "Log.hpp"

namespace Collision {

	block BounceOutsideBoundry(
		const SceneGraph::SceneGraph& sceneGraph, 
		vector<Vector::Vector2<float>>& calculatedCirclePositions, 
		vector<Vector::Vector2<float>>& calculatedSquarePositions,
		const float& deltaTime
	) {

		/* Circle */
		for (size current = 0; current < sceneGraph.circleObjectsCount; current++) {
			auto& object = sceneGraph.circleObjects[current];
			auto& proposedPosition = calculatedCirclePositions[current];
			const auto& type = (Surface::Circle*)(object.surface.type);
			const auto& radius = type->radius;

			/* If we're outside X boundry. */
			if (proposedPosition.x < sceneGraph.sceneBoundry.x + radius || proposedPosition.x > sceneGraph.sceneBoundry.w - radius) {
				/* If we hit it Then because we can be already in it! we change our position to be outside the boundry */
				//proposedPosition.x = Math::Clamp(object.transform.position.x, sceneGraph.sceneBoundry.x + radius, sceneGraph.sceneBoundry.w - radius);
				object.rigidbody.velocity.x *= -1;
				proposedPosition = object.calculateMove(object.transform, object.rigidbody, deltaTime);
			}

			/* If we're outside Y boundry. */
			if (proposedPosition.y < sceneGraph.sceneBoundry.y + radius || proposedPosition.y > sceneGraph.sceneBoundry.h - radius) {
				/* If we hit it Then because we can be already in it! we change our position to be outside the boundry */
				//proposedPosition.y = Math::Clamp(object.transform.position.y, sceneGraph.sceneBoundry.y + radius, sceneGraph.sceneBoundry.h - radius);
				object.rigidbody.velocity.y *= -1;
				proposedPosition = object.calculateMove(object.transform, object.rigidbody, deltaTime);
			}
		}

		/* Square */
		for (size current = 0; current < sceneGraph.squareObjectsCount; current++) {
			auto& object = sceneGraph.squareObjects[current];
			auto& proposedPosition = calculatedSquarePositions[current];
			const auto& type = (Surface::Square*)(object.surface.type);
			const auto& extent = type->extent;

			/* If we're outside X boundry. */
			if (proposedPosition.x < sceneGraph.sceneBoundry.x + extent.x / 2 || proposedPosition.x > sceneGraph.sceneBoundry.w - extent.x / 2) {
				/* If we hit it Then because we can be already in it! we change our position to be outside the boundry */
				//proposedPosition.x = Math::Clamp(object.transform.position.x, sceneGraph.sceneBoundry.x + extent.x, sceneGraph.sceneBoundry.w - extent.x);
				object.rigidbody.velocity.x *= -1;
				proposedPosition = object.calculateMove(object.transform, object.rigidbody, deltaTime);

				//Log::Info("Should Flip: X");
				//Log::Info("Should Flip: X, %f, %f", proposedPosition.x, proposedPosition.y);
			}

			/* If we're outside Y boundry. */
			if (proposedPosition.y < sceneGraph.sceneBoundry.y + extent.y / 2 || proposedPosition.y > sceneGraph.sceneBoundry.h - extent.y / 2) {
				/* If we hit it Then because we can be already in it! we change our position to be outside the boundry */
				//proposedPosition.y = Math::Clamp(object.transform.position.y, sceneGraph.sceneBoundry.y + extent.y, sceneGraph.sceneBoundry.h - extent.y);
				object.rigidbody.velocity.y *= -1;
				proposedPosition = object.calculateMove(object.transform, object.rigidbody, deltaTime);

				//Log::Info("Should Flip: Y");
				//Log::Info("Should Flip: Y, %f, %f", proposedPosition.x, proposedPosition.y);
			}
		}
	}

	block BounceInsideBoundry(
		const SceneGraph::SceneGraph& sceneGraph,
		vector<Vector::Vector2<float>>& calculatedCirclePositions,
		vector<Vector::Vector2<float>>& calculatedSquarePositions,
		const float& deltaTime
	) {
		/* Circle */
		for (size current = 0; current < sceneGraph.circleObjectsCount; current++) {
			auto& object = sceneGraph.circleObjects[current];
			auto& proposedPosition = calculatedCirclePositions[current];
			const auto& type = (Surface::Circle *)(object.surface.type);
			const auto& radius = type->radius;

			for (size triggerIndex = 0; triggerIndex < sceneGraph.triggersCount; triggerIndex++) {
				const auto& trigger = sceneGraph.triggers[triggerIndex];
				if (proposedPosition.x > trigger.boundry.x && proposedPosition.y > trigger.boundry.y &&
					proposedPosition.x < trigger.boundry.w && proposedPosition.y < trigger.boundry.h
					) {
					trigger.callback(SceneGraph::player1);
				}
			}
			
		}

		/* Square */
		for (size current = 0; current < sceneGraph.squareObjectsCount; current++) {
			auto& object = sceneGraph.squareObjects[current];
			auto& proposedPosition = calculatedSquarePositions[current];
			const auto& type = (Surface::Square*)(object.surface.type);
			const auto& extent = type->extent;

			for (size triggerIndex = 0; triggerIndex < sceneGraph.triggersCount; triggerIndex++) {
				const auto& trigger = sceneGraph.triggers[triggerIndex];
				if (proposedPosition.x > trigger.boundry.x && proposedPosition.y > trigger.boundry.y &&
					proposedPosition.x < trigger.boundry.w && proposedPosition.y < trigger.boundry.h
					) {
					trigger.callback(SceneGraph::player2);
				}
			}
		}
	}

	block BounceOutsideBoxCollider(
		const SceneGraph::SceneGraph& sceneGraph,
		vector<Vector::Vector2<float>>& calculatedCirclePositions,
		vector<Vector::Vector2<float>>& calculatedSquarePositions,
		const float& deltaTime
	) {

		for (size collisionIndex = 0; collisionIndex < sceneGraph.staticCollisionsCount; collisionIndex++) {
			const auto& collision = sceneGraph.staticCollisions[collisionIndex];

			/* Circle */
			for (size current = 0; current < sceneGraph.circleObjectsCount; current++) {
				auto& object = sceneGraph.circleObjects[current];
				auto& proposedPosition = calculatedCirclePositions[current];
				const auto& type = (Surface::Circle*)(object.surface.type);
				const auto& radius = type->radius;

				/* If we're outside X boundry. */
				if (proposedPosition.x < collision.x + radius || proposedPosition.x > collision.w - radius) {
					/* If we hit it Then because we can be already in it! we change our position to be outside the boundry */
					//proposedPosition.x = Math::Clamp(object.transform.position.x, sceneGraph.sceneBoundry.x + radius, sceneGraph.sceneBoundry.w - radius);
					object.rigidbody.velocity.x *= -1;
					proposedPosition = object.calculateMove(object.transform, object.rigidbody, deltaTime);

					Log::Info("Should Flip: X");
				}

				/* If we're outside Y boundry. */
				if (proposedPosition.y < collision.y + radius || proposedPosition.y > collision.h - radius) {
					/* If we hit it Then because we can be already in it! we change our position to be outside the boundry */
					//proposedPosition.y = Math::Clamp(object.transform.position.y, sceneGraph.sceneBoundry.y + radius, sceneGraph.sceneBoundry.h - radius);
					object.rigidbody.velocity.y *= -1;
					proposedPosition = object.calculateMove(object.transform, object.rigidbody, deltaTime);

					Log::Info("Should Flip: Y");
				}
			}

			/* Square */
			for (size current = 0; current < sceneGraph.squareObjectsCount; current++) {
				auto& object = sceneGraph.squareObjects[current];
				auto& proposedPosition = calculatedSquarePositions[current];
				const auto& type = (Surface::Square*)(object.surface.type);
				const auto& extent = type->extent;

				/* If we're outside X boundry. */
				if (proposedPosition.x < collision.x + extent.x / 2 || proposedPosition.x > collision.w - extent.x / 2) {
					/* If we hit it Then because we can be already in it! we change our position to be outside the boundry */
					//proposedPosition.x = Math::Clamp(object.transform.position.x, sceneGraph.sceneBoundry.x + extent.x, sceneGraph.sceneBoundry.w - extent.x);
					object.rigidbody.velocity.x *= -1;
					proposedPosition = object.calculateMove(object.transform, object.rigidbody, deltaTime);

					Log::Info("Should Flip: X");
					//Log::Info("Should Flip: X, %f, %f", proposedPosition.x, proposedPosition.y);
				}

				/* If we're outside Y boundry. */
				if (proposedPosition.y < collision.y + extent.y / 2 || proposedPosition.y > collision.h - extent.y / 2) {
					/* If we hit it Then because we can be already in it! we change our position to be outside the boundry */
					//proposedPosition.y = Math::Clamp(object.transform.position.y, sceneGraph.sceneBoundry.y + extent.y, sceneGraph.sceneBoundry.h - extent.y);
					object.rigidbody.velocity.y *= -1;
					proposedPosition = object.calculateMove(object.transform, object.rigidbody, deltaTime);

					Log::Info("Should Flip: Y");
					//Log::Info("Should Flip: Y, %f, %f", proposedPosition.x, proposedPosition.y);
				}
			}
		}

	}

	namespace Circle {
		block CheckCollisionCircle(
			SceneGraph::SceneGraph& sceneGraph,
			vector<Vector::Vector2<float>>& calculatedCirclePositions,
			const float& deltaTime
		) {
			for (size current = 0; current < sceneGraph.circleObjectsCount; current++) {
				auto& object = sceneGraph.circleObjects[current];
				auto& proposedPosition = calculatedCirclePositions[current];

				const auto& collision = (Collision::CircleBody*)object.collision.type;
				const auto& type = (Surface::Circle*)(object.surface.type);
				const auto& radius = type->radius;

				for (size i = 0; i < sceneGraph.circleObjectsCount; i++) {

					auto& other = sceneGraph.circleObjects[i];
					const auto& otherCollision = (Collision::CircleBody*)other.collision.type;
					const auto& otherType = (Surface::Circle*)(other.surface.type);

					if (object.identifier != other.identifier) {

						auto& otherProposedPosition = calculatedCirclePositions[i];

						const auto& otherRadius = otherType->radius;
						const auto& center1 = proposedPosition;
						const auto& center2 = otherProposedPosition;
						const auto lengthBetween = (float)Vector::LengthBetween(center1, center2);
	
						// Collision Detected !
						if (lengthBetween < radius + otherRadius) {
							DEBUG sceneGraph.gizmoLines.push_back({ object.transform.position, other.transform.position, { 255, 0, 0, 255 } });

							Vector::Vector2<float> separation { // simple normalization
								(center1.x - center2.x) / (float)lengthBetween,
								(center1.y - center2.y) / (float)lengthBetween
							};

							//DEBUG Log::Info("Circle Separation: %f, %f", separation.x, separation.y);
	
							if (Collision::isSeperationOn) {
								const auto recalculatedPosition = Vector::Addition(
									object.transform.position, {
										separation.x * (float)(otherRadius - lengthBetween * 0.5f),
										separation.y * (float)(otherRadius - lengthBetween * 0.5f)
									}
								);

								const auto otherRecalculatedPosition = Vector::Subtract(
									other.transform.position, {
										separation.x * (float)(radius - lengthBetween * 0.5f),
										separation.y * (float)(radius - lengthBetween * 0.5f)
									}
								);

								// Check with boundry.
								proposedPosition.x = Math::Clamp(recalculatedPosition.x, sceneGraph.sceneBoundry.x + radius, sceneGraph.sceneBoundry.w - radius);
								proposedPosition.y = Math::Clamp(recalculatedPosition.y, sceneGraph.sceneBoundry.y + radius, sceneGraph.sceneBoundry.h - radius);
								otherProposedPosition.x = Math::Clamp(otherRecalculatedPosition.x, sceneGraph.sceneBoundry.x + radius, sceneGraph.sceneBoundry.w - radius);
								otherProposedPosition.y = Math::Clamp(otherRecalculatedPosition.y, sceneGraph.sceneBoundry.y + radius, sceneGraph.sceneBoundry.h - radius);
							}

							if (Collision::isReflectionOn) {
								const auto offset1 = Vector::MultiplyByScalar(separation, (float)Vector::DotProduct(object.rigidbody.velocity, separation) * 2.0f);
								object.rigidbody.velocity = Vector::Subtract(object.rigidbody.velocity, offset1);
					
								separation = Vector::Vector2<float>{ separation.x * -1.0f, separation.y * -1.0f };
								
								const auto offset2 = Vector::MultiplyByScalar(separation, (float)Vector::DotProduct(other.rigidbody.velocity, separation) * 2.0f);
								other.rigidbody.velocity = Vector::Subtract(other.rigidbody.velocity, offset2);

								// Because we changed velocity we need to recalculate move position to apply changes.
								proposedPosition = object.calculateMove(object.transform, object.rigidbody, deltaTime);
								otherProposedPosition = other.calculateMove(other.transform, other.rigidbody, deltaTime);
							}
						}
					}
				}
			}
		}
	}

	namespace Square {

		void CollisionSquareStatic(
			const Rectangle& sceneBoundry,
			Vector::Vector2<float>& position,
			Vector::Vector2<float>& proposedPosition,
			const Rectangle& boundry,
			const Rectangle& otherBoundry
		) {
			const Vector::Vector2<float>& objectCenter = proposedPosition;

			// Punkt na prostokacie najblizszy srodkowi okregu.
			Vector::Vector2<float> point;

			// Patrzymy punkt na prostokącie najbliższy środkowi okręgu.
			point.x = Math::Clamp(objectCenter.x, otherBoundry.x, otherBoundry.w);
			point.y = Math::Clamp(objectCenter.y, otherBoundry.y, otherBoundry.h);

			const float lengthBetween = (float)Vector::LengthBetween(objectCenter, point);

			const float left = (boundry.w + objectCenter.x) - (otherBoundry.x);
			const float right = (otherBoundry.w) - (boundry.x + objectCenter.x);
			const float top = (boundry.h + objectCenter.y) - (otherBoundry.y);
			const float bottom = (otherBoundry.h) - (boundry.y + objectCenter.y);

			if (left > 0 && right > 0 && top > 0 && bottom > 0) {

				// DEBUG Log::Info("Between: %d", lengthBetween);

				// Wektro separacji w tej formie to opdowiednio wartości: left, right, top, bottom.
				Vector::Vector2<float> separation;
				left < right ? separation.x = -left : separation.x = right;
				top < bottom ? separation.y = -top : separation.y = bottom;
				abs(separation.x) < abs(separation.y) ? separation.y = 0 : separation.x = 0;

				// Zmianiamy pozycje obiektu.
				if (Collision::isSeperationOn) {
					auto recalculatedPosition = Vector::Addition(
						position, {
							separation.x,
							separation.y
						}
					);

					// Check with boundry.
					proposedPosition.x = Math::Clamp(recalculatedPosition.x, sceneBoundry.x + boundry.x / 2, sceneBoundry.w - boundry.x / 2);
					proposedPosition.y = Math::Clamp(recalculatedPosition.y, sceneBoundry.y + boundry.y / 2, sceneBoundry.h - boundry.y / 2);
				}
			}
		}

		block CheckCollisionSquare(
			SceneGraph::SceneGraph& sceneGraph,
			vector<Vector::Vector2<float>>& calculatedSquarePositions,
			const float& deltaTime
		) {
			for (size current = 0; current < sceneGraph.squareObjectsCount; current++) {
				auto& object = sceneGraph.squareObjects[current];
				auto& proposedPosition = calculatedSquarePositions[current];

				const auto& collision = (Collision::SquareBody*)object.collision.type;
				const auto& type = (Surface::Square*)(object.surface.type);
				const auto& boundry = collision->boundry;
				
				for (size i = 0; i < sceneGraph.squareObjectsCount; i++) {
					auto& other = sceneGraph.squareObjects[i];
					
					if (object.identifier != other.identifier) {
						auto& otherProposedPosition = calculatedSquarePositions[i];

						const auto& otherCollision = (Collision::SquareBody*)other.collision.type;
						const auto& otherType = (Surface::Square*)(other.surface.type);
						const auto& otherBoundry = otherCollision->boundry; // object.collision.boundry instead should be used...

						const Vector::Vector2<float>& center1 = proposedPosition;
						const Vector::Vector2<float>& center2 = otherProposedPosition;
						const double lengthBetween = Vector::LengthBetween(center1, center2);

						const float left = (boundry.w + center1.x) - (otherBoundry.x + center2.x);
						const float right = (otherBoundry.w + center2.x) - (boundry.x + center1.x);
						const float top = (boundry.h + center1.y) - (otherBoundry.y + center2.y);
						const float bottom = (otherBoundry.h + center2.y) - (boundry.y + center1.y);

						// Collision Detected
						if (left > 0 && right > 0 && top > 0 && bottom > 0) {
							DEBUG sceneGraph.gizmoLines.push_back({ object.transform.position, other.transform.position, { 255, 0, 0, 255 } });
							
							// Wektro separacji w tej formie to opdowiednio wartości: left, right, top, bottom.
							Vector::Vector2<float> separation;
							left < right ? separation.x = -left : separation.x = right;
							top < bottom ? separation.y = -top : separation.y = bottom;
							abs(separation.x) < abs(separation.y) ? separation.y = 0 : separation.x = 0;

							// Zmianiamy pozycje obiektu.
							if (Collision::isSeperationOn) {
								auto recalculatedPosition = Vector::Addition(
									object.transform.position, {
										separation.x,
										separation.y
									}
								);
							
								auto otherRecalculatedPosition = Vector::Subtract(
									other.transform.position, {
										separation.x,
										separation.y
									}
								);
							
								// Check with boundry.
								proposedPosition.x = Math::Clamp(recalculatedPosition.x, sceneGraph.sceneBoundry.x + boundry.x / 2, sceneGraph.sceneBoundry.w - boundry.x / 2);
								proposedPosition.y = Math::Clamp(recalculatedPosition.y, sceneGraph.sceneBoundry.y + boundry.y / 2, sceneGraph.sceneBoundry.h - boundry.y / 2);
								otherProposedPosition.x = Math::Clamp(otherRecalculatedPosition.x, sceneGraph.sceneBoundry.x + otherBoundry.x / 2, sceneGraph.sceneBoundry.w - otherBoundry.x / 2);
								otherProposedPosition.y = Math::Clamp(otherRecalculatedPosition.y, sceneGraph.sceneBoundry.y + otherBoundry.y / 2, sceneGraph.sceneBoundry.h - otherBoundry.y / 2);
							}
							
							//// Mówimy obiektowi żeby poruszał się teraz w innym torze.
							if (Collision::isReflectionOn) {
								if (separation.x == 0) {
									object.rigidbody.velocity.x *= 1;
									other.rigidbody.velocity.x *= 1;
									object.rigidbody.velocity.y *= -1;
									other.rigidbody.velocity.y *= -1;
								} else {
									object.rigidbody.velocity.x *= -1;
									other.rigidbody.velocity.x *= -1;
									object.rigidbody.velocity.y *= 1;
									other.rigidbody.velocity.y *= 1;
								}

								// Because we changed velocity we need to recalculate move position to apply changes.
								proposedPosition = object.calculateMove(object.transform, object.rigidbody, deltaTime);
								otherProposedPosition = other.calculateMove(other.transform, other.rigidbody, deltaTime);
							}
						}
					}
				}

				for (size i = 0; i < sceneGraph.staticCollisionsCount; i++) {
					auto& collision = sceneGraph.staticCollisions[i];

					CollisionSquareStatic(
						sceneGraph.sceneBoundry,
						object.transform.position, proposedPosition, boundry,
						collision
					);
				}

			}
		}
	}

	namespace BetweenTypes {

		void CollisionCircleSquareStatic(
			SceneGraph::SceneGraph& sceneGraph, 
			Object::Object& object,
			Vector::Vector2<float>& proposedPosition,
			const float& radius,
			const Rectangle& otherBoundry
		) {
			const Vector::Vector2<float>& objectCenter = proposedPosition;
			auto& position = object.transform.position;

			// Punkt na prostokacie najblizszy srodkowi okregu.
			Vector::Vector2<float> point;

			// Patrzymy punkt na prostokącie najbliższy środkowi okręgu.
			point.x = Math::Clamp(objectCenter.x, otherBoundry.x, otherBoundry.w);
			point.y = Math::Clamp(objectCenter.y, otherBoundry.y, otherBoundry.h);

			const float lengthBetween = (float)Vector::LengthBetween(objectCenter, point);

			//DEBUG Log::Info("SC %f, %f", lengthBetween, radius);
			//DEBUG Log::Info("%f, %f", objectCenter.y, point.y);
			//DEBUG sceneGraph.gizmoLines.push_back({ objectCenter, point, { 255, 0, 0, 255 } });

			if (lengthBetween < radius) { // Collision Detected

				if (objectCenter.x == point.x && objectCenter.y == point.y) {

					// Środek okręgu leży na prostokącie, wtedy wektor separacji trzeba policzyć, jak w przypadku prostokątów
					if (Collision::isSeperationOn) {
						const float left = objectCenter.x - otherBoundry.x + radius;
						const float right = otherBoundry.w - objectCenter.x + radius;
						const float top = objectCenter.y - otherBoundry.y + radius;
						const float bottom = otherBoundry.h - objectCenter.y + radius;

						// Wektro separacji w tej formie to opdowiednio wartości: left, right, top, bottom.
						Vector::Vector2<float> separation;
						left < right ? separation.x = -left : separation.x = right;
						top < bottom ? separation.y = -top : separation.y = bottom;
						abs(separation.x) < abs(separation.y) ? separation.y = 0 : separation.x = 0;

						//DEBUG sceneGraph.gizmoLines.push_back({ position, separation, { 255, 0, 0, 255 } });
						//DEBUG sceneGraph.gizmoLines.push_back({ Vector::Vector2<float>{ 0, 0 }, position, {255, 0, 0, 255} });

						//DEBUG Log::Info("HERE NOW");
						//DEBUG Log::Info("old: %f, %f", proposedPosition.x, proposedPosition.y);
						//DEBUG Log::Info("sep: %f, %f", separation.x, separation.y);

						auto recalculatedPosition = Vector::Addition(
							proposedPosition, {
								separation.x,
								separation.y
							}
						);

						//DEBUG Log::Info("pos: %f, %f", recalculatedPosition.x, recalculatedPosition.y);

						proposedPosition.x = Math::Clamp(recalculatedPosition.x, sceneGraph.sceneBoundry.x + radius, sceneGraph.sceneBoundry.w - radius);
						proposedPosition.y = Math::Clamp(recalculatedPosition.y, sceneGraph.sceneBoundry.y + radius, sceneGraph.sceneBoundry.h - radius);
					}

				} else {

					//DEBUG sceneGraph.gizmoLines.push_back({ Vector::Vector2<float>{ 0, 0 }, position, {255, 0, 0, 255} });
					//DEBUG {
					//	const Vector::Vector2 seppos = Vector::Addition(position, separation);
						//Log::Info("Separation: %f, %f, Position: %f, %f", separation.x, separation.y, position.x, position.y);
						//Log::Info("%f, %f", (objectCenter.y - point.y), lengthBetween);
						//Log::Info("%f", separation.y * (radius - lengthBetween));
						//Log::Info("Separation: %f, %f, Position: %f, %f", objectCenter.x, objectCenter.y, position.x, position.y);
						//sceneGraph.gizmoLines.push_back({ objectCenter, point, { 255, 0, 0, 255 } });
					//}
					//DEBUG 

					if (Collision::isSeperationOn) {

						// Rigidbody Logic
						Moveable::CollisionHitY(object.rigidbody);

						Vector::Vector2<float> separation { // Simple normalization
							(objectCenter.x - point.x) / lengthBetween,
							(objectCenter.y - point.y) / lengthBetween
						};

						auto recalculatedPosition = Vector::Addition(
							proposedPosition, {
								separation.x * (radius - lengthBetween),
								separation.y * (radius - lengthBetween)
							}
						);

						//recalculatedPosition.x = (float)(int)recalculatedPosition.x;
						//recalculatedPosition.y = (float)(int)recalculatedPosition.y;

						//DEBUG Log::Info("%f, %f", recalculatedPosition.x, recalculatedPosition.y);

						proposedPosition.x = Math::Clamp(recalculatedPosition.x, sceneGraph.sceneBoundry.x + radius, sceneGraph.sceneBoundry.w - radius);
						proposedPosition.y = Math::Clamp(recalculatedPosition.y, sceneGraph.sceneBoundry.y + radius, sceneGraph.sceneBoundry.h - radius);

						//DEBUG Log::Info("END: %f, %f, %f", separation.y * (radius - lengthBetween), recalculatedPosition.x, recalculatedPosition.y);
					}
				}
			}
		}

		void CollisionCircleSquareDynamic(
			const Rectangle& sceneBoundry,
			Vector::Vector2<float>& position,
			Vector::Vector2<float>& proposedPosition,
			const float& radius,
			Vector::Vector2<float>& otherPosition,
			Vector::Vector2<float>& otherProposedPosition,
			const Rectangle& otherBoundry
		) {
			const Vector::Vector2<float>& objectCenter = proposedPosition;
			const Vector::Vector2<float>& otherCenter = otherProposedPosition;

			// Punkt na prostokacie najblizszy srodkowi okregu.
			Vector::Vector2<float> point;

			// Patrzymy punkt na prostokącie najbliższy środkowi okręgu.
			point.x = Math::Clamp(objectCenter.x, otherCenter.x + otherBoundry.x, otherCenter.x + otherBoundry.w);
			point.y = Math::Clamp(objectCenter.y, otherCenter.y + otherBoundry.y, otherCenter.y + otherBoundry.h);

			const float lengthBetween = (float)Vector::LengthBetween(objectCenter, point);
			//DEBUG Log::Info("Between: %d", lengthBetween);
			//DEBUG Log::Info("Point: %f, %f", point.x, point.y);
			//DEBUG Log::Info("Difference: %f, %f", differnce.x, differnce.y);

			if (lengthBetween < radius) { // Collision Detected
				//DEBUG sceneGraph.gizmoLines.push_back({ object.transform.position, other.transform.position, { 255, 0, 0, 255 } });
				if (objectCenter.x == point.x && objectCenter.y == point.y) {
					// środek okręgu leży na prostokącie, wtedy wektor separacji trzeba policzyć, jak w przypadku prostokątów
					if (Collision::isSeperationOn) {
						//DEBUG Log::Info("1. Between: %f", lengthBetween);
						const float left = objectCenter.x - otherCenter.x + otherBoundry.x + radius;
						const float right = otherCenter.x + otherBoundry.w - objectCenter.x + radius;
						const float top = objectCenter.y - otherCenter.x + otherBoundry.y + radius;
						const float bottom = otherCenter.x + otherBoundry.h - objectCenter.y + radius;
						// Wektro separacji w tej formie to opdowiednio wartości: left, right, top, bottom.
						Vector::Vector2<float> separation;
						left < right ? separation.x = -left : separation.x = right;
						top < bottom ? separation.y = -top : separation.y = bottom;
						abs(separation.x) < abs(separation.y) ? separation.y = 0 : separation.x = 0;
						//DEBUG Log::Info("1. Separation: %f, %f", separation.x, separation.y);

						auto recalculatedPosition = Vector::Subtract(
							position, {
								separation.x,
								separation.y
							}
						);
						//DEBUG sceneGraph.gizmoLines.push_back({ object.transform.position, recalculatedPosition, { 255, 0, 0, 255 } });
						auto otherRecalculatedPosition = Vector::Addition(
							otherPosition, {
								separation.x,
								separation.y
							}
						);

						// Check with boundry.
						proposedPosition.x = Math::Clamp(recalculatedPosition.x, sceneBoundry.x + radius, sceneBoundry.w - radius);
						proposedPosition.y = Math::Clamp(recalculatedPosition.y, sceneBoundry.y + radius, sceneBoundry.h - radius);
						otherProposedPosition.x = Math::Clamp(otherRecalculatedPosition.x, sceneBoundry.x + otherBoundry.x / 2, sceneBoundry.w - otherBoundry.x / 2);
						otherProposedPosition.y = Math::Clamp(otherRecalculatedPosition.y, sceneBoundry.y + otherBoundry.y / 2, sceneBoundry.h - otherBoundry.y / 2);
					}

				} else {
					Vector::Vector2<float> separation { // simple normalization
						(objectCenter.x - point.x) / (float)lengthBetween,
						(objectCenter.y - point.y) / (float)lengthBetween
					};
					//DEBUG Log::Info("1. Separation: %f, %f", separation.x, separation.y);
					//DEBUG sceneGraph.gizmoLines.push_back({ object.transform.position, separation, { 255, 0, 0, 255 } });
					//DEBUG Log::Info("2. Separation: %f, %f", separation.x, separation.y);
					if (Collision::isSeperationOn) {
						// * (radius − lengthBetween)
						//DEBUG Log::Info("2. huh: %f", radius - lengthBetween);
						const auto recalculatedPosition = Vector::Addition(
							position, {
								separation.x,
								separation.y
							}
						);
						//DEBUG Log::Info("1. Separation: %f, %f", recalculatedPosition.x, recalculatedPosition.y);
						const auto otherRecalculatedPosition = Vector::Subtract(
							otherPosition, {
								separation.x,
								separation.y
							}
						);
						// Check with boundry.
						proposedPosition.x = Math::Clamp(recalculatedPosition.x, sceneBoundry.x + radius, sceneBoundry.w - radius);
						proposedPosition.y = Math::Clamp(recalculatedPosition.y, sceneBoundry.y + radius, sceneBoundry.h - radius);
						otherProposedPosition.x = Math::Clamp(otherRecalculatedPosition.x, sceneBoundry.x + otherBoundry.x / 2, sceneBoundry.w - otherBoundry.y / 2);
						otherProposedPosition.y = Math::Clamp(otherRecalculatedPosition.y, sceneBoundry.y + otherBoundry.y / 2, sceneBoundry.h - otherBoundry.y / 2);
					}
				}
			}
		}

		block CheckCollisionCircleSquare(
			SceneGraph::SceneGraph& sceneGraph,
			vector<Vector::Vector2<float>>& calculatedCirclePositions,
			vector<Vector::Vector2<float>>& calculatedSquarePositions,
			const float& deltaTime
		) {

			/* Check Circle -> Square is enought becuse we do logic for the other inside.
				Which means no need to extra enumerate Square -> Circle... */

			//DEBUG Log::Info("CheckCollisionCircleSquare CALL");

			/* Enumerate through Circles */
			for (size current = 0; current < sceneGraph.circleObjectsCount; current++) {

				//DEBUG Log::Info("CheckCollisionCircleSquare HOW MANY?");

				auto& object = sceneGraph.circleObjects[current];
				auto& proposedPosition = calculatedCirclePositions[current];

				const auto& collision = (Collision::CircleBody*)object.collision.type;
				const auto& radius = collision->radius;

				/* Enumerate through Squares [ Here we don't have to look for same ID ] */
				for (size i = 0; i < sceneGraph.squareObjectsCount; i++) {

					auto& other = sceneGraph.squareObjects[i];
					auto& otherProposedPosition = calculatedSquarePositions[i];

					const auto& otherCollision = (Collision::SquareBody*)other.collision.type;
					const auto& otherBoundry = otherCollision->boundry;

					// 1 Circle - 1 Square CHECK
					//CollisionCircleSquareDynamic(
					//	sceneGraph.sceneBoundry, 
					//	object.transform.position, proposedPosition, radius, 
					//	other.transform.position, otherProposedPosition, otherBoundry
					//);

				}

				/* Enumarete through static Squares [ Those don't bounce ] */
				for (size i = 0; i < sceneGraph.staticCollisionsCount; i++) {
					auto& collision = sceneGraph.staticCollisions[i];

					CollisionCircleSquareStatic(
						sceneGraph,
						object, proposedPosition, radius,
						collision
					);
				}

			}
		}

	}

}