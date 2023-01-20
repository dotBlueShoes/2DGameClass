#pragma once
#include "../Framework.hpp"
#include "../Log.hpp"
#include "../Math/Math.hpp"

namespace Jumping {

	const float jumpForce = 4;

	struct JumpingProperties {
		const Uint8* jumpKey;
		const Uint8* moveLeftKey;
		const Uint8* moveRightKey;
		const float* moveAmount;
		Vector::Vector2<float>* position;
		Vector::Vector2<float>* velocity;
	} gProperties {};

	using OnJumping = void(*)(JumpingProperties&);

	void Default(JumpingProperties&);
	void Jump(JumpingProperties&);

	OnJumping onJump = Default;

	void Default(JumpingProperties& properties) {

		// Only when we're not jumping we can move. therefore...
		if (*properties.moveRightKey) (*properties.position).x += *properties.moveAmount;
		if (*properties.moveLeftKey) (*properties.position).x -= *properties.moveAmount;

		(*properties.position).y += (*properties.velocity).y;
	}

	void ReadyToJump(JumpingProperties& properties) {
		//DEBUG Log::Info("Not Jumping");

		// Only when we're not jumping we can move. therefore...
		if (*properties.moveRightKey) (*properties.position).x += *properties.moveAmount;
		if (*properties.moveLeftKey) (*properties.position).x -= *properties.moveAmount;

		if (*properties.jumpKey) {
			onJump = Jump;
			onJump(properties);
			return;
			//DEBUG Log::Info("VelocityY: %f", *(properties.velocityY));
		}

		(*properties.position).y += (*properties.velocity).y;
	}

	void Jump(JumpingProperties& properties) {
		//DEBUG Log::Info("Jumping");

		// If i would be expecting another jump i would place an if statement here
		// eg double jump. However there should be a input time delay logic as of this.

		(*properties.velocity).y -= jumpForce;
		DEBUG Log::Info("Velocity: %f, %f", (*properties.velocity).x, (*properties.velocity).y);

		(*properties.position).y += (*properties.velocity).y;
	}

	void StopJumping();

	using OnStopJumping = void(*)(void);

	void StopJumping() {
		//DEBUG Log::Info("Buttt");
		onJump = ReadyToJump;
	}

}