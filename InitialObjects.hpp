#pragma once
#include "Framework.hpp"
#include "SceneGraph.hpp"
#include "Draw.hpp"
#include "Spawn.hpp"

#include "GameObjects/Player1.hpp"
#include "GameObjects/Player2.hpp"
#include "GameObjects/MazeMap.hpp"
#include "GameObjects/Finish.hpp"
#include "GameObjects/Player.hpp"

const float radius(15.0f);
Surface::Circle circleSurface1 { 15.0f };
Collision::CircleBody collisionCircle { radius };

Surface::Square squareSurface1 { 30, 30 };
Collision::SquareBody collisionSquare { -15.0f, -15.0f, 15.0f, 15.0f };

[[nodiscard]] auto CreatePlayer1sObjects(
	const GameObjects::MazeMap::Map& map,
	const size& collisionsCount,
	const Rectangle* collisions
) {

	const Object::Object player1 {
		Object::Type::Circle + 0,
		{ Spawn::GetRandomValidPosition(map, collisionsCount, collisions) , Transform::Rotation::zero, Transform::Scale::one },
		{ &circleSurface1 },
		Color::blue,
		Draw::Circle,
		{ { 0, 0 }, Jumping::StopJumping },
		Moveable::CalculateMove,
		&collisionCircle,
		GameObjects::Player1::Update::Logic,
		GameObjects::Player1::Update::Render
	};

	return array<Object::Object, 1>{ player1 };

}

[[nodiscard]] auto CreatePlayer2sObjects(
	const GameObjects::MazeMap::Map& map,
	const size& collisionsCount,
	const Rectangle* collisions
) {

	const Object::Object player2 {
		Object::Type::Square + 0,
		{ Spawn::GetRandomValidPosition(map, collisionsCount, collisions), Transform::Rotation::zero, Transform::Scale::one },
		{ &squareSurface1 },
		Color::green,
		Draw::Square,
		{ { 0, 0 }, Jumping::StopJumping },
		Moveable::CalculateMove,
		&collisionSquare,
		GameObjects::Player2::Update::Logic,
		GameObjects::Player2::Update::Render
	};

	return array<Object::Object, 1>{ player2 };
}

