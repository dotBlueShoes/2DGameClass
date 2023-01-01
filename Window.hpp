#pragma once
#include "Framework.hpp"
#include "Math/Math.hpp"

namespace Window {

	struct WindowStruct {
		Vector::Vector2<uint32> viewport;
		size titleLength;
		character* title;
		Color::Color backgroundColor;
	};

}