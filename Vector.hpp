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

	Vector2<float> Addition(const Vector2<float>& first, const Vector2<float>& other) {
		return { first.x + other.x, first.y + other.y };
	}

	Vector2<float> Subtract(const Vector2<float>& first, const Vector2<float>& other) {
		return { first.x - other.x, first.y - other.y };
	}

	Vector2<float> MultiplyByScalar(const Vector2<float>& vector, const float& scalar) {
		return { vector.x * scalar, vector.y * scalar };
	}

	double DotProduct(const Vector2<float>& first, const Vector2<float>& other) {
		return (first.x * other.x) + (first.y * other.y);
	}

	double LengthBetween(const Vector2<float>& origin, const Vector2<float>& destin) {
		return sqrt(pow(destin.x - origin.x, 2) + pow(destin.y - origin.y, 2));
	}

}