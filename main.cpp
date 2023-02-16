#include "Framework.hpp"
#include "Window.hpp"
#include "Game.hpp"

#include "Entity.hpp"
#include "Entities/EntityPlayerCircle.hpp"
#include "Entities/EntityPlayerSquare.hpp"

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

	// Models
	Surface::Circle circleSurface1 { 30 };
	Surface::Square squareSurface1 { 60, 60 };

	// Prefabs
	prefab Entity::PlayerCircle prefabPlayerCircle { Transform::zero, circleSurface1, { 30 }, { Moveable::GetRandomAngleForce(80.0f) } };
	// - we know 1 st element is ( Transform::Transform Surface::Circle Collision::CircleCollision Moveable::MoveData )
	const Entity::PlayerSquare prefabPlayerSquare { Transform::zero, squareSurface1, { 60, 60 }, { Moveable::GetRandomAngleForce(80.0f) } };
	// - we know 2 st element is ( Transform::Transform Surface::Square Collision::SquareCollision Moveable::MoveData )

	// Initial Entity Buffor
	size entitiesBufforLength(2);
	Entity::EntitiesBuffor entitiesBuffor(Entity::CreateEntitiesBuffor(entitiesBufforLength));
	Entity::CreateEntitiesCPY<Entity::PlayerCircle>(entitiesBuffor, prefabPlayerCircle, 1);
	Entity::CreateEntitiesCPY<Entity::PlayerSquare>(entitiesBuffor, prefabPlayerSquare, 1, 1);

	//for (size i = 0; i < entitiesBufforLength; i++) {
	//	auto entity = (Entity::PlayerCircle*)(entitiesBuffor[i]);
	//	auto& position = entity->transform.position;
	//	Log::Info("Position: %f, %f", position.x, position.y);
	//}

	size entitiesBufforOtherLength(1);
	Entity::EntitiesBuffor entitiesBufforOther(Entity::CreateEntitiesBuffor(entitiesBufforOtherLength));
	Entity::CreateEntitiesCPY<Entity::PlayerCircle>(entitiesBufforOther, prefabPlayerCircle, 1);
	Entity::Link(entitiesBuffor, entitiesBufforLength, entitiesBufforOther);

	//for (size i = 0; i < entitiesBufforOtherLength; i++) {
	//	auto entity = (Entity::PlayerCircle*)(entitiesBufforOther[i]);
	//	auto& position = entity->transform.position;
	//	Log::Info("Position: %f, %f", position.x, position.y);
	//}

	{ // Game
		MainWindow mainWindow;
		Renderer mainRenderer;
		Game::Create(windowStruct, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC, mainWindow, mainRenderer);
		Game::MainLoop(mainRenderer, windowStruct.backgroundColor, entitiesBufforLength, entitiesBuffor);
		Game::Destroy(mainWindow, mainRenderer);
	}

	// Clear Entity Buffor
	Entity::DeleteEntitiesBuffor(entitiesBufforOther);
	Entity::DeleteEntitiesBuffor(entitiesBuffor);

	//array<Object::Object, 2> objects { square1, circle1 };
	//array<Object::Object, 4> objects{ circle1, circle2, circle3, circle4 };
	//array<Object::Object, 16> objects { 
	//	square1, square2,
	//	circle1, circle2, circle3, circle4, circle5, circle6, circle7, circle8,
	//	circle9, circle10, circle11, circle12, circle13, circle14
	//};

	return 0;
}