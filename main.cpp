#include "Framework.hpp"
#include "Game.hpp"
#include "Player.hpp"
#include "Key.hpp"

// TODO
// see gpu_sdl https://github.com/grimfang4/sdl-gpu
// hold information about vsync, fullscreen outside game namespace.
// struct Updatable - holds function which contents are being executed inside MainUpdate. // z-layer issue
// struct 2DSprite
// struct 2DSpriteAnimation - holds textures and rects for their destination look.
// NO / struct GameObject / lets keep them in namespaces.
// namespace Player{}; namespace PigsSwarm{};

ErrorCode SDL_main(int argc, char** argv) {

	const array<const char, 25> gameTitle { "2DGry-242539-Polecenie-1" };
	const Color grayColor(23, 23, 23);

	Game::Initialize(gameTitle.data(), gameTitle.size(), grayColor);

	// Initializing GameObjects
	Player::Initialize(Game::mainRenderer);
	Key::Initialize(Game::mainRenderer);
	// ...

	Game::MainLoop();

	// Destroing GameObjects
	Key::Destroy();
	Player::Destroy();
	// ...

	Game::Destroy();

	return success;
}