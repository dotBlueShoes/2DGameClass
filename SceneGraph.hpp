#pragma once
#include "Framework.hpp"
#include "Math/Math.hpp"
#include "Object/Object.hpp"
#include "GameObjects/MazeMap.hpp"

namespace SceneGraph {

	namespace Gizmo {
		struct Line {
			Vector::Vector2<float> originPosition, destinPosition;
			Color::Color color;
		};
	}

	struct SceneGraph {
		Color::Color* backgroundColor;
		size circleObjectsCount;
		Object::Object* circleObjects;
		size squareObjectsCount;
		Object::Object* squareObjects;
		Rectangle sceneBoundry;
		GameObjects::MazeMap::Map map;
		//size gizmoLinesCount = 0;
		vector<Gizmo::Line> gizmoLines;
		
	};

}