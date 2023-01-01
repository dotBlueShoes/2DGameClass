#pragma once
#include "Framework.hpp"

#include <stdarg.h>

namespace Log {

	/*
	 * It's not a good implementation. I decided to not touch it anymore simply because
	 *  I was getting to much distracted by the use of const and cpp approach to them
	 *  telling the compiler something which would literally be a line of code in assembly
	 * 
	 * buffors, pointer / array declaration, const, compile-time code
	*/

	template<typename... Args>
	block Warning(const char* message, Args... args) {
		SDL_LogWarn(0, message, args...);
	}

	template<typename... Args>
	block Error(const char* message, Args... args) {
		SDL_LogError(0, message, args...);
	}

	template<typename... Args>
	block Info(const char* message, Args... args) {
		SDL_LogInfo(0, message, args...);
	}


	//block Warning(const char* message, const char* rest...) {
	//	SDL_LogWarn(0, message);
	//}
	//
	//block Error(const char* message, const char* rest...) {
	//	SDL_LogError(0, message);
	//}
	//
	//block Info(const char* message, const char* rest...) {
	//	SDL_LogInfo(0, message);
	//}

}