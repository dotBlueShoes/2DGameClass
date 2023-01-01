#include "Framework.hpp"
#include "Window.hpp"
#include "Game.hpp"

#include "Entity.hpp"
#include "Entities/EntityPlayerCircle.hpp"
#include "Entities/EntityPlayerSquare.hpp"
#include "Object.hpp"

int SDL_main(int argc, char** argv) {

	// TODO:
	// Do something with it...
	// srand((unsigned int)time(NULL));

	// Window
	const array<char, 25> windowTitle { "2DGry-242539-Polecenie-7" };
	const Color::Color windowColor { 23, 23, 23, 255 };
	const Vector::Vector2<uint32> windowViewport{ 920 , 360 };
	const Window::WindowStruct windowStruct { windowViewport, windowTitle.size(), windowTitle.data(), windowColor };

	// Models
	Surface::Circle circleSurface1 { 30 };
	Surface::Square squareSurface1 { 60, 60 };

	// Prefabs
	const Entity::PlayerCircle prefabPlayerCircle { Transform::zero, circleSurface1, { 30 }, { Moveable::GetRandomAngleForce(80.0f) } };
	const Entity::PlayerSquare prefabPlayerSquare { Transform::zero, squareSurface1, { 60, 60 }, { Moveable::GetRandomAngleForce(80.0f) } };

	// Initial Entity Buffor
	Entity::EntitiesBuffor entitiesBuffor(Entity::CreateEntitiesBuffor(100));
	Entity::CreateEntitiesCPY<Entity::PlayerCircle>(entitiesBuffor, prefabPlayerCircle, 1);
	Entity::CreateEntitiesCPY<Entity::PlayerSquare>(entitiesBuffor, prefabPlayerSquare, 1, 1);

	{ // Game
		MainWindow mainWindow;
		Renderer mainRenderer;
		Game::Create(windowStruct, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC, mainWindow, mainRenderer);
		Game::MainLoop(mainRenderer, windowStruct.backgroundColor, entitiesBuffor, entitiesBuffor.data());
		Game::Destroy(mainWindow, mainRenderer);
	}

	// Clear Entity Buffor
	Entity::DeleteEntitiesBuffor(entitiesBuffor, 100);

	//array<Object::Object, 2> objects { square1, circle1 };
	//array<Object::Object, 4> objects{ circle1, circle2, circle3, circle4 };
	//array<Object::Object, 16> objects { 
	//	square1, square2,
	//	circle1, circle2, circle3, circle4, circle5, circle6, circle7, circle8,
	//	circle9, circle10, circle11, circle12, circle13, circle14
	//};

	return 0;
}