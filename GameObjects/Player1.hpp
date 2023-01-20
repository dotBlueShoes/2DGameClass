#pragma once
#include "../Framework.hpp"
#include "../Math/Math.hpp"
#include "../Log.hpp"

#include "../Object/Jump.hpp"

namespace GameObjects::Player1 {

	namespace Update {

		Vector::Vector2<float> Logic(
			const float& deltaTime,
			Object::Object& object,
			const Vector::Vector2<float>& mousePosition,
			const Uint32& mouseBitMask,
			const Uint8* const keyboard
		) {

			const float stepAmount = 4.0f;
			Vector::Vector2<float> temp { object.transform.position.x, object.transform.position.y };

			if (keyboard[SDL_SCANCODE_RIGHT]) temp.x += stepAmount;
			if (keyboard[SDL_SCANCODE_LEFT]) temp.x -= stepAmount;

			// Acceleration - Przyœpieszenie
			// Velocity - Prêdkoœæ

			auto& velocity = object.rigidbody.velocity;
			velocity.y = Moveable::GetGravityInfluence(object.rigidbody);

			{
				using namespace Jumping;
				gProperties.jumpKey = &keyboard[SDL_SCANCODE_SPACE];
				gProperties.positionY = &temp.y;
				gProperties.velocityY = &velocity.y;
				onJump(gProperties);
			}

			//DEBUG Log::Info("Velocity: %f,  %f", velocity.x, velocity.y);
			//DEBUG Log::Info("Position: %f,  %f", temp.x, temp.y);

			// We're programming collision model with gravity..
			//  If we look at unity we can tell that their collision logic is connected to gravity.
			//  What is happening there is that when we COLLIDE on y-axis we lose our y-velocity
			// - Velocity is something we constantly add to our position. Therefore position on y won't change anymore.

			//const float currentTime = 1;
			//const float startingVelocity = 1;
			//const float startingPosition = temp.y;
			//temp.y = 336.3371f;
			//temp.y = 333.0f;
			//temp.y = ( 1.0f / 2.0f * Math::Constants::g<float> * currentTime * currentTime ) + ( startingVelocity * currentTime ) + temp.y;
			//DEBUG Log::Info("newY: %f", temp.y);

			return temp;
		}

		block Render(const Renderer& renderer, const Camera::Camera& camera, Object::Object& object) {
			const auto& type = (Surface::Circle*)(object.surface.type);
			auto& radius = type->radius;

			const Vector::Vector2<float> renderPosition {
				object.transform.position.x - camera.position.x,
				object.transform.position.y - camera.position.y
			};

			object.draw(renderer, camera, renderPosition, &radius, object.color);
		}

	}

}