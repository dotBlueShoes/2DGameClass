#pragma once
#include "../Framework.hpp"
#include "../Math/Math.hpp"
#include "Transform.hpp"
#include "../Log.hpp"

namespace RigidBody {

	const Vector::Vector2<float> zero { 0, 0 };

	struct RigidBody {
		Vector::Vector2<float> velocity;
	};

	Vector::Vector2<float> GetRandomAngleForce(const float& force) {
		const float angle = (float)(rand() * 3.14159 / 180);
		const Vector::Vector2<float> temp = { (float)cos(angle) * force, (float)sin(angle) * force };
		DEBUG Log::Info("Move Vector: %f, %f", temp.x, temp.y);
		return temp;
	}

	constexpr const Vector::Vector2<float> CalculateMove(
		const Transform::Transform& transform,
		const RigidBody& rigidBody,
		const float& deltaTime
	) {
		return { transform.position.x + rigidBody.velocity.x * deltaTime,
			transform.position.y + rigidBody.velocity.y * deltaTime };
	}

}