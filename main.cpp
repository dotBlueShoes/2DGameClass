#include "Framework.hpp"
#include "Window.hpp"
#include "Object.hpp"
#include "Game.hpp"

int SDL_main(int argc, char** argv) {

	// TODO:
	// Do something with it...
	srand((unsigned int)time(NULL));

	// Window
	array<char, 25> windowTitle { "2DGry-242539-Polecenie-6" };
	const Color::Color windowColor { 23, 23, 23, 255 };
	const Vector::Vector2<uint32> windowViewport{ 920 , 360 };
	const Window::WindowStruct windowStruct { windowViewport, windowTitle.size(), windowTitle.data(), windowColor };
	const float radius(30.0f);

	// Objects
	const Object::Object circle1 { 
		{ { 100, 200 }, Transform::Rotation::zero, Transform::Scale::one },
		Color::red, 
		Draw::Circle, 
		{ Moveable::GetRandomAngleForce(80.0f), { 1, 1 } },
		Moveable::CalculateMove,
		{ { -radius, -radius, radius, radius }, 0 }
	};

	const Object::Object circle2 {
		{ { 200, 200 }, Transform::Rotation::zero, Transform::Scale::one },
		Color::green,
		Draw::Circle,
		{ Moveable::GetRandomAngleForce(80.0f), { 1, 1 } },
		Moveable::CalculateMove,
		{ { -radius, -radius, radius, radius }, 1 }
	};

	const Object::Object circle3{
		{ { 300, 200 }, Transform::Rotation::zero, Transform::Scale::one },
		Color::blue,
		Draw::Circle,
		{ Moveable::GetRandomAngleForce(80.0f), { 1, 1 } },
		Moveable::CalculateMove,
		{ -radius, -radius, radius, radius }
	};

	const Object::Object circle4{
		{ { 400, 200 }, Transform::Rotation::zero, Transform::Scale::one },
		Color::red,
		Draw::Circle,
		{ Moveable::GetRandomAngleForce(80.0f), { 1, 1 } },
		Moveable::CalculateMove,
		{ -radius, -radius, radius, radius }
	};

	const Object::Object circle5{
		{ { 500, 200 }, Transform::Rotation::zero, Transform::Scale::one },
		Color::red,
		Draw::Circle,
		{ Moveable::GetRandomAngleForce(80.0f), { 1, 1 } },
		Moveable::CalculateMove,
		{ -radius, -radius, radius, radius }
	};

	const Object::Object circle6{
		{ { 600, 200 }, Transform::Rotation::zero, Transform::Scale::one },
		Color::red,
		Draw::Circle,
		{ Moveable::GetRandomAngleForce(80.0f), { 1, 1 } },
		Moveable::CalculateMove,
		{ -radius, -radius, radius, radius }
	};

	array<Object::Object, 2> objects { circle1, circle2 };
	//array<Object::Object, 6> objects{ circle1, circle2, circle3, circle4, circle5, circle6 };

	MainWindow mainWindow;
	Renderer mainRenderer;

	// Game
	Game::Create(windowStruct, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC, mainWindow, mainRenderer);
	Game::MainLoop(mainRenderer, windowStruct.backgroundColor, objects.size(), objects.data());
	Game::Destroy(mainWindow, mainRenderer);

	return 0;
}