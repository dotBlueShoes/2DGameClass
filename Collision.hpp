#pragma once
#include "Framework.hpp"

namespace Collision {

	const bool isCollisionOn(true);
	bool isSeperationOn(true);
	bool isReflectionOn(true);

	struct CircleCollision {
		float radius;
	};

	struct SquareCollision {
		Rectangle boundry;
	};

}