[[nodiscard]] auto CreateCircleObjects() {

	const Object::Object circle1 {
		Object::Type::Circle + 0,
		{ { 300, 200 }, Transform::Rotation::zero, Transform::Scale::one },
		{ &circleSurface1 },
		Color::blue,
		Draw::Circle,
		{ Moveable::GetRandomAngleForce(80.0f) },
		Moveable::CalculateMove,
		&collisionCircle,
		Object::Nothing::Update::Logic,
		Object::Nothing::Update::RenderCircle
	};

	const Object::Object circle2 {
		Object::Type::Circle + 1,
		{ { 400, 200 }, Transform::Rotation::zero, Transform::Scale::one },
		{ &circleSurface1 },
		Color::purple,
		Draw::Circle,
		{ Moveable::GetRandomAngleForce(80.0f) },
		Moveable::CalculateMove,
		&collisionCircle,
		Object::Nothing::Update::Logic,
		Object::Nothing::Update::RenderCircle
	};

	const Object::Object circle3 {
		Object::Type::Circle + 2,
		{ { 500, 200 }, Transform::Rotation::zero, Transform::Scale::one },
		{ &circleSurface1 },
		Color::pink,
		Draw::Circle,
		{ Moveable::GetRandomAngleForce(80.0f) },
		Moveable::CalculateMove,
		&collisionCircle,
		Object::Nothing::Update::Logic,
		Object::Nothing::Update::RenderCircle
	};

	const Object::Object circle4 {
		Object::Type::Circle + 3,
		{ { 600, 200 }, Transform::Rotation::zero, Transform::Scale::one },
		{ &circleSurface1 },
		Color::lightBlue,
		Draw::Circle,
		{ Moveable::GetRandomAngleForce(80.0f) },
		Moveable::CalculateMove,
		&collisionCircle,
		Object::Nothing::Update::Logic,
		Object::Nothing::Update::RenderCircle
	};

	const Object::Object circle5 {
		Object::Type::Circle + 4,
		{ { 700, 200 }, Transform::Rotation::zero, Transform::Scale::one },
		{ &circleSurface1 },
		Color::cyan,
		Draw::Circle,
		{ Moveable::GetRandomAngleForce(80.0f) },
		Moveable::CalculateMove,
		&collisionCircle,
		Object::Nothing::Update::Logic,
		Object::Nothing::Update::RenderCircle
	};

	const Object::Object circle6 {
		Object::Type::Circle + 5,
		{ { 800, 200 }, Transform::Rotation::zero, Transform::Scale::one },
		{ &circleSurface1 },
		Color::lightGreen,
		Draw::Circle,
		{ Moveable::GetRandomAngleForce(80.0f) },
		Moveable::CalculateMove,
		&collisionCircle, 
		Object::Nothing::Update::Logic,
		Object::Nothing::Update::RenderCircle
	};

	const Object::Object circle7 {
		Object::Type::Circle + 6,
		{ { 100, 300 }, Transform::Rotation::zero, Transform::Scale::one },
		{ &circleSurface1 },
		Color::darkBlue,
		Draw::Circle,
		{ Moveable::GetRandomAngleForce(80.0f) },
		Moveable::CalculateMove,
		&collisionCircle, 
		Object::Nothing::Update::Logic,
		Object::Nothing::Update::RenderCircle
	};

	const Object::Object circle8 {
		Object::Type::Circle + 7,
		{ { 200, 300 }, Transform::Rotation::zero, Transform::Scale::one },
		{ &circleSurface1 },
		Color::darkGreen,
		Draw::Circle,
		{ Moveable::GetRandomAngleForce(80.0f) },
		Moveable::CalculateMove,
		&collisionCircle, 
		Object::Nothing::Update::Logic,
		Object::Nothing::Update::RenderCircle
	};

	const Object::Object circle9 {
		Object::Type::Circle + 8,
		{ { 300, 300 }, Transform::Rotation::zero, Transform::Scale::one },
		{ &circleSurface1 },
		Color::brown,
		Draw::Circle,
		{ Moveable::GetRandomAngleForce(80.0f) },
		Moveable::CalculateMove,
		&collisionCircle, 
		Object::Nothing::Update::Logic,
		Object::Nothing::Update::RenderCircle
	};

	const Object::Object circle10 {
		Object::Type::Circle + 9,
		{ { 400, 300 }, Transform::Rotation::zero, Transform::Scale::one },
		{ &circleSurface1 },
		Color::orange,
		Draw::Circle,
		{ Moveable::GetRandomAngleForce(80.0f) },
		Moveable::CalculateMove,
		&collisionCircle, 
		Object::Nothing::Update::Logic,
		Object::Nothing::Update::RenderCircle
	};

	const Object::Object circle11 {
		Object::Type::Circle + 10,
		{ { 500, 300 }, Transform::Rotation::zero, Transform::Scale::one },
		{ &circleSurface1 },
		Color::magenta,
		Draw::Circle,
		{ Moveable::GetRandomAngleForce(80.0f) },
		Moveable::CalculateMove,
		&collisionCircle,
		Object::Nothing::Update::Logic,
		Object::Nothing::Update::RenderCircle
	};

	const Object::Object circle12 {
		Object::Type::Circle + 11,
		{ { 600, 300 }, Transform::Rotation::zero, Transform::Scale::one },
		{ &circleSurface1 },
		Color::white,
		Draw::Circle,
		{ Moveable::GetRandomAngleForce(80.0f) },
		Moveable::CalculateMove,
		&collisionCircle,
		Object::Nothing::Update::Logic,
		Object::Nothing::Update::RenderCircle
	};

	const Object::Object circle13 {
		Object::Type::Circle + 12,
		{ { 700, 300 }, Transform::Rotation::zero, Transform::Scale::one },
		{ &circleSurface1 },
		Color::lightGray,
		Draw::Circle,
		{ Moveable::GetRandomAngleForce(80.0f) },
		Moveable::CalculateMove,
		&collisionCircle,
		Object::Nothing::Update::Logic,
		Object::Nothing::Update::RenderCircle
	};

	const Object::Object circle14 {
		Object::Type::Circle + 13,
		{ { 800, 300 }, Transform::Rotation::zero, Transform::Scale::one },
		{ &circleSurface1 },
		Color::gray,
		Draw::Circle,
		{ Moveable::GetRandomAngleForce(80.0f) },
		Moveable::CalculateMove,
		&collisionCircle,
		Object::Nothing::Update::Logic,
		Object::Nothing::Update::RenderCircle
	};

	//return array<Object::Object, 0>{};
	return array<Object::Object, 6> { 
		circle1, circle2, 
		circle3, circle4,
		circle5, circle6
	};
	//return array<Object::Object, 14>{ 
	//	circle1, circle2, circle3, circle4, 
	//	circle5, circle6, circle7, circle8,
	//	circle9, circle10, circle11, circle12, 
	//	circle13, circle14 
	//};
}

