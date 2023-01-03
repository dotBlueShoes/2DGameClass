#pragma once
#include "../Framework.hpp"

namespace Collision {

	const bool isCollisionOn(true);
	bool isSeperationOn(true);
	bool isReflectionOn(true);

	/* Those should not be actual collision representations 
	 *  Instead they should represent factor of object's physical size.
	*/

	struct CircleBody {
		float radius;
	};

	struct SquareBody {
		Rectangle boundry;
	};

	struct Body {
		any type;
	};

}