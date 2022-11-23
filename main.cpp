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

	// Objects
	const Object::Object circle { 
		Transform::zero, 
		Color::red, 
		Draw::Circle, 
		{ Moveable::GetRandomAngleForce(80.0f), { 1, 1 } },
		Moveable::CalculateMove 
	};

	array<Object::Object, 1> objects { circle };

	MainWindow mainWindow;
	Renderer mainRenderer;

	// Game
	Game::Create(windowStruct, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC, mainWindow, mainRenderer);
	Game::MainLoop(mainRenderer, windowStruct.backgroundColor, objects.size(), objects.data());
	Game::Destroy(mainWindow, mainRenderer);

	return 0;
}