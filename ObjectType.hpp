#pragma once
#include "Vector.hpp"

namespace ObjectType {

	struct Square {
		Vector::Vector2<float> size;
	};

	struct Circle {
		float radius;
	};

	struct ObjectType {
		any representation;
	};
	
}