[[nodiscard]] auto CreateSquareObjects() {

	// Objects
	const Object::Object square1 {
		Object::Type::Square + 0,
		{ { 100, 200 }, Transform::Rotation::zero, Transform::Scale::one },
		{ &squareSurface1 },
		Color::purple,
		Draw::Square,
		{ Moveable::GetRandomAngleForce(80.0f) },
		Moveable::CalculateMove,
		&collisionSquare,
		Object::Nothing::Update::Logic,
		Object::Nothing::Update::RenderSquare
	};

	const Object::Object square2 {
		Object::Type::Square + 1,
		{ { 200, 200 }, Transform::Rotation::zero, Transform::Scale::one },
		{ &squareSurface1 },
		Color::green,
		Draw::Square,
		{ Moveable::GetRandomAngleForce(80.0f) },
		Moveable::CalculateMove,
		&collisionSquare,
		Object::Nothing::Update::Logic,
		Object::Nothing::Update::RenderSquare
	};

	const Object::Object square3 {
		Object::Type::Square + 2,
		{ { 200, 300 }, Transform::Rotation::zero, Transform::Scale::one },
		{ &squareSurface1 },
		Color::white,
		Draw::Square,
		{ Moveable::GetRandomAngleForce(80.0f) },
		Moveable::CalculateMove,
		&collisionSquare,
		Object::Nothing::Update::Logic,
		Object::Nothing::Update::RenderSquare
	};

	const Object::Object square4 {
		Object::Type::Square + 3,
		{ { 200, 400 }, Transform::Rotation::zero, Transform::Scale::one },
		{ &squareSurface1 },
		Color::brown,
		Draw::Square,
		{ Moveable::GetRandomAngleForce(80.0f) },
		Moveable::CalculateMove,
		&collisionSquare,
		Object::Nothing::Update::Logic,
		Object::Nothing::Update::RenderSquare
	};

	const Object::Object square5 {
		Object::Type::Square + 4,
		{ { 300, 100 }, Transform::Rotation::zero, Transform::Scale::one },
		{ &squareSurface1 },
		Color::cyan,
		Draw::Square,
		{ Moveable::GetRandomAngleForce(80.0f) },
		Moveable::CalculateMove,
		&collisionSquare,
		Object::Nothing::Update::Logic,
		Object::Nothing::Update::RenderSquare
	};

	const Object::Object square6 {
		Object::Type::Square + 5,
		{ { 300, 200 }, Transform::Rotation::zero, Transform::Scale::one },
		{ &squareSurface1 },
		Color::gray,
		Draw::Square,
		{ Moveable::GetRandomAngleForce(80.0f) },
		Moveable::CalculateMove,
		&collisionSquare,
		Object::Nothing::Update::Logic,
		Object::Nothing::Update::RenderSquare
	};

	const Object::Object square7 {
		Object::Type::Square + 6,
		{ { 300, 300 }, Transform::Rotation::zero, Transform::Scale::one },
		{ &squareSurface1 },
		Color::lightGray,
		Draw::Square,
		{ Moveable::GetRandomAngleForce(80.0f) },
		Moveable::CalculateMove,
		&collisionSquare,
		Object::Nothing::Update::Logic,
		Object::Nothing::Update::RenderSquare
	};

	const Object::Object square8 {
		Object::Type::Square + 7,
		{ { 300, 400 }, Transform::Rotation::zero, Transform::Scale::one },
		{ &squareSurface1 },
		Color::pink,
		Draw::Square,
		{ Moveable::GetRandomAngleForce(80.0f) },
		Moveable::CalculateMove,
		&collisionSquare,
		Object::Nothing::Update::Logic,
		Object::Nothing::Update::RenderSquare
	};

	const Object::Object square9 {
		Object::Type::Square + 8,
		{ { 400, 100 }, Transform::Rotation::zero, Transform::Scale::one },
		{ &squareSurface1 },
		Color::orange,
		Draw::Square,
		{ Moveable::GetRandomAngleForce(80.0f) },
		Moveable::CalculateMove,
		&collisionSquare,
		Object::Nothing::Update::Logic,
		Object::Nothing::Update::RenderSquare
	};

	const Object::Object square10 {
		Object::Type::Square + 9,
		{ { 400, 200 }, Transform::Rotation::zero, Transform::Scale::one },
		{ &squareSurface1 },
		Color::darkGreen,
		Draw::Square,
		{ Moveable::GetRandomAngleForce(80.0f) },
		Moveable::CalculateMove,
		&collisionSquare,
		Object::Nothing::Update::Logic,
		Object::Nothing::Update::RenderSquare
	};

	const Object::Object square11 {
		Object::Type::Square + 10,
		{ { 400, 300 }, Transform::Rotation::zero, Transform::Scale::one },
		{ &squareSurface1 },
		Color::magenta,
		Draw::Square,
		{ Moveable::GetRandomAngleForce(80.0f) },
		Moveable::CalculateMove,
		&collisionSquare,
		Object::Nothing::Update::Logic,
		Object::Nothing::Update::RenderSquare
	};

	const Object::Object square12 {
		Object::Type::Square + 11,
		{ { 400, 400 }, Transform::Rotation::zero, Transform::Scale::one },
		{ &squareSurface1 },
		Color::lightGreen,
		Draw::Square,
		{ Moveable::GetRandomAngleForce(80.0f) },
		Moveable::CalculateMove,
		&collisionSquare,
		Object::Nothing::Update::Logic,
		Object::Nothing::Update::RenderSquare
	};

	//return array<Object::Object, 0>{};
	return array<Object::Object, 6>{ 
		square1, square2,
		square3, square4,
		square5, square6,
	};
	//return array<Object::Object, 12>{
	//	square1, square2, square3, square4,
	//	square5, square6, square7, square8,
	//	square9, square10, square11, square12,
	//};
}

