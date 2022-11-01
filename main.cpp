#include "Framework.hpp"
#include "Game.hpp"
#include "Map.hpp"

// Links
// https://www.youtube.com/watch?v=1eaxE_waDNc
// https://stackoverflow.com/questions/18591758/sdl2-tilemap-too-slow
// https://www.reddit.com/r/gamedev/comments/3y1va8/sdl2_c_tile_map_most_efficient_way_to_render_lots/

// TODO
// see gpu_sdl https://github.com/grimfang4/sdl-gpu
// hold information about vsync, fullscreen outside game namespace.
// struct Updatable - holds function which contents are being executed inside MainUpdate. // z-layer issue
// struct 2DSprite
// struct 2DSpriteAnimation - holds textures and rects for their destination look.
// NO / struct GameObject / lets keep them in namespaces.
// namespace Player{}; namespace PigsSwarm{};
// FixedLogicUpdate, 
// Have structs required for function use (said modules)

ErrorCode SDL_main(int argc, char** argv) {

	const array<const char, 25> gameTitle { "2DGry-242539-Polecenie-3" };
	const Color grayColor { 23, 23, 23, 0 };
	const Vector2<int> screenSize{ 920 , 360 };

	Game::backgroundColor = grayColor;
	Game::Create(screenSize, gameTitle.data(), gameTitle.size());

	// Initializing GameObjects
	Player::Create(Game::mainRenderer);
	Key::Create(Game::mainRenderer);
	Player2::Create();
	Map::Create(Game::mainRenderer);

	const char* mapFile1("assets/maps/1.map");
	const char* mapFile2("assets/maps/2.map");

	std::ifstream file(mapFile1);

	std::string buffor, temp;

	while (std::getline(file, temp)) {
		buffor += temp;
		buffor += '\n';
	}

	Map::LoadMapFromString(buffor.c_str());
	file.close();

	// ...

	Game::MainLoop();

	// Destroing GameObjects
	Map::Destroy();
	Key::Destroy();
	Player::Destroy();
	// ...

	Game::Destroy();

	return success;
}