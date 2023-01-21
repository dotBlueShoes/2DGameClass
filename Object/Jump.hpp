#pragma once
#include "../Framework.hpp"
#include "../Log.hpp"
#include "../Math/Math.hpp"

namespace Jumping {

	const float jumpDistance = 96 + 64; // in tilesize - worldsize
	const float jumpHeight = 64; // in tilesize - worldsize
	const float jumpTime = 0.25; // sec
	const float groundDelay = 1.5f; // sec
	const float jumpKeyDelay = 0.2f; // sec
	const float jumpForce = 4;

	const float increasetGravity = 1.05f;

	// Following the excercise.
	//  We're not really making it realistic instead we want a precise control
	//  of our jumping abillity therefore we need to elasticly change gravity.
	getter GetJumpGravity() {
		return (2 * jumpHeight) / (jumpTime * jumpTime);
	}

	//getter GetDoubleJumpGravity() {
	//	return (2.25 * jumpHeight) / (jumpTime * jumpTime);
	//}

	getter GetJumpYForce() {
		return (-2 * jumpHeight) / jumpTime;
	}

	getter GetJumpXForce() {
		return jumpDistance / 2 / jumpTime;
	}

	struct JumpingProperties {
		const Uint8* jumpKey;
		const Uint8* moveLeftKey;
		const Uint8* moveRightKey;
		const float* moveAmount;
		float groundDelay = 0;
		Vector::Vector2<float> preJumpPosition;
		Vector::Vector2<float>* position;
		Vector::Vector2<float>* velocity;
		float* timeAcceleration;
		float jumpDirection;
	} gProperties {};

	using OnJumping = void(*)(JumpingProperties&);

	void ReadyToJump(JumpingProperties&);
	void Default(JumpingProperties&);
	void Jump(JumpingProperties&);
	void JumpUp(JumpingProperties&);
	void DoubleJump(JumpingProperties&);
	void DoubleJumpUp(JumpingProperties&);
	void FasterFallingXY(JumpingProperties&);
	void FasterFallingY(JumpingProperties&);

	OnJumping onJump = Default;

	//void FallFasterXY(JumpingProperties& properties) {
	//	// I we're above halfway we're falling.
	//	if (*properties.timeAcceleration > jumpTime) {
	//		onJump = FasterFallingXY;
	//	}
	//}
	//
	//void FallFasterY(JumpingProperties& properties) {
	//	// I we're above halfway we're falling.
	//	if (*properties.timeAcceleration > jumpTime) {
	//		onJump = FasterFallingY;
	//	}
	//}

	void Default(JumpingProperties& properties) {
		// Only when we're not jumping we can move. therefore...
		if (*properties.moveRightKey) (*properties.position).x += *properties.moveAmount;
		if (*properties.moveLeftKey) (*properties.position).x -= *properties.moveAmount;

		(*properties.position).y += (*properties.velocity).y;
	}

	void ReadyToJump(JumpingProperties& properties) {

		//if (properties.groundDelay < groundDelay) { // TO MAKE IT IMPOSSIBLE TO JUMP MID_AIR
			if (*properties.jumpKey) {
				*properties.timeAcceleration = 0;
				properties.preJumpPosition.y = (*properties.position).y;
				properties.preJumpPosition.x = (*properties.position).x;

				if (*properties.moveRightKey) {			// JumpRight
					properties.jumpDirection = 1;
					onJump = Jump;
					onJump(properties);
					return;
				} else if (*properties.moveLeftKey) {	// JumpLeft
					properties.jumpDirection = -1;
					onJump = Jump;
					onJump(properties);
					return;
				} else {								// JumpUp
					onJump = JumpUp;
					onJump(properties);
					return;
				}
			}
		//} else {
		//	properties.groundDelay = 0;
		//	onJump = Default;
		//}

		// Only when we're not jumping we can move. therefore...
		else if (*properties.moveRightKey) (*properties.position).x += *properties.moveAmount;
		else if (*properties.moveLeftKey) (*properties.position).x -= *properties.moveAmount;

		(*properties.position).y += (*properties.velocity).y;
	}

	void JumpUp(JumpingProperties& properties) {
		// Double Jump Logic.
		if (*properties.jumpKey) {
			auto& delay = *properties.timeAcceleration;
			if (delay > jumpKeyDelay) {
				*properties.timeAcceleration = 0;
				properties.preJumpPosition.y = (*properties.position).y;
				properties.preJumpPosition.x = (*properties.position).x;
				onJump = DoubleJumpUp;
				onJump(properties);
				return;
			}
		}

		// Falling Faster implementation.
		if (*properties.timeAcceleration < jumpTime) {
			(*properties.position).y = // Y-AXIS
				(0.5f * GetJumpGravity() * (*properties.timeAcceleration) * (*properties.timeAcceleration)) +
				(GetJumpYForce() * (*properties.timeAcceleration)) + properties.preJumpPosition.y;
		} else {
			(*properties.position).y = // Y-AXIS
				(0.5f * increasetGravity * GetJumpGravity() * (*properties.timeAcceleration) * (*properties.timeAcceleration)) +
				(GetJumpYForce() * (*properties.timeAcceleration)) + properties.preJumpPosition.y;
		}
	}

