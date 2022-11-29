#pragma once
#include "Framework.hpp"
#include "Transform.hpp"
#include "Movable.hpp"
#include "Color.hpp"
#include "Collision.hpp"

namespace Object {	

	using DrawCallback = void (*)(const Renderer&, const Vector::Vector2<float>&, const float&, const Color::Color&);
	using CalculateMoveCallback = const Vector::Vector2<float> (*)(const Transform::Transform& transform, const Moveable::Moveable& moveable, const float& deltaTime);

	struct Object {
		Transform::Transform transform;
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
