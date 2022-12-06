#pragma once

namespace Collision {

	struct CircleCollision {
		float radius;
	};

	struct SquareCollision {
		Rectangle boundry;
		uint64 id;
	};

}