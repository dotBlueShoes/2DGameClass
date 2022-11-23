#pragma once
#include "Framework.hpp"
#include "Vector.hpp"
#include "Color.hpp"

namespace Window {

	struct WindowStruct {
		Vector::Vector2<uint32> viewport;
		const size& titleLength;
		char* title;
		Color::Color backgroundColor;
	};

}