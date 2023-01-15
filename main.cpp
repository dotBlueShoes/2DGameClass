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
// - DONE labirynt jest wczytywanym z pliku zbiorem �cian z po��czonych prostok�t�w, labirynt jest wi�kszy, ni� ekran, wi�c potrzebne s� algorytmy ruchu kamery,
// - DONE wy�wietlany jest cel oraz wskazanie kierunku na niego, je�li nie jest on aktualnie na ekranie,
// - DONE - wy�wietlanych jest dw�ch graczy, gracze maj� dwie r�ne bry�y kolizyjne(kwadrat i okr�g) � sterowanie klawiatura + pad lub klawiatura WSAD + klawiatura strza�ki,
// - DONE gracze poruszaj� si� po planszy, aby dotrze� do celu, zrestartowa� gr�(po widocznej pauzie), gdy kt�rykolwiek z graczy osi�gnie cel,
// - DONE ocena 5 wymaga(zamiast restartowania) trzech sekwencyjnie wczytywanych labirynt�w ka�dego nieco wi�kszego od poprzedniego i restartu dopiero po osi�gni�ciu celu w trzecim z nich(wraz z wypisaniem wyniku(np.na konsoli) � to znaczy, ile cel�w na 3 labirynty osi�gn�� ka�dy z graczy).

// Zadanie:
// - pol 11-12
// - pol 13
// - pol 14

// wiele rzeczy tu si? prosi o rewrite teraz... 

// Przygotowa? pikselartowy zestaw sprit�w do gry:
// - minimum 2 postacie / obiekty grywalne,
// - minimum 2 animacje akcji dla ka?dej z nich � wersja d?uga i kr�tka(2 klatki naprzemienne),
// - minimum 6 asset�w ze ?wiata gry,
// - pixelartowy ekran tytu?owy gry(na dodatkowy + 1 do oceny).
// - Realizacja: indywidualna.
// Oprogramowanie : dowolne.
// Proporcje pikseli : kwadrat.
// Forma oddania : sprite sheet(png) prezentuj?cy ca?y zestaw postaci(tak?e osobne klatki animacji postaci) i asset�w oraz palet? kolor�w(zdefiniowane RGB, HSV, HEX), osobne pliki(png) statycznych sprite'�w, osobne pliki (gif) animowanych sprite'�w.


int SDL_main(int argc, char** argv) {

	DEBUG Log::Info("Running in Debug Mode...");

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
		GameObjects::MazeMap::Map map1(GameObjects::MazeMap::CreateMapFromFile({ 0.0f, 0.0f }, textureAtlas, "assets/maps/1.map", { 78, 45 } ));
		GameObjects::MazeMap::Map map2(GameObjects::MazeMap::CreateMapFromFile({ 0.0f, 0.0f }, textureAtlas, "assets/maps/2.map", { 60, 36 } ));
		GameObjects::MazeMap::Map map3(GameObjects::MazeMap::CreateMapFromFile({ 0.0f, 0.0f }, textureAtlas, "assets/maps/3.map", { 86, 39 } ));

		// Collisions
		auto collisions1 = CreateCollisionsMap1(tileSize);
		auto collisions2 = CreateCollisionsMap2(tileSize);
		auto collisions3 = CreateCollisionsMap3(tileSize);

		// Triggers
		int startX = 2 * tileSize, startY = 2 * tileSize;
		Trigger::Trigger exitTrigger1 { Rectangle { startX, startY, 32 * 2 + startX, 32 * 2 + startY }, Finish::Trigger };
		array<Trigger::Trigger, 1> triggers1 { exitTrigger1 };
		Trigger::Trigger exitTrigger2{ Rectangle { startX, startY, 32 * 2 + startX, 32 * 2 + startY }, Finish::Trigger };
		array<Trigger::Trigger, 1> triggers2 { exitTrigger2 };
		Trigger::Trigger exitTrigger3{ Rectangle { startX, startY, 32 * 2 + startX, 32 * 2 + startY }, Finish::Trigger };
		array<Trigger::Trigger, 1> triggers3 { exitTrigger3 };

		// Players
		auto player1s = CreatePlayer1sObjects(map1, collisions1.size(), collisions1.data());
		auto player2s = CreatePlayer2sObjects(map1, collisions1.size(), collisions1.data());

		auto scene1 = SceneGraph::SceneGraph {
			&windowStruct.backgroundColor,
			camera,
			player1s.size(),
			player1s.data(),
			player2s.size(),
			player2s.data(),
			{ 0, 0, (int)sceneViewport.x * 2, (int)sceneViewport.y * 2 },
			map1,
			collisions1.size(),
			collisions1.data(),
			triggers1.size(),
			triggers1.data()
		};

		auto scene2 = SceneGraph::SceneGraph{
			&windowStruct.backgroundColor,
			camera,
			player1s.size(),
			player1s.data(),
			player2s.size(),
			player2s.data(),
			{ 0, 0, (int)sceneViewport.x * 3, (int)sceneViewport.y * 3 },
			map2,
			collisions2.size(),
			collisions2.data(),
			triggers2.size(),
			triggers2.data()
		};

		auto scene3 = SceneGraph::SceneGraph{
			&windowStruct.backgroundColor,
			camera,
			player1s.size(),
			player1s.data(),
			player2s.size(),
			player2s.data(),
			{ 0, 0, (int)sceneViewport.x * 3, (int)sceneViewport.y * 3 },
			map3,
			collisions3.size(),
			collisions3.data(),
			triggers3.size(),
			triggers3.data()
		};

		array<SceneGraph::SceneGraph, 3> scenes { scene1, scene2, scene3 };

		Game::MainLoop(scenes.size(), scenes.data(), mainRenderer);
		Game::Destroy(mainWindow, mainRenderer);

		
		GameObjects::MazeMap::DestroyMap(scene1.map);
		GameObjects::MazeMap::DestroyTextureAtlas(scene1.map.textureAtlas);
	}

	return 0;
}