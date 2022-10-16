#pragma once
#include "Framework.hpp"
#include "Vector2.hpp"

namespace Math {

	template <class T = Sint32>
	Vector2<T> Lerp( Vector2<T>& startPoint, Vector2<T>& endPoint, float percentage) {
		return { startPoint.x + (endPoint.x - startPoint.x) * percentage , startPoint.y + (endPoint.y - startPoint.y) * percentage };
	}

	template <class T = Sint32>
	unsigned Absolute(T value) { return value < 0 ? 0 - unsigned(value) : unsigned(value); }

}