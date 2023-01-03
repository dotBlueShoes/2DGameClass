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
			auto& calculatedPosition = calculatedCirclePositions[current];
			const auto& type = (Surface::Circle*)(object.surface.type);
			const auto& radius = type->radius;

			/* If we're outside X boundry. */
			if (calculatedPosition.x < sceneGraph.sceneBoundry.x + radius || calculatedPosition.x > sceneGraph.sceneBoundry.w - radius) {
				object.rigidbody.velocity.x *= -1;
				object.calculateMove(object.transform, object.rigidbody, deltaTime);
			}

			/* If we're outside Y boundry. */
			if (calculatedPosition.y < sceneGraph.sceneBoundry.y + radius || calculatedPosition.y > sceneGraph.sceneBoundry.h - radius) {
				object.rigidbody.velocity.y *= -1;
				object.calculateMove(object.transform, object.rigidbody, deltaTime);
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
				object.rigidbody.velocity.x *= -1;
				object.calculateMove(object.transform, object.rigidbody, deltaTime);
				//Log::Info("Should Flip: X");
			}

			/* If we're outside Y boundry. */
			if (proposedPosition.y < sceneGraph.sceneBoundry.y + extent.y / 2 || proposedPosition.y > sceneGraph.sceneBoundry.h - extent.y / 2) {	
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
		block CheckCollisionCircle() {

		}

		block CkeckCollisionSquare() {

		}
	}

	namespace Square {
		block CkeckCollisionSquare() {

		}

		block CheckCollisionCircle() {

		}
	}

}