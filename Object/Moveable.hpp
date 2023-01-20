#pragma once
#include "../Framework.hpp"
#include "../Log.hpp"
#include "Transform.hpp"

#include "Jump.hpp"

namespace Moveable {

	struct Rigidbody {
		Vector::Vector2<float> velocity;
		Jumping::OnHitJumping extra = nullptr;
		Jumping::OnHitJumping extra1 = nullptr;

		float personalGravity = Math::Constants::g<float>;
		float timeAcceleration = 0.0f; // 
		
	};

	block Accelerate(Rigidbody& rigidbody, const float& deltaTime) {
		rigidbody.timeAcceleration += deltaTime;
	}

	block CollisionHit(Rigidbody& rigidbody) {
		rigidbody.timeAcceleration = 0.0f;
		auto callback = (Jumping::OnHitJumping)(rigidbody.extra);
		callback();
	}

	block CollisionGroundHit(Rigidbody& rigidbody) {
		auto callback = (Jumping::OnHitJumping)(rigidbody.extra1);
		callback();
	}

	float GetGravityInfluence(const Rigidbody& rigidoby) {
		return (rigidoby.personalGravity * rigidoby.timeAcceleration); // +velocity.y;
	}

	Vector::Vector2<float> GetRandomAngleForce(const float& force) {
		const float angle = (float)(rand() * 3.14159 / 180);
		const Vector::Vector2<float> temp = { (float)cos(angle) * force, (float)sin(angle) * force };
		DEBUG Log::Info("Move Vector: %f, %f", temp.x, temp.y);
		return temp;
	}

	const getter CalculateMove(const Transform::Transform& transform, const Rigidbody& rigidbody, const float& deltaTime) {
		return Vector::Vector2<float> { transform.position.x + rigidbody.velocity.x * deltaTime,
			transform.position.y + rigidbody.velocity.y * deltaTime };
	}

}