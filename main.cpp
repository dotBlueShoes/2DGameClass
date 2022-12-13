#include "Framework.hpp"
#include "Window.hpp"
#include "Game.hpp"

#include "Entity.hpp"
#include "Entities/EntityPlayerCircle.hpp"
#include "Entities/EntityPlayerSquare.hpp"
#include "Object.hpp"

int SDL_main(int argc, char** argv) {

	// TODO:
	// Do something with it...
	srand((unsigned int)time(NULL));

	// Window
	array<char, 25> windowTitle { "2DGry-242539-Polecenie-7" };
	const Color::Color windowColor { 23, 23, 23, 255 };
	const Vector::Vector2<uint32> windowViewport{ 920 , 360 };
	const Window::WindowStruct windowStruct { windowViewport, windowTitle.size(), windowTitle.data(), windowColor };
	const float radius(30.0f);

	Surface::Circle circleSurface1 { 30 };
	Surface::Square squareSurface1 { 60, 60 };

	const Entity::PlayerCircle playerCircle { Transform::zero, circleSurface1, { 30 }, { Moveable::GetRandomAngleForce(80.0f) } };
	const Entity::PlayerSquare playerSquare { Transform::zero, squareSurface1, { 60, 60 }, { Moveable::GetRandomAngleForce(80.0f) } };

	Entity::EntitiesBuffor buffor(Entity::CreateEntitiesBuffor(100));
	Entity::CreateEntitiesCPY<Entity::PlayerCircle>(buffor, playerCircle, 1);
	Entity::CreateEntitiesCPY<Entity::PlayerSquare>(buffor, playerSquare, 1, 1);
	Entity::DeleteEntitiesBuffor(buffor, 100);

	// Objects
	const Object::Object square1 { 
		Object::Type::Square + 0,
		{ { 100, 200 }, Transform::Rotation::zero, Transform::Scale::one },
		{ &squareSurface1 },
		Color::red, 
		Draw::Square, 
		{ Moveable::GetRandomAngleForce(80.0f) },
		Moveable::CalculateMove,
		{ { -radius, -radius, radius, radius }}
	};

	const Object::Object square2 {
		Object::Type::Square + 1,
		{ { 200, 200 }, Transform::Rotation::zero, Transform::Scale::one },
		{ &squareSurface1 },
		Color::green,
		Draw::Square,
		{ Moveable::GetRandomAngleForce(80.0f) },
		Moveable::CalculateMove,
		{ { -radius, -radius, radius, radius }}
	};

	const Object::Object circle1 {
		Object::Type::Circle + 0,
		{ { 300, 200 }, Transform::Rotation::zero, Transform::Scale::one },
		{ &circleSurface1 },
		Color::blue,
		Draw::Circle,
		{ Moveable::GetRandomAngleForce(80.0f) },
		Moveable::CalculateMove,
		{ { -radius, -radius, radius, radius } }
	};
	
	const Object::Object circle2 {
		Object::Type::Circle + 1,
		{ { 400, 200 }, Transform::Rotation::zero, Transform::Scale::one },
		{ &circleSurface1 },
		Color::purple,
		Draw::Circle,
		{ Moveable::GetRandomAngleForce(80.0f) },
		Moveable::CalculateMove,
		{ { -radius, -radius, radius, radius }}
	};
	
	const Object::Object circle3 {
		Object::Type::Circle + 2,
		{ { 500, 200 }, Transform::Rotation::zero, Transform::Scale::one },
		{ &circleSurface1 },
		Color::pink,
		Draw::Circle,
		{ Moveable::GetRandomAngleForce(80.0f) },
		Moveable::CalculateMove,
		{ { -radius, -radius, radius, radius } }
	};
	
	const Object::Object circle4 {
		Object::Type::Circle + 3,
		{ { 600, 200 }, Transform::Rotation::zero, Transform::Scale::one },
		{ &circleSurface1 },
		Color::lightBlue,
		Draw::Circle,
		{ Moveable::GetRandomAngleForce(80.0f) },
		Moveable::CalculateMove,
		{ { -radius, -radius, radius, radius } }
	};
	
	const Object::Object circle5 {
		Object::Type::Circle + 4,
		{ { 700, 200 }, Transform::Rotation::zero, Transform::Scale::one },
		{ &circleSurface1 },
		Color::cyan,
		Draw::Circle,
		{ Moveable::GetRandomAngleForce(80.0f) },
		Moveable::CalculateMove,
		{ { -radius, -radius, radius, radius } }
	};
	
	const Object::Object circle6 {
		Object::Type::Circle + 5,
		{ { 800, 200 }, Transform::Rotation::zero, Transform::Scale::one },
		{ &circleSurface1 },
		Color::lightGreen,
		Draw::Circle,
		{ Moveable::GetRandomAngleForce(80.0f) },
		Moveable::CalculateMove,
		{ { -radius, -radius, radius, radius } }
	};
	
	const Object::Object circle7 {
		Object::Type::Circle + 6,
		{ { 100, 300 }, Transform::Rotation::zero, Transform::Scale::one },
		{ &circleSurface1 },
		Color::darkBlue,
		Draw::Circle,
		{ Moveable::GetRandomAngleForce(80.0f) },
		Moveable::CalculateMove,
		{ { -radius, -radius, radius, radius } }
	};
	
	const Object::Object circle8 {
		Object::Type::Circle + 7,
		{ { 200, 300 }, Transform::Rotation::zero, Transform::Scale::one },
		{ &circleSurface1 },
		Color::darkGreen,
		Draw::Circle,
		{ Moveable::GetRandomAngleForce(80.0f) },
		Moveable::CalculateMove,
		{ { -radius, -radius, radius, radius } }
	};
	
	const Object::Object circle9 {
		Object::Type::Circle + 8,
		{ { 300, 300 }, Transform::Rotation::zero, Transform::Scale::one },
		{ &circleSurface1 },
		Color::brown,
		Draw::Circle,
		{ Moveable::GetRandomAngleForce(80.0f) },
		Moveable::CalculateMove,
		{ { -radius, -radius, radius, radius } }
	};
	
	const Object::Object circle10 {
		Object::Type::Circle + 9,
		{ { 400, 300 }, Transform::Rotation::zero, Transform::Scale::one },
		{ &circleSurface1 },
		Color::orange,
		Draw::Circle,
		{ Moveable::GetRandomAngleForce(80.0f) },
		Moveable::CalculateMove,
		{ { -radius, -radius, radius, radius } }
	};
	
	const Object::Object circle11 {
		Object::Type::Circle + 10,
		{ { 500, 300 }, Transform::Rotation::zero, Transform::Scale::one },
		{ &circleSurface1 },
		Color::magenta,
		Draw::Circle,
		{ Moveable::GetRandomAngleForce(80.0f) },
		Moveable::CalculateMove,
		{ { -radius, -radius, radius, radius } }
	};
	
	const Object::Object circle12 {
		Object::Type::Circle + 11,
		{ { 600, 300 }, Transform::Rotation::zero, Transform::Scale::one },
		{ &circleSurface1 },
		Color::white,
		Draw::Circle,
		{ Moveable::GetRandomAngleForce(80.0f) },
		Moveable::CalculateMove,
		{ { -radius, -radius, radius, radius } }
	};
	
	const Object::Object circle13 {
		Object::Type::Circle + 12,
		{ { 700, 300 }, Transform::Rotation::zero, Transform::Scale::one },
		{ &circleSurface1 },
		Color::lightGray,
		Draw::Circle,
		{ Moveable::GetRandomAngleForce(80.0f) },
		Moveable::CalculateMove,
		{ { -radius, -radius, radius, radius } }
	};
	
	const Object::Object circle14 {
		Object::Type::Circle + 13,
		{ { 800, 300 }, Transform::Rotation::zero, Transform::Scale::one },
		{ &circleSurface1 },
		Color::gray,
		Draw::Circle,
		{ Moveable::GetRandomAngleForce(80.0f) },
		Moveable::CalculateMove,
		{ { -radius, -radius, radius, radius } }
	};

	array<Object::Object, 2> objects { square1, circle1 };
	//array<Object::Object, 4> objects{ circle1, circle2, circle3, circle4 };
	//array<Object::Object, 16> objects { 
	//	square1, square2,
	//	circle1, circle2, circle3, circle4, circle5, circle6, circle7, circle8,
	//	circle9, circle10, circle11, circle12, circle13, circle14
	//};

	MainWindow mainWindow;
	Renderer mainRenderer;

	// Game
	Game::Create(windowStruct, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC, mainWindow, mainRenderer);
	Game::MainLoop(mainRenderer, windowStruct.backgroundColor, objects.size(), objects.data());
	Game::Destroy(mainWindow, mainRenderer);

	return 0;
}