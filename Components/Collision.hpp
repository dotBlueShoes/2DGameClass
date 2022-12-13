#pragma once
#include "../Framework.hpp"

namespace Collision {

	// ! Should have identifier as a field.

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