getter CreateCollisionsSidescrollerMap(const int& tileSize) {
	const size collidersCount(6);

	return array<Rectangle, collidersCount> {
		// It should work this way matthew but doesn't... // start_x, start_y, start_x + end_x, start_y + end_y.
		// Should be: start_x, start_y, extent_x, extent_y.
		Rectangle { 5 * tileSize, 0 * tileSize, 94 * tileSize, (0 + 2) * tileSize },
		Rectangle { 5 * tileSize, 11 * tileSize, 37 * tileSize, (11 + 1) * tileSize },
		Rectangle { 40 * tileSize, 9 * tileSize, 43 * tileSize, (9 + 1) * tileSize }, // platform_1
		Rectangle { 46 * tileSize, 11 * tileSize, 94 * tileSize, (11 + 1) * tileSize },
		Rectangle { 65 * tileSize, 9 * tileSize, (65 + 2) * tileSize, (9 + 1) * tileSize }, // platform_2
		Rectangle { 71 * tileSize, 8 * tileSize, (71 + 2) * tileSize, (8 + 1) * tileSize }  // platform_3
	};
}


[[nodiscard]] auto CreateCollisionsMap1(const int& tileSize) {
	const size nonLoopLength = 4;
	array<Rectangle, nonLoopLength + (4 * 7) + (6 * 3) + (3 * 6)> collisions;
	collisions[0] = { 0, 0, 78 * 32, 2 * 32 }; // map top
	collisions[1] = { 0, 0, 2 * 32, 44 * 32 }; // map left
	collisions[2] = { 76 * 32, 0, 2 * 32, 44 * 32 }; // map right
	collisions[3] = { 0, 43 * 32, 78 * 32, 2 * 32 }; // map bottom

	for (int y = 0; y < 4; y++) { // Central Part
		for (int x = 0; x < 7; x++) {
			const int colliderLengthX = 4 * tileSize;
			const int colliderLengthY = 4 * tileSize;

			const auto& index = x + (y * 7);
			const auto& startX = (4 * tileSize) + (x * 11 * tileSize);
			const auto& startY = (4 * tileSize) + (y * 11 * tileSize);

			collisions[nonLoopLength + index] = { startX, startY, colliderLengthX + startX, colliderLengthY + startY };
		}
	}

	for (int y = 0; y < 3; y++) { // Pluses Y Part
		for (int x = 0; x < 6; x++) {
			const int colliderLengthX = 3 * tileSize;
			const int colliderLengthY = 9 * tileSize;

			const auto& index = x + (y * 6);
			const auto& startX = (10 * tileSize) + (x * 11 * tileSize);
			const auto& startY = (7 * tileSize) + (y * 11 * tileSize);

			collisions[nonLoopLength + (4 * 7) + index] = {startX, startY, colliderLengthX + startX, colliderLengthY + startY};
		}
	}

	for (int y = 0; y < 3; y++) { // Pluses X Part
		for (int x = 0; x < 6; x++) {
			const int colliderLengthX = 9 * tileSize;
			const int colliderLengthY = 3 * tileSize;

			const auto& index = x + (y * 6);
			const auto& startX = (7 * tileSize) + (x * 11 * tileSize);
			const auto& startY = (10 * tileSize) + (y * 11 * tileSize);

			collisions[nonLoopLength + (4 * 7) + (3 * 6) + index] = { startX, startY, colliderLengthX + startX, colliderLengthY + startY };
		}
	}

	return collisions;
}

