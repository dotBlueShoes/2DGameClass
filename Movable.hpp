#pragma once
#include "Transform.hpp"

namespace Moveable {

	struct Moveable {
		Vector::Vector2<float> velocity;
		Vector::Vector2<float> direction;
	};

	Vector::Vector2<float> GetRandomAngleForce(const float& force) {
		const float angle = (float)(rand() * 3.14159 / 180);
		return { (float)cos(angle) * force, (float)sin(angle) * force };
	}

	constexpr const Vector::Vector2<float> CalculateMove(const Transform::Transform& transform, const Moveable& moveable, const float& deltaTime) {
		return { transform.position.x + moveable.velocity.x * deltaTime,
			transform.position.y + moveable.velocity.y * deltaTime };
	}

}