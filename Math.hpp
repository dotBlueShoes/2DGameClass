#pragma once
#include "Framework.hpp"
#include "Vector2.hpp"

namespace Math {

	inline constexpr float Lerp(float startValue, float endValue, float percentage) {
		return (startValue + ((endValue - startValue) * percentage));
	}

	template <class T = Sint32>
	inline constexpr Vector2<T> Lerp(Vector2<T>& startPoint, Vector2<T>& endPoint, float percentage) {
		return { startPoint.x + ((endPoint.x - startPoint.x) * percentage) , startPoint.y + ((endPoint.y - startPoint.y) * percentage) };
	}

	namespace EasingFunctions {
		inline constexpr float EaseIn(float value) { return value * value; }
		inline constexpr float Flip(float value) { return 1 - value; } // Not Working requires logic changes!
		inline constexpr float EaseOut(float value) { return Flip(EaseIn(Flip(value))); }
		inline constexpr float EaseInOut(float value) { return Lerp(EaseIn(value), EaseOut(value), value); }
		inline constexpr float Spike(float value) { // Not Working requires logic changes!
			if (value <= .5f) return EaseIn(value / .5f);
			else return EaseIn(Flip(value) / .5f);
		}
	};

	template <class T = Sint32>
	unsigned Absolute(T value) { return value < 0 ? 0 - unsigned(value) : unsigned(value); }

}