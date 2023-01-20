#pragma once
#include "../Framework.hpp"
#include "../Log.hpp"
#include "../Math/Math.hpp"

namespace Jumping {

	const float jumpDistance = 96 + 64; // in tilesize - worldsize
	const float jumpHeight = 64; // in tilesize - worldsize
	const float jumpTime = 0.5; // sec
	const float groundDelay = 1; // sec
	const float jumpForce = 4;

	// Following the excercise.
	//  We're not really making it realistic instead we want a precise control
	//  of our jumping abillity therefore we need to elasticly change gravity.
	getter GetJumpGravity() {
		return (2 * jumpHeight) / (jumpTime * jumpTime);
	}

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
		float groundDelay;
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

	OnJumping onJump = Default;

	void Default(JumpingProperties& properties) {

		// Only when we're not jumping we can move. therefore...
		if (*properties.moveRightKey) (*properties.position).x += *properties.moveAmount;
		if (*properties.moveLeftKey) (*properties.position).x -= *properties.moveAmount;

		(*properties.position).y += (*properties.velocity).y;
	}

	void ReadyToJump(JumpingProperties& properties) {

		//if (properties.groundDelay < groundDelay) { // TO MAKE IT IMPOSSIBLE TO JUMP MID_AIR
			if (*properties.jumpKey) {

				//DEBUG Log::Info("here");

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
		// Y-AXIS
		(*properties.position).y =
			(0.5 * GetJumpGravity() * (*properties.timeAcceleration) * (*properties.timeAcceleration)) +
			(GetJumpYForce() * (*properties.timeAcceleration)) + properties.preJumpPosition.y;
	}

	void Jump(JumpingProperties& properties) {
		// If i would be expecting another jump i would place an if statement here
		// eg double jump. However there should be a input time delay logic as of this.

		// X-AXIS
		(*properties.position).x = 
			(GetJumpXForce() * properties.jumpDirection * (*properties.timeAcceleration)) + 
			properties.preJumpPosition.x;

		// Y-AXIS
		(*properties.position).y = 
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