	void DoubleJumpUp(JumpingProperties& properties) {
		// Falling Faster implementation.
		if (*properties.timeAcceleration < jumpTime) {
			(*properties.position).y = // Y-AXIS
				(0.5f * GetJumpGravity() * (*properties.timeAcceleration) * (*properties.timeAcceleration)) +
				(GetJumpYForce() * (*properties.timeAcceleration)) + properties.preJumpPosition.y;
		} else {
			(*properties.position).y = // Y-AXIS
				(0.5f * increasetGravity * GetJumpGravity() * (*properties.timeAcceleration) * (*properties.timeAcceleration)) +
				(GetJumpYForce() * (*properties.timeAcceleration)) + properties.preJumpPosition.y;
		}
	}

	void Jump(JumpingProperties& properties) {
		// Double Jump Logic.
		if (*properties.jumpKey) {
			auto& delay = *properties.timeAcceleration;
			if (delay > jumpKeyDelay) {
				*properties.timeAcceleration = 0;
				properties.preJumpPosition.y = (*properties.position).y;
				properties.preJumpPosition.x = (*properties.position).x;
				onJump = DoubleJump;
				onJump(properties);
				return;
			}
		}

		// Falling Faster implementation.
		if (*properties.timeAcceleration < jumpTime) {
			(*properties.position).x = // X-AXIS
				(GetJumpXForce() * properties.jumpDirection * (*properties.timeAcceleration)) +
				properties.preJumpPosition.x;
			(*properties.position).y = // Y-AXIS
				(0.5f * GetJumpGravity() * (*properties.timeAcceleration) * (*properties.timeAcceleration)) +
				(GetJumpYForce() * (*properties.timeAcceleration)) + properties.preJumpPosition.y;
		} else {
			(*properties.position).x = // X-AXIS
				(GetJumpXForce() * properties.jumpDirection * (*properties.timeAcceleration)) +
				properties.preJumpPosition.x;
			(*properties.position).y = // Y-AXIS
				(0.5f * increasetGravity * GetJumpGravity() * (*properties.timeAcceleration) * (*properties.timeAcceleration)) +
				(GetJumpYForce() * (*properties.timeAcceleration)) + properties.preJumpPosition.y;
		}
		
	}

	void DoubleJump(JumpingProperties& properties) {
		// Falling Faster implementation.
		if (*properties.timeAcceleration < jumpTime) {
			(*properties.position).x = // X-AXIS
				(GetJumpXForce() * properties.jumpDirection * (*properties.timeAcceleration)) +
				properties.preJumpPosition.x;
			(*properties.position).y = // Y-AXIS
				(0.5f * GetJumpGravity() * (*properties.timeAcceleration) * (*properties.timeAcceleration)) +
				(GetJumpYForce() * (*properties.timeAcceleration)) + properties.preJumpPosition.y;
		} else {
			(*properties.position).x = // X-AXIS
				(GetJumpXForce() * properties.jumpDirection * (*properties.timeAcceleration)) +
				properties.preJumpPosition.x;
			(*properties.position).y = // Y-AXIS
				(0.5f * increasetGravity * GetJumpGravity() * (*properties.timeAcceleration) * (*properties.timeAcceleration)) +
				(GetJumpYForce() * (*properties.timeAcceleration)) + properties.preJumpPosition.y;
		}
		
	}

	void FasterFallingXY(JumpingProperties& properties) {
		(*properties.position).x = // X-AXIS
			(GetJumpXForce() * properties.jumpDirection * (*properties.timeAcceleration)) +
			properties.preJumpPosition.x;
		(*properties.position).y = // Y-AXIS
			(0.5 * GetJumpGravity() * (*properties.timeAcceleration) * (*properties.timeAcceleration)) +
			(GetJumpYForce() * (*properties.timeAcceleration)) + properties.preJumpPosition.y;
	}

	void FasterFallingY(JumpingProperties& properties) {
		(*properties.position).y = // Y-AXIS
			(0.5 * GetJumpGravity() * (*properties.timeAcceleration) * (*properties.timeAcceleration)) +
			(GetJumpYForce() * (*properties.timeAcceleration)) + properties.preJumpPosition.y;
	}

	void GroundHit();
	void Hit();

	using OnHitJumping = void(*)(void);

	void Hit() {
		onJump = Default;
	}

	void GroundHit() {
		//DEBUG Log::Info("Buttt");
		//properties.groundDelay
		onJump = ReadyToJump;
	}

}