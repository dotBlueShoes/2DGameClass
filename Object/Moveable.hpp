#pragma once
#include "../Framework.hpp"
#include "../Log.hpp"
#include "Transform.hpp"

namespace Moveable {

	struct Rigidbody {
		Vector::Vector2<float> velocity;
		//Vector::Vector2<float> direction;
	};

	Vector::Vector2<float> GetRandomAngleForce(const float& force) {
		const float angle = (float)(rand() * 3.14159 / 180);
		const Vector::Vector2<float> temp = { (float)cos(angle) * force, (float)sin(angle) * force };
		DEBUG Log::Info("Move Vector: %f, %f", temp.x, temp.y);
		return temp;
	}

	constexpr const Vector::Vector2<float> CalculateMove(const Transform::Transform& transform, const Rigidbody& rigidbody, const float& deltaTime) {
		return { transform.position.x + rigidbody.velocity.x * deltaTime,
			transform.position.y + rigidbody.velocity.y * deltaTime };
	}

}