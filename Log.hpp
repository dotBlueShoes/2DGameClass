#pragma once
#include "Framework.hpp"

namespace Log {

	const size warrningLength = 9, errorLength = 7, infoLength = 6;
	char* info, error, warning;

	template <size sharedBufforSize>
	block Initialize() {
		//info = (char*) malloc(sharedBufforSize * sizeof char); // uninitialized data. if i assign it with = i willchange pointer reference...
		//char* test = strdup("testingonly");
		//delete test;

		//warning = new char[sharedBufforSize] { "Warning: " "\0" };
		//error = new char[sharedBufforSize] { "Error: " "\0" };
		//info = new char[sharedBufforSize] { "Info: " "\0" };
	}

	block Info(const char* message) {

		
		info[infoLength];

		//SDL_Log("Info: " + message);
	}
}