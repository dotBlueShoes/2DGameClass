#pragma once
#include "Vector.hpp"

namespace ObjectType {

	enum class Type : uint64 {
		Square = 0,
		Circle = 1
	};

	struct Square {
		Vector::Vector2<float> size;
	};

	struct Circle {
		float radius;
	};

	struct ObjectType {
		Type type;
		void* representation;
	};
	
}