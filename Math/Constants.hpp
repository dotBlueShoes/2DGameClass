#pragma once
#include "../Framework.hpp"

namespace Math::Constants {

	const float fepsilon = 1.19209e-07;
	const double depsilon = 2.22045e-16;
	const long double ldepsilon = 1.0842e-19;

	template <typename T>
	const T pi(3.14);

	template <typename T>
	const T g(9.81);
}
