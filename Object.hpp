#pragma once
#include "Framework.hpp"
#include "Transform.hpp"
#include "Movable.hpp"
#include "Color.hpp"
#include "Collision.hpp"
#include "ObjectType.hpp"

namespace Object {	

	using DrawCallback = void (*)(const Renderer&, const Vector::Vector2<float>&, void*, const Color::Color&);
	using CalculateMoveCallback = const Vector::Vector2<float> (*)(const Transform::Transform& transform, const Moveable::Moveable& moveable, const float& deltaTime);

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
		ObjectType::ObjectType type;
		Color::Color color;
		DrawCallback draw;
		Moveable::Moveable moveable;
		CalculateMoveCallback calculateMove;
		Collision::SquareCollision collision;
	};

	//block Draw(
	//	const Object& object, 
	//	const Renderer& renderer, 
	//	const float& radius
	//) {
	//	object.draw(renderer, object.transform.position, radius, object.color);
	//}

	

	//block UpdatePosition(Object& object, Moveable::Moveable& moveable, const float& deltaTime) {
	//	object.transform.position.x += moveable.velocity.x * deltaTime;
	//	object.transform.position.y += moveable.velocity.y * deltaTime;
	//}

}
