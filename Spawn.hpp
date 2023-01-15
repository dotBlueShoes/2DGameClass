#pragma once
#include "Framework.hpp"
#include "Math/Math.hpp"
#include "GameObjects/MazeMap.hpp"

namespace Spawn {

	[[nodiscard]] Vector::Vector2<float> GetRandomValidPosition(
		const GameObjects::MazeMap::Map& map,
		const size& collisionsCount,
		const Rectangle* collisions
	) {
		const Vector::Vector2<float> mapSize{ map.extent.x * map.textureAtlas.tileSize, map.extent.y * map.textureAtlas.tileSize };

		// This needs to be moved / worked on.
		std::random_device rd; // obtain a random number from hardware
		std::mt19937 gen(rd()); // seed the generator
		std::uniform_int_distribution<> distrbutionX(0 + 2 * 32, mapSize.x - (2 * 32)); // define the range
		std::uniform_int_distribution<> distrbutionY(0 + 2 * 32, mapSize.y - (2 * 32)); // define the range

		auto x = (float)distrbutionX(gen), y = (float)distrbutionY(gen);
		DEBUG Log::Info("map-size: %f, %f", mapSize.x, mapSize.y);
		DEBUG Log::Info("random: %f, %f", x, y);
		return { x,  y };
	}

}