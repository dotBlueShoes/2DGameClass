#pragma once
#include "../Framework.hpp"
#include "../Math/Math.hpp"
#include "../Log.hpp"

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

			if (keyboard[SDL_SCANCODE_UP]) temp.y -= stepAmount;
			if (keyboard[SDL_SCANCODE_RIGHT]) temp.x += stepAmount;
			if (keyboard[SDL_SCANCODE_DOWN]) temp.y += stepAmount;
			if (keyboard[SDL_SCANCODE_LEFT]) temp.x -= stepAmount;

			return temp;
		}

		block Render(const Renderer& renderer, Object::Object& object /*, Camera::Camera& camera */) {
			const auto& type = (Surface::Circle*)(object.surface.type);
			auto& radius = type->radius;
			object.draw(renderer, object.transform.position, &radius, object.color);
		}

	}

}