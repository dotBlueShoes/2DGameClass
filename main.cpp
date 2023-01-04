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
// - wyœwietlanych jest dwóch graczy, gracze maj¹ dwie ró¿ne bry³y kolizyjne(kwadrat i okr¹g) – sterowanie klawiatura + pad lub klawiatura WSAD + klawiatura strza³ki,
// - gracze poruszaj¹ siê po planszy, aby dotrzeæ do celu, zrestartowaæ grê(po widocznej pauzie), gdy którykolwiek z graczy osi¹gnie cel,
// - ocena 5 wymaga(zamiast restartowania) trzech sekwencyjnie wczytywanych labiryntów ka¿dego nieco wiêkszego od poprzedniego i restartu dopiero po osi¹gniêciu celu w trzecim z nich(wraz z wypisaniem wyniku(np.na konsoli) – to znaczy, ile celów na 3 labirynty osi¹gn¹³ ka¿dy z graczy).

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