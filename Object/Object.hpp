#pragma once
#include "../Framework.hpp"
#include "../Math/Math.hpp"
#include "../Camera.hpp"
#include "Surface.hpp"
#include "Transform.hpp"
#include "Moveable.hpp"
#include "CollisionBody.hpp"


namespace Object {	

	//namespace Callback {
	//	using Draw = void (*)(const Renderer&, const Vector::Vector2<float>&, void*, const Color::Color&);
	//	using CalculateMove = const Vector::Vector2<float>(*)(const Transform::Transform& transform, const Moveable::MoveData& moveData, const float& deltaTime);
	//}

	struct Object;

	namespace Callback {
		using Draw = void(*)(const Renderer&, const Camera::Camera& camera, const Vector::Vector2<float>&, void*, const Color::Color&);
		using CalculateMove = const Vector::Vector2<float>(*)(const Transform::Transform& transform, const Moveable::Rigidbody& rigidbody, const float& deltaTime);
		using Logic = Vector::Vector2<float>(*)(const float& deltaTime, Object& object, const Vector::Vector2<float>& mousePosition, const Uint32& mouseBitMask, const Uint8* const keyboard);
		using Render = void(*)(const Renderer& renderer, const Camera::Camera& camera, Object& object);
	}

	const uint64 typeRange = 100000;
	enum Type : uint64 {
		Square = 0,
		Circle = 0 + typeRange
	};

	constexpr bool IsType(const uint64& identifier, const uint64& type) {
		return identifier >= (Type)(type) && identifier < (Type)(type + typeRange);
	}

	constexpr bool IsType(const uint64& firstIdentifier, const uint64& secondIdentifier, const uint64& type) {
		return IsType(firstIdentifier, type) && IsType(secondIdentifier, type);
	}

	struct Object {
		uint64 identifier;
		Transform::Transform transform;
		Surface::Surface surface;
		Color::Color color;
		Callback::Draw draw;
		Moveable::Rigidbody rigidbody;
		Callback::CalculateMove calculateMove;
		Collision::Body collision;
		Callback::Logic logic;
		Callback::Render render;
	};

	namespace Nothing::Update {
		Vector::Vector2<float> Logic(
			const float& deltaTime,
			Object& object,
			const Vector::Vector2<float>& mousePosition,
			const Uint32& mouseBitMask,
			const Uint8* const keyboard
		) {
			return object.transform.position;
		}

		block RenderSquare(const Renderer& renderer, const Camera::Camera& camera, Object& object) {
			const auto& type = (Surface::Square*)(object.surface.type);
			auto& extent = type->extent;
			object.draw(renderer, camera, object.transform.position, &extent, object.color);
		}

		block RenderCircle(const Renderer& renderer, const Camera::Camera& camera, Object& object) {
			const auto& type = (Surface::Circle*)(object.surface.type);
			auto& extent = type->radius;
			object.draw(renderer, camera, object.transform.position, &extent, object.color);
		}
	}

}
