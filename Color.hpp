#pragma once
#include "Framework.hpp"

// TODO: Could optimize the structure to possibly don't store the alpha as a template variant.
struct Color {
	const Uint8 red, green, blue, alpha;
	Color(Uint8 newRed, Uint8 newGreen, Uint8 newBlue, Uint8 newAlpha = 255) :
		red(newRed), green(newGreen), blue(newBlue), alpha(newAlpha) {}
};