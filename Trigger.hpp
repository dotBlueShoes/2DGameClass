#pragma once
#include "Framework.hpp"
#include "SceneGraph.hpp"

namespace Trigger {

	namespace Callback {
		using Trigger = void(*)(
			//Camera::Camera mainCamera,
			//size circleObjectsCount,
			//Object::Object* circleObjects,
			//size squareObjectsCount,
			//Object::Object* squareObjects
		);
	}

	struct Trigger {
		Rectangle boundry;
		Callback::Trigger callback;
	};

}