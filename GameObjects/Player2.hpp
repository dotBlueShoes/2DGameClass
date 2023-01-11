#pragma once
#include "../Framework.hpp"
#include "../Math/Math.hpp"
#include "../Log.hpp"

namespace GameObjects::Player2 {

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

			if (keyboard[SDL_SCANCODE_W]) temp.y -= stepAmount;
			if (keyboard[SDL_SCANCODE_D]) temp.x += stepAmount;
			if (keyboard[SDL_SCANCODE_S]) temp.y += stepAmount;
			if (keyboard[SDL_SCANCODE_A]) temp.x -= stepAmount;

			return temp;
		}

		block Render(const Renderer& renderer, const Camera::Camera& camera, Object::Object& object) {
			const auto& type = (Surface::Square*)(object.surface.type);
			auto& extent = type->extent;

			const Vector::Vector2<float> renderPosition {
				object.transform.position.x - camera.position.x,
				object.transform.position.y - camera.position.y
			};

			object.draw(renderer, camera, renderPosition, &extent, object.color);
		}

	}
	
}