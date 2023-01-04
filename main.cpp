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
// - labirynt jest wczytywanym z pliku zbiorem �cian z po��czonych prostok�t�w, labirynt jest wi�kszy, ni� ekran, wi�c potrzebne s� algorytmy ruchu kamery,
// - wy�wietlany jest cel oraz wskazanie kierunku na niego, je�li nie jest on aktualnie na ekranie,
// - DONE - wy�wietlanych jest dw�ch graczy, gracze maj� dwie r�ne bry�y kolizyjne(kwadrat i okr�g) � sterowanie klawiatura + pad lub klawiatura WSAD + klawiatura strza�ki,
// - gracze poruszaj� si� po planszy, aby dotrze� do celu, zrestartowa� gr�(po widocznej pauzie), gdy kt�rykolwiek z graczy osi�gnie cel,
// - ocena 5 wymaga(zamiast restartowania) trzech sekwencyjnie wczytywanych labirynt�w ka�dego nieco wi�kszego od poprzedniego i restartu dopiero po osi�gni�ciu celu w trzecim z nich(wraz z wypisaniem wyniku(np.na konsoli) � to znaczy, ile cel�w na 3 labirynty osi�gn�� ka�dy z graczy).

int SDL_main(int argc, char** argv) {

	DEBUG Log::Info("Running in Debug Mode...");

	// Window Itself can have it's parameters changed.
	const array<character, 25> windowTitle { "2DGry-242539-Polecenie-7" };
	const Vector::Vector2<uint32> sceneViewport { 1280 , 720 };
	Window::WindowStruct windowStruct { sceneViewport, windowTitle.size(), windowTitle.data(), { 23, 23, 23, 255 } };

	

	{ // Game
		MainWindow mainWindow;
		Renderer mainRenderer;
		Game::Create(windowStruct, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC, mainWindow, mainRenderer);

		auto player1s = CreatePlayer1sObjects();
		auto player2s = CreatePlayer2sObjects();

		// MAP
		GameObjects::MazeMap::TextureAtlas textureAtlas(GameObjects::MazeMap::CreateTextureAtlas(mainRenderer, 8, 32, "assets/tilemap.png"));
		GameObjects::MazeMap::Map map(GameObjects::MazeMap::CreateMapFromFile({ 0.0f, 0.0f }, textureAtlas, "assets/maps/1.map"));

		SceneGraph::SceneGraph sceneGraph{
			&windowStruct.backgroundColor,
			player1s.size(),
			player1s.data(),
			player2s.size(),
			player2s.data(),
			{ 0, 0, sceneViewport.x, sceneViewport.y },
			map
		};

		//auto circleObjects = CreateCircleObjects();
		//auto squareObjects = CreateSquareObjects();
		//
		//SceneGraph::SceneGraph sceneGraph{
		//	&windowStruct.backgroundColor,
		//	circleObjects.size(),
		//	circleObjects.data(),
		//	squareObjects.size(),
		//	squareObjects.data(),
		//	{ 0, 0, sceneViewport.x, sceneViewport.y }
		//};

		Game::MainLoop(sceneGraph, mainRenderer);
		Game::Destroy(mainWindow, mainRenderer);

		GameObjects::MazeMap::DestroyMap(map);
		GameObjects::MazeMap::DestroyTextureAtlas(textureAtlas);
	}

	return 0;
}