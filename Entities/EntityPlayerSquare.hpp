#pragma once
#include "../Framework.hpp"
#include "../Entity.hpp"
#include "../Components/Transform.hpp"
#include "../Components/Collision.hpp"
#include "../Components/Movable.hpp"
#include "../Components/Surface.hpp"

namespace Entity {

	struct PlayerSquare {
		Transform::Transform transform;
		Surface::Square surface;
		Collision::SquareCollision collision;
		Moveable::MoveData moveData;
	};

}
