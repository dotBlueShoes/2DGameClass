#pragma once
#include "Framework.hpp"
#include "Log.hpp"

#include <chrono>

// namespace Time {
// 
//     float elapsedTime = 0.0f;
//     float deltaTime = 0.0f;
//     float lastFrame = 0.0f;
// 
// }

namespace Time {

	using SystemClock = std::chrono::system_clock;
	using TimePoint = SystemClock::time_point;
	using ElapsedTime = std::chrono::duration<float>; // In seconds!!!

	TimePoint startTime, lastFrameTime, currentTime; // Storing tempTime globally so we don't recreate it each frame.
	ElapsedTime tempTime(0);

	void Start() {
		startTime = SystemClock::now();
		lastFrameTime = startTime;
		DEBUG Log::Info("Clock Start");
	}

	float GetElapsedTime() {
		currentTime = SystemClock::now();
		tempTime = (currentTime - lastFrameTime);
		lastFrameTime = SystemClock::now();
		return tempTime.count();
	}

};