#pragma once
#include "../Framework.hpp"
#include "../Math/Math.hpp"

namespace Collision {

	// ! Should have identifier as a field.

	const bool isCollisionOn(true);
	bool isSeperationOn(true);
	bool isReflectionOn(true);

	struct Circle {
		float radius;
	};

	struct Square {
		Rectangle boundry;
	};

}