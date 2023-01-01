#pragma once
#include "Framework.hpp"

namespace FunctionStack {

	using StackFunction = void (*)(any parameters, size parametersLength);

	template <size bufforLength>
	struct FunctionStack {
		StackFunction* buffor;
	};

	template <size bufforLength>
	getter Initialize() {
		FunctionStack<bufforLength> stack;
		stack.buffor = new size[bufforLength];
	}

	//block PlaceOnStack() {
	//
	//}

	template <size bufforLength>
	block Destroy(FunctionStack<bufforLength> stack) {
		delete[] stack.buffor;
	}

	block Execute() {

	}

	block Next() {

	}

}