#pragma once
#include "Framework.hpp"
#include "Math/Math.hpp"
#include "Object/Object.hpp"

namespace SceneGraph {

	struct SceneGraph {
		Color::Color* backgroundColor;
		size circleObjectsCount;
		Object::Object* circleObjects;
		size squareObjectsCount;
		Object::Object* squareObjects;
	};

}