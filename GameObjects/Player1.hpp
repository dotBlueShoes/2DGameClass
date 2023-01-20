#pragma once
#include "../Framework.hpp"
#include "../Math/Math.hpp"
#include "../Log.hpp"

#include "../Object/Jump.hpp"

namespace GameObjects::Player1 {

	const float stepAmount = 4.0f;

	namespace Update {

		Vector::Vector2<float> Logic(
			const float& deltaTime,
			Object::Object& object,
			const Vector::Vector2<float>& mousePosition,
			const Uint32& mouseBitMask,
			const Uint8* const keyboard
		) {
			Vector::Vector2<float> temp { object.transform.position.x, object.transform.position.y };

			auto& velocity = object.rigidbody.velocity;
			velocity.y = Moveable::GetGravityInfluence(object.rigidbody);

			{
				using namespace Jumping;
				gProperties.jumpKey = &keyboard[SDL_SCANCODE_SPACE];		// Should be assigned once !
				gProperties.moveRightKey = &keyboard[SDL_SCANCODE_RIGHT];	// Should be assigned once !
				gProperties.moveLeftKey = &keyboard[SDL_SCANCODE_LEFT];		// Should be assigned once !
				gProperties.moveAmount = &stepAmount;						// Should be assigned once ! I guess depends ?
				gProperties.position = &temp;
				gProperties.velocity = &velocity;
				gProperties.timeAcceleration = &object.rigidbody.timeAcceleration;
				onJump(gProperties);
			}

			//DEBUG Log::Info("Velocity: %f,  %f", velocity.x, velocity.y);
			//DEBUG Log::Info("Position: %f,  %f", temp.x, temp.y);

			// We're programming collision model with gravity..
			//  If we look at unity we can tell that their collision logic is connected to gravity.
			//  What is happening there is that when we COLLIDE on y-axis we lose our y-velocity
			// - Velocity is something we constantly add to our position. Therefore position on y won't change anymore.

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