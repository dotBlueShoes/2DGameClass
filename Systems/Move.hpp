#pragma once
#include "../Framework.hpp"
#include "../Entity.hpp"
#include "../Math/Math.hpp"

#include "../Components/Transform.hpp"
#include "../Components/RigidBody.hpp"

namespace Move {

	// constexpr const Vector::Vector2<float> CalculateMove(
	// 	const Transform::Transform& transform, 
	// 	const Moveable::MoveData& moveData,
	// 	const float& deltaTime
	// ) {
	// 	return { transform.position.x + moveData.velocity.x * deltaTime,
	// 		transform.position.y + moveData.velocity.y * deltaTime };
	// }

	//template <class ... Ts>
	void CalculateMove (
		Transform::Transform transform,
		RigidBody::RigidBody rigidBody
	) {
		std::cout << "hello" << std::endl;
	}

	//template <class T>
	//getter CalculateMove (
	//	Entity::System& system,
	//	const float& deltaTime
	//) {
	//	array<Vector::Vector2<float>, 10> output { 0 };
	//
	//	for (size i = 0; i < system.rangesLength; i++) {
	//		for (size j = 0; j < system.ranges[i]; j++) {
	//			auto& entity = /*(T)*/system.entities[j];
	//			
	//			//entity.transform.psoition.x + entity.moveData.velocity.x * deltaTime,
	//			//	entity.transfrom.position.y + entity.moveData.velocity.x * deltaTime;
	//		}
	//	}
	//
	//	// If we want to opperate on more then one buffor.
	//	//  TODO: Placing it here or can i actually call the system again with different params?
	//
	//	// 100 - BufforLength
	//	// 100
	//
	//	return output;
	//}

}