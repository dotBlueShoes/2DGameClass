#pragma once
#include "Framework.hpp"

// TODO: Could optimize the structure to possibly don't store the alpha as a template variant.
struct Color {
	Uint8 red = 0, green = 0, blue = 0, alpha = 255;
};