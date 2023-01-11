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

// ZADANIE:
// - labirynt jest wczytywanym z pliku zbiorem œcian z po³¹czonych prostok¹tów, labirynt jest wiêkszy, ni¿ ekran, wiêc potrzebne s¹ algorytmy ruchu kamery,
// - wyœwietlany jest cel oraz wskazanie kierunku na niego, jeœli nie jest on aktualnie na ekranie,
// - DONE - wyœwietlanych jest dwóch graczy, gracze maj¹ dwie ró¿ne bry³y kolizyjne(kwadrat i okr¹g) – sterowanie klawiatura + pad lub klawiatura WSAD + klawiatura strza³ki,
// - gracze poruszaj¹ siê po planszy, aby dotrzeæ do celu, zrestartowaæ grê(po widocznej pauzie), gdy którykolwiek z graczy osi¹gnie cel,
// - ocena 5 wymaga(zamiast restartowania) trzech sekwencyjnie wczytywanych labiryntów ka¿dego nieco wiêkszego od poprzedniego i restartu dopiero po osi¹gniêciu celu w trzecim z nich(wraz z wypisaniem wyniku(np.na konsoli) – to znaczy, ile celów na 3 labirynty osi¹gn¹³ ka¿dy z graczy).

int SDL_main(int argc, char** argv) {

	DEBUG Log::Info("Running in Debug Mode...");

	// Window Itself can have it's parameters changed.
	const array<character, 25> windowTitle { "2DGry-242539-Polecenie-7" };
	const Vector::Vector2<uint32> sceneViewport { 1280 , 720 };
	Window::WindowStruct windowStruct { sceneViewport, windowTitle.size(), windowTitle.data(), { 23, 23, 23, 255 } };

	GameObjects::Player::Player player1 { 0 }, player2 { 0 };

	{ // Game
		MainWindow mainWindow;
		Renderer mainRenderer;
		Game::Create(windowStruct, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC, mainWindow, mainRenderer);

		//auto scene1 = CreateScene1(mainRenderer, windowStruct.backgroundColor, sceneViewport);
		// Camera
		const Camera::Camera camera { Vector::Vector2<float> { 0, 0 }, sceneViewport };
		// Players
		auto player1s = CreatePlayer1sObjects();
		auto player2s = CreatePlayer2sObjects();
		// MAP
		const int tileSize = 32;
		GameObjects::MazeMap::TextureAtlas textureAtlas(GameObjects::MazeMap::CreateTextureAtlas(mainRenderer, 8, tileSize, "assets/tilemap.png"));
		GameObjects::MazeMap::Map map(GameObjects::MazeMap::CreateMapFromFile({ 0.0f, 0.0f }, textureAtlas, "assets/maps/3.map"));
		// Collisions
		auto collisions = CreateCollisionsMap1(tileSize);
		// Triggers
		int startX = 2 * tileSize, startY = 2 * tileSize;
		Trigger::Trigger exitTrigger { Rectangle { startX, startY, 32 * 2 + startX, 32 * 2 + startY }, Finish::Trigger };
		array<Trigger::Trigger, 1> triggers { exitTrigger };
		auto scene1 = SceneGraph::SceneGraph {
			&windowStruct.backgroundColor,
			camera,
			player1s.size(),
			player1s.data(),
			player2s.size(),
			player2s.data(),
			{ 0, 0, (int)sceneViewport.x * 2, (int)sceneViewport.y * 2 },
			map,
			collisions.size(),
			collisions.data(),
			triggers.size(),
			triggers.data()
		};

		array<SceneGraph::SceneGraph, 1> scenes { scene1 };

		Game::MainLoop(scenes.size(), scenes.data(), mainRenderer);
		Game::Destroy(mainWindow, mainRenderer);

		
		GameObjects::MazeMap::DestroyMap(scene1.map);
		GameObjects::MazeMap::DestroyTextureAtlas(scene1.map.textureAtlas);
	}

	return 0;
}