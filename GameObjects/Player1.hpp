#pragma once
#include "../Framework.hpp"
#include "../Math/Math.hpp"
#include "../Log.hpp"

#include "../Object/Jump.hpp"

namespace GameObjects::Player1 {

	const float stepAmount = 4.0f;

	namespace Update {

		block JumpInputProcess(
			const float& deltaTime,
			Object::Object& object,
			const Vector::Vector2<float>& mousePosition,
			const Uint32& mouseBitMask,
			const Uint8* const keyboard
		) {
			const float step = 1.0f;
			if (keyboard[SDL_SCANCODE_Z]) {
				Jumping::jumpDistance -= step;
				DEBUG {
					Log::Info("Jump X: %f", Jumping::jumpDistance);
					Log::Info("Jump Y: %f", Jumping::jumpHeight);
					Log::Info("Gravity: %f", Jumping::GetJumpGravity());
					Log::Info("Force X: %f", Jumping::GetJumpXForce());
					Log::Info("Force Y: %f\n", Jumping::GetJumpYForce());
					Log::Info("");
				}
			} else if (keyboard[SDL_SCANCODE_X]) {
				Jumping::jumpDistance += step;
				DEBUG {
					Log::Info("Jump X: %f", Jumping::jumpDistance);
					Log::Info("Jump Y: %f", Jumping::jumpHeight);
					Log::Info("Gravity: %f", Jumping::GetJumpGravity());
					Log::Info("Force X: %f", Jumping::GetJumpXForce());
					Log::Info("Force Y: %f\n", Jumping::GetJumpYForce());
					Log::Info("");
				}
			} else if (keyboard[SDL_SCANCODE_C]) {
				Jumping::jumpHeight -= step;
				DEBUG {
					Log::Info("Jump X: %f", Jumping::jumpDistance);
					Log::Info("Jump Y: %f", Jumping::jumpHeight);
					Log::Info("Gravity: %f", Jumping::GetJumpGravity());
					Log::Info("Force X: %f", Jumping::GetJumpXForce());
					Log::Info("Force Y: %f", Jumping::GetJumpYForce());
					Log::Info("");
				}
			} else if (keyboard[SDL_SCANCODE_V]) {
				Jumping::jumpHeight += step;
				DEBUG {
					Log::Info("Jump X: %f", Jumping::jumpDistance);
					Log::Info("Jump Y: %f", Jumping::jumpHeight);
					Log::Info("Gravity: %f", Jumping::GetJumpGravity());
					Log::Info("Force X: %f", Jumping::GetJumpXForce());
					Log::Info("Force Y: %f\n", Jumping::GetJumpYForce());
					Log::Info("");
				}
			}
		}

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

			// We're programming collision model with gravity..
			//  If we look at unity we can tell that their collision logic is connected to gravity.
			//  What is happening there is that when we COLLIDE on y-axis we lose our y-velocity
			// - Velocity is something we constantly add to our position. Therefore position on y won't change anymore.

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