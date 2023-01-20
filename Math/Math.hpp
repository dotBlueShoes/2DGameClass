#pragma once
#include "Constants.hpp"
#include "Vector.hpp"
#include "Color.hpp"

namespace Math {

	float Clamp(const float& value, const float& min, const float& max) {
		if (value < min) return min;
		if (value > max) return max;
		return value;
	}

	getter Sign(const int x) {
		return (x >> 31) | 1;
	}

}