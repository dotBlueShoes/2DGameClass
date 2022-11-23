#pragma once
#include "Framework.hpp"
#include "Vector.hpp"

namespace Camera {

	struct Camera {
		Vector::Vector2<float> position;
		Vector::Vector2<float> viewport;
	};

}