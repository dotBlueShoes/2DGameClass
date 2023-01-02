#include "Framework.hpp"
#include "Window.hpp"
#include "Game.hpp"
#include "InitialObjects.hpp"

int SDL_main(int argc, char** argv) {

	// TODO:
	// Do something with it...
	// srand((unsigned int)time(NULL));

	DEBUG Log::Info("Running in Debug Mode...");

	// Window
	const array<character, 25> windowTitle { "2DGry-242539-Polecenie-7" };
	const Vector::Vector2<uint32> windowViewport { 1280 , 720 };
	const Color::Color windowColor { 23, 23, 23, 255 };
	
	// Window Itself can have it's parameters changed.
	Window::WindowStruct windowStruct { windowViewport, windowTitle.size(), windowTitle.data(), windowColor };

	auto objects = CreateObjects();

	{ // Game
		MainWindow mainWindow;
		Renderer mainRenderer;
		Game::Create(windowStruct, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC, mainWindow, mainRenderer);
		Game::MainLoop(mainRenderer, windowStruct.backgroundColor, objects.size(), objects.data());
		Game::Destroy(mainWindow, mainRenderer);
	}

	return 0;
}