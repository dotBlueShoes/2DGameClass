#pragma once
#include "../Framework.hpp"
#include "../Entity.hpp"
#include "../Math.hpp"

#include "../Components/Transform.hpp"
#include "../Components/Movable.hpp"

namespace Move {

	// Ranges specify the entities in entity lists that have required components.
	//  because components can be only added at creation.
	//  therefore thier position in buffors in known.

	using Range = size;
	using Ranges = Range*;

	struct System {
		Entity::Entities entities;
		const Ranges ranges;
		const size rangesLength;
		const size offset;
	};

	// constexpr const Vector::Vector2<float> CalculateMove(
	// 	const Transform::Transform& transform, 
	// 	const Moveable::MoveData& moveData,
	// 	const float& deltaTime
	// ) {
	// 	return { transform.position.x + moveData.velocity.x * deltaTime,
	// 		transform.position.y + moveData.velocity.y * deltaTime };
	// }

	//template <class T>
	getter CalculateMove (
		System& system,
		const float& deltaTime
	) {
		array<Vector::Vector2<float>, 10> output { 0 };

		for (size i = 0; i < system.rangesLength; i++) {
			for (size j = 0; j < system.ranges[i]; j++) {
				auto& entity = /*(T)*/system.entities[j];
				
				//entity.transform.psoition.x + entity.moveData.velocity.x * deltaTime,
				//	entity.transfrom.position.y + entity.moveData.velocity.x * deltaTime;
			}
		}

		// If we want to opperate on more then one buffor.
		//  TODO: Placing it here or can i actually call the system again with different params?

		// 100 - BufforLength
		// 100

		return output;
	}

}