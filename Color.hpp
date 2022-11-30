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
	const Color purple { 52, 17, 247, 255 };

	const Color pink { 222, 16, 227, 255 };
	const Color lightBlue { 57, 133, 247, 255 };
	const Color cyan { 84, 241, 247, 255 };
	const Color lightGreen { 49, 247, 95, 255 };

	const Color darkBlue { 29, 36, 128, 255 };
	const Color darkGreen { 15, 41, 22, 255 };
	const Color brown { 52, 36, 14, 255 };
	const Color orange { 198, 64, 25, 255 };

	const Color magenta { 199, 12, 100, 255 };
	const Color white { 255, 255, 255, 255 };
	const Color black { 0, 0, 0, 255 };
	const Color lightGray { 128, 128, 128, 255 };
	const Color gray { 64, 64, 64, 255 };

}