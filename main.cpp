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

// EXERCISE
// *Verleta*

// BUGS
// - collision bug where one can push other through walls...
// - collision bug where a cube shape between 2 static cube shapes can move through static collidiers...

int SDL_main(int argc, char** argv) {

	// DEBUG Log::Info("Running in Debug Mode...");

	// Window itself can have it's parameters changed.
	const array<character, 25> windowTitle { "2DGry-242539-Polecenie-7" };
	const Vector::Vector2<uint32> sceneViewport { 1280 , 720 };
	Window::WindowStruct windowStruct { sceneViewport, windowTitle.size(), windowTitle.data(), { 23, 23, 23, 255 } };

	{ // Game
		MainWindow mainWindow;
		Renderer mainRenderer;
		Game::Create(windowStruct, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC, mainWindow, mainRenderer);

		//auto scene1 = CreateScene1(mainRenderer, windowStruct.backgroundColor, sceneViewport);
		
		// Camera
		const Camera::Camera camera { Vector::Vector2<float> { 0, 0 }, sceneViewport };

		// MAP
		const int tileSize = 32;
		GameObjects::MazeMap::TextureAtlas textureAtlas(GameObjects::MazeMap::CreateTextureAtlas(mainRenderer, 8, tileSize, "assets/tilemap.png"));
		GameObjects::MazeMap::Map sidescrollerMap(GameObjects::MazeMap::CreateMapFromFile({ 0.0f, 0.0f }, textureAtlas, "assets/maps/sidescroller.map", { 94, 12 }));
		//GameObjects::MazeMap::Map map1(GameObjects::MazeMap::CreateMapFromFile({ 0.0f, 0.0f }, textureAtlas, "assets/maps/1.map", { 78, 45 } ));
		//GameObjects::MazeMap::Map map2(GameObjects::MazeMap::CreateMapFromFile({ 0.0f, 0.0f }, textureAtlas, "assets/maps/2.map", { 60, 36 } ));
		//GameObjects::MazeMap::Map map3(GameObjects::MazeMap::CreateMapFromFile({ 0.0f, 0.0f }, textureAtlas, "assets/maps/3.map", { 86, 39 } ));

		// Collisions
		auto collisions = CreateCollisionsSidescrollerMap(tileSize);
		//auto collisions1 = CreateCollisionsMap1(tileSize);
		//auto collisions2 = CreateCollisionsMap2(tileSize);
		//auto collisions3 = CreateCollisionsMap3(tileSize);

		// // Triggers
		// int startX = 2 * tileSize, startY = 2 * tileSize;
		// Trigger::Trigger exitTrigger1 { Rectangle { startX, startY, 32 * 2 + startX, 32 * 2 + startY }, Finish::Trigger };
		// array<Trigger::Trigger, 1> triggers1 { exitTrigger1 };
		// Trigger::Trigger exitTrigger2{ Rectangle { startX, startY, 32 * 2 + startX, 32 * 2 + startY }, Finish::Trigger };
		// array<Trigger::Trigger, 1> triggers2 { exitTrigger2 };
		// Trigger::Trigger exitTrigger3{ Rectangle { startX, startY, 32 * 2 + startX, 32 * 2 + startY }, Finish::Trigger };
		// array<Trigger::Trigger, 1> triggers3 { exitTrigger3 };

		// Players
		auto player1s = CreatePlayer1sObjects(sidescrollerMap, collisions.size(), collisions.data());
		auto player2s = CreatePlayer2sObjects(sidescrollerMap, collisions.size(), collisions.data());

		//auto scene1 = SceneGraph::SceneGraph {
		//	&windowStruct.backgroundColor,
		//	camera,
		//	player1s.size(),
		//	player1s.data(),
		//	player2s.size(),
		//	player2s.data(),
		//	{ 0, 0, (int)sceneViewport.x * 2, (int)sceneViewport.y * 2 },
		//	map1,
		//	collisions1.size(),
		//	collisions1.data(),
		//	triggers1.size(),
		//	triggers1.data()
		//};
		//
		//auto scene2 = SceneGraph::SceneGraph{
		//	&windowStruct.backgroundColor,
		//	camera,
		//	player1s.size(),
		//	player1s.data(),
		//	player2s.size(),
		//	player2s.data(),
		//	{ 0, 0, (int)sceneViewport.x * 3, (int)sceneViewport.y * 3 },
		//	map2,
		//	collisions2.size(),
		//	collisions2.data(),
		//	triggers2.size(),
		//	triggers2.data()
		//};
		//
		//auto scene3 = SceneGraph::SceneGraph{
		//	&windowStruct.backgroundColor,
		//	camera,
		//	player1s.size(),
		//	player1s.data(),
		//	player2s.size(),
		//	player2s.data(),
		//	{ 0, 0, (int)sceneViewport.x * 3, (int)sceneViewport.y * 3 },
		//	map3,
		//	collisions3.size(),
		//	collisions3.data(),
		//	triggers3.size(),
		//	triggers3.data()
		//};

		auto scene1 = SceneGraph::SceneGraph {
			&windowStruct.backgroundColor,
			camera,
			player1s.size(),
			player1s.data(),
			player2s.size(),
			player2s.data(),
			{ 0, 0, (int)sceneViewport.x * 3, (int)sceneViewport.y * 3 }, // outside_collider
			sidescrollerMap,
			collisions.size(),
			collisions.data()
		};

		array<SceneGraph::SceneGraph, 1> scenes { scene1 };

		Game::MainLoop(scenes.size(), scenes.data(), mainRenderer);
		Game::Destroy(mainWindow, mainRenderer);

		
		GameObjects::MazeMap::DestroyMap(scene1.map);
		GameObjects::MazeMap::DestroyTextureAtlas(scene1.map.textureAtlas);
	}

	return 0;
}