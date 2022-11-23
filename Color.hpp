#pragma once
#include "Framework.hpp"

namespace Color {

	struct Color {
		uint8 r;
		uint8 g;
		uint8 b;
		uint8 a = 255;
	};

	const Color red   { 255, 0, 0, 255 };
	const Color green { 0, 255, 0, 255 };
	const Color blue  { 0, 0, 255, 255 };

}