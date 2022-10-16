#include "Framework.hpp"
#include "Game.hpp"

// TODO
// see gpu_sdl https://github.com/grimfang4/sdl-gpu
// hold information about vsync, fullscreen outside game namespace.
// struct Updatable - holds function which contents are being executed inside MainUpdate. // z-layer issue
// struct 2DSprite
// struct 2DSpriteAnimation - holds textures and rects for their destination look.
// NO / struct GameObject / lets keep them in namespaces.
// namespace Player{}; namespace PigsSwarm{};
// Time, EaseIn, FixedLogicUpdate, 

ErrorCode SDL_main(int argc, char** argv) {

	const array<const char, 25> gameTitle { "2DGry-242539-Polecenie-2" };
	const Color grayColor { 23, 23, 23, 0 };

	Game::backgroundColor = grayColor;
	Game::Create(gameTitle.data(), gameTitle.size());

	// Initializing GameObjects
	Player::Create(Game::mainRenderer);
	Key::Create(Game::mainRenderer);
	Player2::Create();
	// ...

	Game::MainLoop();

	// Destroing GameObjects
	Key::Destroy();
	Player::Destroy();
	// ...

	Game::Destroy();

	return success;
}