[[nodiscard]] auto CreateCollisionsMap2(const int& tileSize) {
	const size nonLoopLength = 4;
	array<Rectangle, nonLoopLength + (4 * 7)> collisions;
	collisions[0] = { 0, 0, 64 * tileSize, 2 * tileSize }; // map top
	collisions[1] = { 0, 0, 2 * tileSize, 44 * tileSize }; // map left
	collisions[2] = { 58 * tileSize, 0, 2 * tileSize, 44 * tileSize }; // map right
	collisions[3] = { 0, 34 * tileSize, 64 * tileSize, 2 * tileSize }; // map bottom

	for (int y = 0; y < 4; y++) { // Central Part
		for (int x = 0; x < 7; x++) {
			const int colliderLengthX = 4 * tileSize;
			const int colliderLengthY = 4 * tileSize;

			const auto& index = x + (y * 7);
			const auto& startX = (4 * tileSize) + (x * 8 * tileSize);
			const auto& startY = (4 * tileSize) + (y * 8 * tileSize);

			collisions[nonLoopLength + index] = { startX, startY, colliderLengthX + startX, colliderLengthY + startY };
		}
	}

	return collisions;
}

[[nodiscard]] auto CreateCollisionsMap3(const int& tileSize) {
	const size nonLoopLength = 4;
	array<Rectangle, nonLoopLength> collisions;
	collisions[0] = { 0, 0, 86 * tileSize, 2 * tileSize }; // map top
	collisions[1] = { 0, 0, 2 * tileSize, 44 * tileSize }; // map left
	collisions[2] = { 84 * tileSize, 0, 2 * tileSize, 44 * tileSize }; // map right
	collisions[3] = { 0, 37 * tileSize, 86 * tileSize, 2 * tileSize }; // map bottom

	return collisions;
}