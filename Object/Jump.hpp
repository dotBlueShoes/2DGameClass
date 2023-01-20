#pragma once
#include "../Framework.hpp"
#include "../Log.hpp"

namespace Jumping {

	struct JumpingProperties {
		const Uint8* jumpKey;
		float* positionY;
		float* velocityY;
	} gProperties {};

	using OnJumping = void(*)(JumpingProperties&);

	void Default(JumpingProperties&);
	void Jump(JumpingProperties&);

	OnJumping onJump = Default;

	void Default(JumpingProperties& properties) {
		//DEBUG Log::Info("Not Jumping");

		if (*properties.jumpKey) {
			onJump = Jump;
			onJump(properties);
			return;
			//DEBUG Log::Info("VelocityY: %f", *(properties.velocityY));
		}

		*(properties.positionY) += *(properties.velocityY);
	}

	void Jump(JumpingProperties& properties) {
		DEBUG Log::Info("Jumping");

		*(properties.positionY) += *(properties.velocityY) - 4;
	}

	void StopJumping();

	using OnStopJumping = void(*)(void);

	void StopJumping() {
		DEBUG Log::Info("Buttt");
		onJump = Default;
	}

}