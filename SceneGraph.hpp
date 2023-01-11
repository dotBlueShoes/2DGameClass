#pragma once
#include "Framework.hpp"
#include "Math/Math.hpp"
#include "Object/Object.hpp"
#include "GameObjects/MazeMap.hpp"
#include "Trigger.hpp"
#include "Camera.hpp"

namespace SceneGraph {

	namespace Gizmo {
		struct Line {
			Vector::Vector2<float> originPosition, destinPosition;
			Color::Color color;
		};
	}

	struct SceneGraph {
		Color::Color* backgroundColor;
		Camera::Camera mainCamera;
		size circleObjectsCount;
		Object::Object* circleObjects;
		size squareObjectsCount;
		Object::Object* squareObjects;
		Rectangle sceneBoundry;
		GameObjects::MazeMap::Map map;
		size staticCollisionsCount;
		Rectangle* staticCollisions;
		size triggersCount;
		Trigger::Trigger* triggers;
		vector<Gizmo::Line> gizmoLines;
	};

	block Restart(SceneGraph& sceneGraph) {
		//sceneGraph.mainCamera.position = { 0, 0 };
	}

}