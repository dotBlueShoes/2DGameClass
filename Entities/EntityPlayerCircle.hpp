#pragma once
#include "../Framework.hpp"
#include "../Entity.hpp"
#include "../Components/Transform.hpp"
#include "../Components/Collision.hpp"
#include "../Components/RigidBody.hpp"

namespace Entity {

	struct PlayerCircle {
		Transform::Transform transform;
		Surface::Circle surface;
		Collision::Circle collision;
		RigidBody::RigidBody rigidBody;

		constexpr inline static const size GetComponentsCount() { return 4; }

		//template <size index>
		constexpr inline static const size GetComponentOffset(const size& index) {
			assert(index >= GetComponentsCount());

			const size sizes[] { 
				sizeof transform, sizeof surface, 
				sizeof collision, sizeof rigidBody 
			};

			size result (0);

			for (size i = 0; i < index; ++i) {
				result += sizes[i];
			}

			return result;
		}
	};

}