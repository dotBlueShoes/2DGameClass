#pragma once
#include "Vector.hpp"

namespace Surface {

	struct Square {
		Vector::Vector2<float> size;
	};

	struct Circle {
		float radius;
	};

	struct Surface {
		any type;
	};
	
}