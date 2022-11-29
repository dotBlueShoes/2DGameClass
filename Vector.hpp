#pragma once
#include "Framework.hpp"

namespace Vector {

	template <class T>
	struct Vector2 {
		T x, y;
	};

	template <class T>
	struct Vector3 {
		T x, y, z;
	};

	template <class T>
	struct Vector4 {
		T x, y, z;
	};

	double LengthBetween(const Vector2<float>& origin, const Vector2<float>& destin) {
		return sqrt(pow(destin.x - origin.x, 2) + pow(destin.y - origin.y, 2));
	}

}