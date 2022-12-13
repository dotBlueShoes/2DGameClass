#pragma once
#include "../Framework.hpp"
#include "../Entity.hpp"
#include "../Components/Transform.hpp"
#include "../Components/Collision.hpp"
#include "../Components/Movable.hpp"

namespace Entity {

	struct PlayerCircle {
		Transform::Transform transform;
		Surface::Circle surface;
		Collision::CircleCollision collision;
		Moveable::MoveData moveData;
	};

}