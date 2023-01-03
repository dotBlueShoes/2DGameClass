#pragma once
#include "../Framework.hpp"
#include "../Math/Math.hpp"

namespace Surface {

	struct Square {
		Vector::Vector2<float> extent;
	};

	struct Circle {
		float radius;
	};

	struct Surface {
		any type;
	};

}