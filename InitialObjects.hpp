#pragma once
#include "Framework.hpp"
#include "SceneGraph.hpp"
#include "Draw.hpp"

const float radius(30.0f);
Surface::Circle circleSurface1 { 30 };
Collision::CircleBody collisionCircle { radius };
Surface::Square squareSurface1 { 60, 60 };
Collision::SquareBody collisionSquare { -30, -30, 30, 30 };

[[nodiscard]] auto CreateCircleObjects() {

	const Object::Object circle1 {
		Object::Type::Circle + 0,
		{ { 300, 200 }, Transform::Rotation::zero, Transform::Scale::one },
		{ &circleSurface1 },
		Color::blue,
		Draw::Circle,
		{ Moveable::GetRandomAngleForce(80.0f) },
		Moveable::CalculateMove,
		&collisionCircle
	};

	const Object::Object circle2 {
		Object::Type::Circle + 1,
		{ { 400, 200 }, Transform::Rotation::zero, Transform::Scale::one },
		{ &circleSurface1 },
		Color::purple,
		Draw::Circle,
		{ Moveable::GetRandomAngleForce(80.0f) },
		Moveable::CalculateMove,
		&collisionCircle
	};

	const Object::Object circle3 {
		Object::Type::Circle + 2,
		{ { 500, 200 }, Transform::Rotation::zero, Transform::Scale::one },
		{ &circleSurface1 },
		Color::pink,
		Draw::Circle,
		{ Moveable::GetRandomAngleForce(80.0f) },
		Moveable::CalculateMove,
		&collisionCircle
	};

	const Object::Object circle4 {
		Object::Type::Circle + 3,
		{ { 600, 200 }, Transform::Rotation::zero, Transform::Scale::one },
		{ &circleSurface1 },
		Color::lightBlue,
		Draw::Circle,
		{ Moveable::GetRandomAngleForce(80.0f) },
		Moveable::CalculateMove,
		&collisionCircle
	};

	const Object::Object circle5 {
		Object::Type::Circle + 4,
		{ { 700, 200 }, Transform::Rotation::zero, Transform::Scale::one },
		{ &circleSurface1 },
		Color::cyan,
		Draw::Circle,
		{ Moveable::GetRandomAngleForce(80.0f) },
		Moveable::CalculateMove,
		&collisionCircle
	};

	const Object::Object circle6 {
		Object::Type::Circle + 5,
		{ { 800, 200 }, Transform::Rotation::zero, Transform::Scale::one },
		{ &circleSurface1 },
		Color::lightGreen,
		Draw::Circle,
		{ Moveable::GetRandomAngleForce(80.0f) },
		Moveable::CalculateMove,
		&collisionCircle
	};

	const Object::Object circle7 {
		Object::Type::Circle + 6,
		{ { 100, 300 }, Transform::Rotation::zero, Transform::Scale::one },
		{ &circleSurface1 },
		Color::darkBlue,
		Draw::Circle,
		{ Moveable::GetRandomAngleForce(80.0f) },
		Moveable::CalculateMove,
		&collisionCircle
	};

	const Object::Object circle8 {
		Object::Type::Circle + 7,
		{ { 200, 300 }, Transform::Rotation::zero, Transform::Scale::one },
		{ &circleSurface1 },
		Color::darkGreen,
		Draw::Circle,
		{ Moveable::GetRandomAngleForce(80.0f) },
		Moveable::CalculateMove,
		&collisionCircle
	};

	const Object::Object circle9 {
		Object::Type::Circle + 8,
		{ { 300, 300 }, Transform::Rotation::zero, Transform::Scale::one },
		{ &circleSurface1 },
		Color::brown,
		Draw::Circle,
		{ Moveable::GetRandomAngleForce(80.0f) },
		Moveable::CalculateMove,
		&collisionCircle
	};

	const Object::Object circle10 {
		Object::Type::Circle + 9,
		{ { 400, 300 }, Transform::Rotation::zero, Transform::Scale::one },
		{ &circleSurface1 },
		Color::orange,
		Draw::Circle,
		{ Moveable::GetRandomAngleForce(80.0f) },
		Moveable::CalculateMove,
		&collisionCircle
	};

	const Object::Object circle11 {
		Object::Type::Circle + 10,
		{ { 500, 300 }, Transform::Rotation::zero, Transform::Scale::one },
		{ &circleSurface1 },
		Color::magenta,
		Draw::Circle,
		{ Moveable::GetRandomAngleForce(80.0f) },
		Moveable::CalculateMove,
		&collisionCircle
	};

	const Object::Object circle12 {
		Object::Type::Circle + 11,
		{ { 600, 300 }, Transform::Rotation::zero, Transform::Scale::one },
		{ &circleSurface1 },
		Color::white,
		Draw::Circle,
		{ Moveable::GetRandomAngleForce(80.0f) },
		Moveable::CalculateMove,
		&collisionCircle
	};

	const Object::Object circle13 {
		Object::Type::Circle + 12,
		{ { 700, 300 }, Transform::Rotation::zero, Transform::Scale::one },
		{ &circleSurface1 },
		Color::lightGray,
		Draw::Circle,
		{ Moveable::GetRandomAngleForce(80.0f) },
		Moveable::CalculateMove,
		&collisionCircle
	};

	const Object::Object circle14 {
		Object::Type::Circle + 13,
		{ { 800, 300 }, Transform::Rotation::zero, Transform::Scale::one },
		{ &circleSurface1 },
		Color::gray,
		Draw::Circle,
		{ Moveable::GetRandomAngleForce(80.0f) },
		Moveable::CalculateMove,
		&collisionCircle
	};

	//array<Object::Object, 2> objects { square1, circle1 };
	//array<Object::Object, 14> objects { 
	//	circle1, circle2, circle3, circle4, circle5, circle6, circle7, circle8,
	//	circle9, circle10, circle11, circle12, circle13, circle14
	//};

	return array<Object::Object, 4>{ circle1, circle2, circle3, circle4 };
}

[[nodiscard]] auto CreateSquareObjects() {

	// Objects
	const Object::Object square1 {
		Object::Type::Square + 0,
		{ { 100, 200 }, Transform::Rotation::zero, Transform::Scale::one },
		{ &squareSurface1 },
		Color::red,
		Draw::Square,
		{ Moveable::GetRandomAngleForce(80.0f) },
		Moveable::CalculateMove,
		&collisionSquare
	};

	const Object::Object square2 {
		Object::Type::Square + 1,
		{ { 200, 200 }, Transform::Rotation::zero, Transform::Scale::one },
		{ &squareSurface1 },
		Color::green,
		Draw::Square,
		{ Moveable::GetRandomAngleForce(80.0f) },
		Moveable::CalculateMove,
		&collisionSquare
	};

	return array<Object::Object, 2>{ square1, square2 };
}