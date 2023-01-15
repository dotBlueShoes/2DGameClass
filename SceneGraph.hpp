#pragma once
#include "Framework.hpp"
#include "Math/Math.hpp"
#include "Object/Object.hpp"
#include "GameObjects/MazeMap.hpp"
#include "Trigger.hpp"
#include "Camera.hpp"
#include "GameObjects/Player.hpp"
#include "Spawn.hpp"

namespace SceneGraph {

	namespace Gizmo {
		struct Line {
			Vector::Vector2<float> originPosition, destinPosition;
			Color::Color color;
		};
	}

	struct SceneGraph {
		Color::Color* backgroundColor;
		Camera::Camera mainCamera;
		size circleObjectsCount;
		Object::Object* circleObjects;
		size squareObjectsCount;
		Object::Object* squareObjects;
		Rectangle sceneBoundry;
		GameObjects::MazeMap::Map map;
		size staticCollisionsCount;
		Rectangle* staticCollisions;
		size triggersCount;
		Trigger::Trigger* triggers;
		vector<Gizmo::Line> gizmoLines;
	};


	GameObjects::Player::Player player1{ 0 }, player2{ 0 };
	size currentSceneIndex = 0;
	size scenesCount = 3;
	SceneGraph* currentScene;
	SceneGraph* scenes;

	block Restart() {
		DEBUG Log::Info("Restart!");

		for (size i = 0; i < currentScene->circleObjectsCount; i++) {
			currentScene->circleObjects->transform.position = Spawn::GetRandomValidPosition(
				currentScene->map, currentScene->staticCollisionsCount, currentScene->staticCollisions
			);
		}

		for (size i = 0; i < currentScene->squareObjectsCount; i++) {
			currentScene->squareObjects->transform.position = { 300, 300 };
		}

	}

	block NextLevel() {
		DEBUG Log::Info("NextLevel!");

		++currentSceneIndex;
		if (currentSceneIndex == scenesCount) {
			DEBUG Log::Info("Player1 scored: %d, Player2 scored: %d", player1.score, player2.score);
			currentSceneIndex = 0;
		}
		currentScene = &scenes[currentSceneIndex];
		Restart();
	}

}