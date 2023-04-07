#pragma once
#include "../Framework.hpp"
#include "../Entity.hpp"
#include "../Components/Transform.hpp"
#include "../Components/Collision.hpp"
#include "../Components/RigidBody.hpp"

namespace Entity {

	struct PlayerCircle { /* 36 bytes */
		Transform::Transform transform; // 5 * 4 = 20
		Surface::Circle surface; // 1 * 4 = 4
		Collision::Circle collision; // 1 * 4 = 4
		RigidBody::RigidBody rigidBody; // 2 * 4 = 8

		constexpr inline size GetComponentsCount() { return 4; }

		template <size index>
		constexpr inline size GetComponentOffset() {

			// Byte Sizes
			const size transform = 20;
			const size surface = 4;
			const size collision = 4;
			const size rigidBody = 8;

			switch constexpr (index) {
				case 0: return 0;
				case 1: return transform;
				case 2: return transform + surface;
				case 3: return transform + surface + collision;
				case default: assert(true);
			}

		}
	};

}