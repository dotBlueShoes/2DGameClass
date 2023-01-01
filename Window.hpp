#pragma once
#include "Framework.hpp"
#include "Vector.hpp"
#include "Color.hpp"

namespace Window {

	struct WindowStruct {
		Vector::Vector2<uint32> viewport;
		const size& titleLength;
		const char* title;
		Color::Color backgroundColor;
	};

}