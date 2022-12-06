#include "Framework.hpp"
#include "Window.hpp"
#include "Object.hpp"
#include "Game.hpp"

int SDL_main(int argc, char** argv) {

	// TODO:
	// Do something with it...
	srand((unsigned int)time(NULL));

	// Window
	array<char, 25> windowTitle { "2DGry-242539-Polecenie-7" };
	const Color::Color windowColor { 23, 23, 23, 255 };
	const Vector::Vector2<uint32> windowViewport{ 920 , 360 };
	const Window::WindowStruct windowStruct { windowViewport, windowTitle.size(), windowTitle.data(), windowColor };
	const float radius = 30.0f;

	ObjectType::Circle circleType1 { 30 };
	ObjectType::Square squareType1 { 60, 60 };

	// Objects
	const Object::Object circle1 { 
		{ { 100, 200 }, Transform::Rotation::zero, Transform::Scale::one },
		{ ObjectType::Type::Square, &squareType1 },
		Color::red, 
		Draw::Square, 
		{ Moveable::GetRandomAngleForce(80.0f), { 1, 1 } },
		Moveable::CalculateMove,
		{ { -radius, -radius, radius, radius }, 0 }
	};

	const Object::Object circle2 {
		{ { 200, 200 }, Transform::Rotation::zero, Transform::Scale::one },
		{ ObjectType::Type::Square, &squareType1 },
		Color::green,
		Draw::Square,
		{ Moveable::GetRandomAngleForce(80.0f), { 1, 1 } },
		Moveable::CalculateMove,
		{ { -radius, -radius, radius, radius }, 1 }
	};

	const Object::Object circle3{
		{ { 300, 200 }, Transform::Rotation::zero, Transform::Scale::one },
		{ ObjectType::Type::Circle, &circleType1 },
		Color::blue,
		Draw::Circle,
		{ Moveable::GetRandomAngleForce(80.0f), { 1, 1 } },
		Moveable::CalculateMove,
		{ { -radius, -radius, radius, radius }, 2 }
	};
	
	const Object::Object circle4{
		{ { 400, 200 }, Transform::Rotation::zero, Transform::Scale::one },
		{ ObjectType::Type::Circle, &circleType1 },
		Color::purple,
		Draw::Circle,
		{ Moveable::GetRandomAngleForce(80.0f), { 1, 1 } },
		Moveable::CalculateMove,
		{ { -radius, -radius, radius, radius }, 3 }
	};
	
	const Object::Object circle5{
		{ { 500, 200 }, Transform::Rotation::zero, Transform::Scale::one },
		{ ObjectType::Type::Circle, &circleType1 },
		Color::pink,
		Draw::Circle,
		{ Moveable::GetRandomAngleForce(80.0f), { 1, 1 } },
		Moveable::CalculateMove,
		{ { -radius, -radius, radius, radius }, 4 }
	};
	
	const Object::Object circle6{
		{ { 600, 200 }, Transform::Rotation::zero, Transform::Scale::one },
		{ ObjectType::Type::Circle, &circleType1 },
		Color::lightBlue,
		Draw::Circle,
		{ Moveable::GetRandomAngleForce(80.0f), { 1, 1 } },
		Moveable::CalculateMove,
		{ { -radius, -radius, radius, radius }, 5 }
	};
	
	const Object::Object circle7 {
		{ { 700, 200 }, Transform::Rotation::zero, Transform::Scale::one },
		{ ObjectType::Type::Circle, &circleType1 },
		Color::cyan,
		Draw::Circle,
		{ Moveable::GetRandomAngleForce(80.0f), { 1, 1 } },
		Moveable::CalculateMove,
		{ { -radius, -radius, radius, radius }, 6 }
	};
	
	const Object::Object circle8 {
		{ { 800, 200 }, Transform::Rotation::zero, Transform::Scale::one },
		{ ObjectType::Type::Circle, &circleType1 },
		Color::lightGreen,
		Draw::Circle,
		{ Moveable::GetRandomAngleForce(80.0f), { 1, 1 } },
		Moveable::CalculateMove,
		{ { -radius, -radius, radius, radius }, 7 }
	};
	
	const Object::Object circle9 {
		{ { 100, 300 }, Transform::Rotation::zero, Transform::Scale::one },
		{ ObjectType::Type::Circle, &circleType1 },
		Color::darkBlue,
		Draw::Circle,
		{ Moveable::GetRandomAngleForce(80.0f), { 1, 1 } },
		Moveable::CalculateMove,
		{ { -radius, -radius, radius, radius }, 8 }
	};
	
	const Object::Object circle10 {
		{ { 200, 300 }, Transform::Rotation::zero, Transform::Scale::one },
		{ ObjectType::Type::Circle, &circleType1 },
		Color::darkGreen,
		Draw::Circle,
		{ Moveable::GetRandomAngleForce(80.0f), { 1, 1 } },
		Moveable::CalculateMove,
		{ { -radius, -radius, radius, radius }, 9 }
	};
	
	const Object::Object circle11 {
		{ { 300, 300 }, Transform::Rotation::zero, Transform::Scale::one },
		{ ObjectType::Type::Circle, &circleType1 },
		Color::brown,
		Draw::Circle,
		{ Moveable::GetRandomAngleForce(80.0f), { 1, 1 } },
		Moveable::CalculateMove,
		{ { -radius, -radius, radius, radius }, 10 }
	};
	
	const Object::Object circle12 {
		{ { 400, 300 }, Transform::Rotation::zero, Transform::Scale::one },
		{ ObjectType::Type::Circle, &circleType1 },
		Color::orange,
		Draw::Circle,
		{ Moveable::GetRandomAngleForce(80.0f), { 1, 1 } },
		Moveable::CalculateMove,
		{ { -radius, -radius, radius, radius }, 11 }
	};
	
	const Object::Object circle13 {
		{ { 500, 300 }, Transform::Rotation::zero, Transform::Scale::one },
		{ ObjectType::Type::Circle, &circleType1 },
		Color::magenta,
		Draw::Circle,
		{ Moveable::GetRandomAngleForce(80.0f), { 1, 1 } },
		Moveable::CalculateMove,
		{ { -radius, -radius, radius, radius }, 12 }
	};
	
	const Object::Object circle14 {
		{ { 600, 300 }, Transform::Rotation::zero, Transform::Scale::one },
		{ ObjectType::Type::Circle, &circleType1 },
		Color::white,
		Draw::Circle,
		{ Moveable::GetRandomAngleForce(80.0f), { 1, 1 } },
		Moveable::CalculateMove,
		{ { -radius, -radius, radius, radius }, 13 }
	};
	
	const Object::Object circle15 {
		{ { 700, 300 }, Transform::Rotation::zero, Transform::Scale::one },
		{ ObjectType::Type::Circle, &circleType1 },
		Color::lightGray,
		Draw::Circle,
		{ Moveable::GetRandomAngleForce(80.0f), { 1, 1 } },
		Moveable::CalculateMove,
		{ { -radius, -radius, radius, radius }, 14 }
	};
	
	const Object::Object circle16 {
		{ { 800, 300 }, Transform::Rotation::zero, Transform::Scale::one },
		{ ObjectType::Type::Circle, &circleType1 },
		Color::gray,
		Draw::Circle,
		{ Moveable::GetRandomAngleForce(80.0f), { 1, 1 } },
		Moveable::CalculateMove,
		{ { -radius, -radius, radius, radius }, 15 }
	};

	//array<Object::Object, 2> objects { circle1, circle2 };
	//array<Object::Object, 4> objects{ circle1, circle2, circle3, circle4 };
	array<Object::Object, 16> objects { 
		circle1, circle2, circle3, circle4, circle5, circle6, circle7, circle8,
		circle9, circle10, circle11, circle12, circle13, circle14, circle15, circle16,
	};

	MainWindow mainWindow;
	Renderer mainRenderer;

	// Game
	Game::Create(windowStruct, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC, mainWindow, mainRenderer);
	Game::MainLoop(mainRenderer, windowStruct.backgroundColor, objects.size(), objects.data());
	Game::Destroy(mainWindow, mainRenderer);

	return 0;
}