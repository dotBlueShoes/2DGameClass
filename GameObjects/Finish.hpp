#pragma once
#include "../Framework.hpp"
#include "../Log.hpp"
#include "../SceneGraph.hpp"
#include "Player.hpp"

namespace Finish {

	block Trigger(GameObjects::Player::Player& player) {
		DEBUG Log::Info("Player scored: %d", ++player.score);
		SceneGraph::NextLevel();
	}

	block Render(const Renderer& renderer, const Camera::Camera& camera, const Vector::Vector2<float>& position) {
		const Vector::Vector2<float> extent { 64, 64 };
		const Vector::Vector2<float> renderPosition {
			position.x - camera.position.x,
			position.y - camera.position.y
		};

		Draw::Square(renderer, camera, renderPosition, extent, Color::gray);
	}

}
