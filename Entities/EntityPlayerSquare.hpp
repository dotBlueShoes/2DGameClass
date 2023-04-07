#pragma once
#include "../Framework.hpp"
#include "../Entity.hpp"
#include "../Components/Transform.hpp"
#include "../Components/Collision.hpp"
#include "../Components/RigidBody.hpp"
#include "../Components/Surface.hpp"

namespace Entity {

	struct PlayerSquare {
		Transform::Transform transform;
		Surface::Square surface;
		Collision::Square collision;
		RigidBody::RigidBody rigidBody;
	};

}
