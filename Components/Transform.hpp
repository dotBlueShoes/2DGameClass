#pragma once
#include "../Framework.hpp"
#include "../Math/Math.hpp"

namespace Transform {

	constexpr size TransformID = 1;

	namespace Position {
		const Vector::Vector2<float> zero { 0, 0 };
		const Vector::Vector2<float> center { 920 / 2 , 360 / 2 };
	}

	namespace Rotation {
		const float zero ( 0 );
	}

	namespace Scale {
		const Vector::Vector2<float> one { 1, 1 };
	}

	struct Transform {
		Vector::Vector2<float> position;
		float rotation;
		Vector::Vector2<float> scale;
	};

	const Transform zero = { Position::zero, Rotation::zero, Scale::one,  };

}