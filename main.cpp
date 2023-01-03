#include "Framework.hpp"
#include "Window.hpp"
#include "Game.hpp"
#include "InitialObjects.hpp"

// TODO:
// - srand((unsigned int)time(NULL));
//   Do something with it...
// - FixedLogicUpdate(); ?
//   if(deltaTime)
//   some OS integration.... winapi ? yes
//   https://stackoverflow.com/questions/15683221/how-to-call-a-function-every-x-seconds

int SDL_main(int argc, char** argv) {

	DEBUG Log::Info("Running in Debug Mode...");

	// Window Itself can have it's parameters changed.
	const array<character, 25> windowTitle { "2DGry-242539-Polecenie-7" };
	const Vector::Vector2<uint32> sceneViewport { 1280 , 720 };
	Window::WindowStruct windowStruct { sceneViewport, windowTitle.size(), windowTitle.data(), { 23, 23, 23, 255 } };

	auto circleObjects = CreateCircleObjects();
	auto squareObjects = CreateSquareObjects();

	SceneGraph::SceneGraph sceneGraph {
		&windowStruct.backgroundColor,
		circleObjects.size(),
		circleObjects.data(),
		squareObjects.size(),
		squareObjects.data(),
		{ 0, 0, sceneViewport.x, sceneViewport.y }
	};

	{ // Game
		MainWindow mainWindow;
		Renderer mainRenderer;
		Game::Create(windowStruct, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC, mainWindow, mainRenderer);
		Game::MainLoop(sceneGraph, mainRenderer);
		Game::Destroy(mainWindow, mainRenderer);
	}

	return 0;
}