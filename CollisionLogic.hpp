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
			}

			/* If we're outside Y boundry. */
			if (proposedPosition.y < sceneGraph.sceneBoundry.y + extent.y / 2 || proposedPosition.y > sceneGraph.sceneBoundry.h - extent.y / 2) {
				/* If we hit it Then because we can be already in it! we change our position to be outside the boundry */
				//proposedPosition.y = Math::Clamp(object.transform.position.y, sceneGraph.sceneBoundry.y + extent.y, sceneGraph.sceneBoundry.h - extent.y);
				object.rigidbody.velocity.y *= -1;
				object.calculateMove(object.transform, object.rigidbody, deltaTime);
				//Log::Info("Should Flip: Y");
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

			if (proposedPosition.x > sceneGraph.sceneBoundry.x + radius && proposedPosition.y > sceneGraph.sceneBoundry.y + radius &&
				proposedPosition.x < sceneGraph.sceneBoundry.w - radius && proposedPosition.y < sceneGraph.sceneBoundry.h - radius
			) {
				// Flip Logic HERE!
				//Log::Info("Position: %f, %f", proposedPosition.x, proposedPosition.y);
			}
		}

		/* Square */
		for (size current = 0; current < sceneGraph.squareObjectsCount; current++) {
			auto& object = sceneGraph.squareObjects[current];
			auto& proposedPosition = calculatedSquarePositions[current];
			const auto& type = (Surface::Square*)(object.surface.type);
			const auto& extent = type->extent;

			if (proposedPosition.x > sceneGraph.sceneBoundry.x + extent.x / 2 && proposedPosition.y > sceneGraph.sceneBoundry.y + extent.y / 2 &&
				proposedPosition.x < sceneGraph.sceneBoundry.w - extent.x / 2 && proposedPosition.y < sceneGraph.sceneBoundry.h - extent.y / 2
				) {
				// Flip Logic HERE!
				//Log::Info("Position: %f, %f", proposedPosition.x, proposedPosition.y);
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
				const auto& extent = type->extent;
				
				for (size i = 0; i < sceneGraph.squareObjectsCount; i++) {
					auto& other = sceneGraph.squareObjects[i];
					
					if (object.identifier != other.identifier) {
						auto& otherProposedPosition = calculatedSquarePositions[i];

						const auto& otherCollision = (Collision::SquareBody*)other.collision.type;
						const auto& otherType = (Surface::Square*)(other.surface.type);
						const auto& otherExtent = otherType->extent; // object.collision.boundry instead should be used...

						const Vector::Vector2<float>& center1 = proposedPosition;
						const Vector::Vector2<float>& center2 = otherProposedPosition;
						const double lengthBetween = Vector::LengthBetween(center1, center2);

						const float left = (collision->boundry.x + center1.x) - (otherCollision->boundry.x + center2.x);
						const float right = (otherCollision->boundry.w + center2.x) - (collision->boundry.x + center1.x);
						const float top = (collision->boundry.h + center1.y) - (otherCollision->boundry.y + center2.y);
						const float bottom = (otherCollision->boundry.h + center2.y) - (collision->boundry.y + center1.y);

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
								proposedPosition.x = Math::Clamp(recalculatedPosition.x, sceneGraph.sceneBoundry.x + extent.x / 2, sceneGraph.sceneBoundry.w - extent.x / 2);
								proposedPosition.y = Math::Clamp(recalculatedPosition.y, sceneGraph.sceneBoundry.y + extent.y / 2, sceneGraph.sceneBoundry.h - extent.y / 2);
								otherProposedPosition.x = Math::Clamp(otherRecalculatedPosition.x, sceneGraph.sceneBoundry.x + otherExtent.x / 2, sceneGraph.sceneBoundry.w - otherExtent.x / 2);
								otherProposedPosition.y = Math::Clamp(otherRecalculatedPosition.y, sceneGraph.sceneBoundry.y + otherExtent.y / 2, sceneGraph.sceneBoundry.h - otherExtent.y / 2);
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
			}
		}
	}

	namespace BetweenTypes {

		block CheckCollisionCircleSquare(
			SceneGraph::SceneGraph& sceneGraph,
			vector<Vector::Vector2<float>>& calculatedCirclePositions,
			vector<Vector::Vector2<float>>& calculatedSquarePositions,
			const float& deltaTime
		) {

			/* Enumerate through Circles */
			for (size current = 0; current < sceneGraph.circleObjectsCount; current++) {

				auto& object = sceneGraph.circleObjects[current];
				auto& proposedPosition = calculatedCirclePositions[current];

				const auto& collision = (Collision::CircleBody*)object.collision.type;
				const auto& type = (Surface::Circle*)(object.surface.type);
				const auto& radius = type->radius;

				/* Enumerate through Squares [ Here we don't have to look for same ID ] */
				for (size i = 0; i < sceneGraph.squareObjectsCount; i++) {

					auto& other = sceneGraph.squareObjects[i];
					auto& otherProposedPosition = calculatedSquarePositions[i];

					const auto& otherCollision = (Collision::SquareBody*)other.collision.type;
					const auto& otherType = (Surface::Square*)(other.surface.type);
					const auto& otherExtent = otherType->extent;

					{ // 1 Circle - 1 Square CHECK
						const Vector::Vector2<float>& objectCenter = proposedPosition;
						const Vector::Vector2<float>& otherCenter = otherProposedPosition;

						//const double lengthBetween = Vector::LengthBetween(center1, center2);
						//const float left = (collision->radius + objectCenter.x) - (otherCollision->boundry.x + otherCenter.x);
						//const float right = (otherCollision->boundry.w + otherCenter.x) - (collision->radius + objectCenter.x);
						//const float top = (collision->radius + objectCenter.y) - (otherCollision->boundry.y + otherCenter.y);
						//const float bottom = (otherCollision->boundry.h + otherCenter.y) - (collision->radius + objectCenter.y);

						//const float left = objectCenter.x - otherCollision->boundry.x + radius;
						//const float right = otherCollision->boundry.w - objectCenter.x + radius;
						//const float top = objectCenter.y - otherCollision->boundry.y + radius;
						//const float bottom = otherCollision->boundry.h - objectCenter.y + radius;

	
						// Punkt na prostokacie najblizszy srodkowi okregu.
						Vector::Vector2<float> point;
						//point.x = Math::Clamp(object.transform.position.x, left, right);
						//point.y = Math::Clamp(object.transform.position.y, top, bottom);

						// Patrzymy punkt na prostokącie najbliższy środkowi okręgu.
						point.x = Math::Clamp(objectCenter.x, otherCenter.x + otherCollision->boundry.x, otherCenter.x + otherCollision->boundry.w);
						point.y = Math::Clamp(objectCenter.y, otherCenter.y + otherCollision->boundry.y, otherCenter.y + otherCollision->boundry.h);
	
						// długość różnicy
						//const Vector::Vector2<float> differnce = Vector::Subtract(objectCenter, point);
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

									const float left = objectCenter.x - otherCenter.x + otherCollision->boundry.x + radius;
									const float right = otherCenter.x + otherCollision->boundry.w - objectCenter.x + radius;
									const float top = objectCenter.y - otherCenter.x + otherCollision->boundry.y + radius;
									const float bottom = otherCenter.x + otherCollision->boundry.h - objectCenter.y + radius;

									// Wektro separacji w tej formie to opdowiednio wartości: left, right, top, bottom.
									Vector::Vector2<float> separation;
									left < right ? separation.x = -left : separation.x = right;
									top < bottom ? separation.y = -top : separation.y = bottom;
									abs(separation.x) < abs(separation.y) ? separation.y = 0 : separation.x = 0;
									//DEBUG Log::Info("1. Separation: %f, %f", separation.x, separation.y);

									auto recalculatedPosition = Vector::Subtract(
										object.transform.position, {
											separation.x,
											separation.y
										}
									);

									//
									//DEBUG sceneGraph.gizmoLines.push_back({ object.transform.position, recalculatedPosition, { 255, 0, 0, 255 } });
									//
									auto otherRecalculatedPosition = Vector::Addition(
										other.transform.position, {
											separation.x,
											separation.y
										}
									);
									//
									//// Check with boundry.
									proposedPosition.x = Math::Clamp(recalculatedPosition.x, sceneGraph.sceneBoundry.x + radius, sceneGraph.sceneBoundry.w - radius);
									proposedPosition.y = Math::Clamp(recalculatedPosition.y, sceneGraph.sceneBoundry.y + radius, sceneGraph.sceneBoundry.h - radius);
									otherProposedPosition.x = Math::Clamp(otherRecalculatedPosition.x, sceneGraph.sceneBoundry.x + otherExtent.x / 2, sceneGraph.sceneBoundry.w - otherExtent.y / 2);
									otherProposedPosition.y = Math::Clamp(otherRecalculatedPosition.y, sceneGraph.sceneBoundry.y + otherExtent.y / 2, sceneGraph.sceneBoundry.h - otherExtent.y / 2);
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
										object.transform.position, {
											separation.x, // *(float)(radius - lengthBetween),
											separation.y  //* (float)(radius - lengthBetween)
										}
									);

									//DEBUG Log::Info("1. Separation: %f, %f", recalculatedPosition.x, recalculatedPosition.y);
									
									const auto otherRecalculatedPosition = Vector::Subtract(
										other.transform.position, {
											separation.x, // * (float)(radius - lengthBetween),
											separation.y  //* (float)(radius - lengthBetween)
										}
									);

									// Check with boundry.
									proposedPosition.x = Math::Clamp(recalculatedPosition.x, sceneGraph.sceneBoundry.x + radius, sceneGraph.sceneBoundry.w - radius);
									proposedPosition.y = Math::Clamp(recalculatedPosition.y, sceneGraph.sceneBoundry.y + radius, sceneGraph.sceneBoundry.h - radius);
									otherProposedPosition.x = Math::Clamp(otherRecalculatedPosition.x, sceneGraph.sceneBoundry.x + otherExtent.x / 2, sceneGraph.sceneBoundry.w - otherExtent.y / 2);
									otherProposedPosition.y = Math::Clamp(otherRecalculatedPosition.y, sceneGraph.sceneBoundry.y + otherExtent.y / 2, sceneGraph.sceneBoundry.h - otherExtent.y / 2);
								}
							}

						}
					}
				}

			}

			/* Enemerate through Squares */
			for (size current = 0; current < sceneGraph.squareObjectsCount; current++) {

				auto& object = sceneGraph.squareObjects[current];
				auto& proposedPosition = calculatedSquarePositions[current];

				const auto& collision = (Collision::SquareBody*)object.collision.type;
				const auto& type = (Surface::Square*)(object.surface.type);
				const auto& extent = type->extent;

				/* Enumerate through Circles [ Here we don't have to look for same ID ] */
				for (size i = 0; i < sceneGraph.circleObjectsCount; i++) {

					auto& other = sceneGraph.circleObjects[i];
					auto& otherProposedPosition = calculatedCirclePositions[i];

					const auto& otherCollision = (Collision::CircleBody*)other.collision.type;
					const auto& otherType = (Surface::Circle*)(other.surface.type);
					const auto& otherRadius = otherType->radius;

					{ // 1 Square - 1 Circle CHECK
					
					}
				}
			}

		}

	}

}