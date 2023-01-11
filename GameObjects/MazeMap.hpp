#pragma once
#include "../Framework.hpp"
#include "../Math/Math.hpp"
#include "../File.hpp"

namespace GameObjects::MazeMap {

	//const char const sampleStringMap[] {
	//	'0', '0', '0', '\n',
	//	'0', '1', '0', '\n',
	//	'0', '0', '0', '\n',
	//	'\n'
	//};

	struct Sprite {
		Rectangle spriteTransform;
	};

	struct TextureAtlas {
		Texture texture;
		int tileSize;
		size spritesCount;
		Sprite* sprites;
	};

	struct Map {
		Vector::Vector2<float> position; // offset?
		TextureAtlas textureAtlas;
		Vector::Vector2<uint8> extent; // - board 2dim count
		uint8* board;
	};

	TextureAtlas CreateTextureAtlas(Renderer& renderer, const size& spritesCount, const int& tileSize, const char* textureFilePath) {

		TSurface surface(IMG_Load(textureFilePath));

		DEBUG if (surface == nullptr) {
			Log::Error("Unable to load TILEMAP TEXTURE!");
			//return nullptr;
		}

		Texture texture = SDL_CreateTextureFromSurface(renderer, surface);
		SDL_FreeSurface(surface);

		DEBUG if (texture == nullptr) {
			Log::Error("Unable to load CREATE TILEMAP TEXTURE!");
			//return nullptr;
		}

		Sprite* sprites = new Sprite[spritesCount];

		// 192x192 sprite_atlas
		// 64x64 sprite

		sprites[0].spriteTransform.x = 0 * tileSize;
		sprites[0].spriteTransform.y = 0 * tileSize;
		sprites[0].spriteTransform.w = 1 * tileSize;
		sprites[0].spriteTransform.h = 1 * tileSize;

		sprites[1].spriteTransform.x = 1 * tileSize;
		sprites[1].spriteTransform.y = 0 * tileSize;
		sprites[1].spriteTransform.w = 1 * tileSize;
		sprites[1].spriteTransform.h = 1 * tileSize;

		sprites[2].spriteTransform.x = 2 * tileSize;
		sprites[2].spriteTransform.y = 0 * tileSize;
		sprites[2].spriteTransform.w = 1 * tileSize;
		sprites[2].spriteTransform.h = 1 * tileSize;

		sprites[3].spriteTransform.x = 3 * tileSize;
		sprites[3].spriteTransform.y = 0 * tileSize;
		sprites[3].spriteTransform.w = 1 * tileSize;
		sprites[3].spriteTransform.h = 1 * tileSize;

		sprites[4].spriteTransform.x = 0 * tileSize;
		sprites[4].spriteTransform.y = 1 * tileSize;
		sprites[4].spriteTransform.w = 1 * tileSize;
		sprites[4].spriteTransform.h = 1 * tileSize;

		sprites[5].spriteTransform.x = 1 * tileSize;
		sprites[5].spriteTransform.y = 1 * tileSize;
		sprites[5].spriteTransform.w = 1 * tileSize;
		sprites[5].spriteTransform.h = 1 * tileSize;

		sprites[6].spriteTransform.x = 2 * tileSize;
		sprites[6].spriteTransform.y = 1 * tileSize;
		sprites[6].spriteTransform.w = 1 * tileSize;
		sprites[6].spriteTransform.h = 1 * tileSize;

		sprites[7].spriteTransform.x = 3 * tileSize;
		sprites[7].spriteTransform.y = 1 * tileSize;
		sprites[7].spriteTransform.w = 1 * tileSize;
		sprites[7].spriteTransform.h = 1 * tileSize;

		return TextureAtlas{ texture, tileSize, spritesCount, sprites };
	}

	Map CreateMapFromFile(
		const Vector::Vector2<float>& position,
		const TextureAtlas& textureAtlas, 
		const char* mapFilePath
	) {

		std::string buffor;

		File::Read(buffor, mapFilePath);
		//DEBUG Log::Info("Map Read:\n%s", buffor.c_str());

		uint8* board = new uint8[buffor.size()];
		
		
		uint8 rowSize = 0;
		for (; buffor[rowSize] != '\n'; rowSize++);

		uint32 inputIndex = 0;
		uint32 mapIndex = 0;
		while (buffor[inputIndex] != '\0') {
			for (; buffor[inputIndex] != '\n'; inputIndex++) {
				switch (buffor[inputIndex]) {
					case '0': { board[mapIndex] = 0; break; }
					case '1': { board[mapIndex] = 1; break; }
					case '2': { board[mapIndex] = 2; break; }
					case '3': { board[mapIndex] = 3; break; }
					default: { 
						board[mapIndex] = 0; 
						DEBUG Log::Error("Map Load Error: %i, %d", inputIndex, buffor[inputIndex]);
					}
				}
				mapIndex++;
			}
			inputIndex++;
		}

		DEBUG Log::Info("InputIndex %d, MapIndex %d, RowSize, %d", inputIndex, mapIndex, rowSize);

		return Map { { 0, 0 }, textureAtlas, { rowSize, (uint8)(mapIndex / rowSize) }, board };
	}

	block Render(const Renderer& renderer, const Camera::Camera& camera, const Map& map) {
		//const Vector::Vector2<float> cameraMoveToCenter = Camera::GetCameraScaleMovePosition(camera);
		//const Vector::Vector2<float> startPosition{ ceil((position.x + camera.position.x) * camera.zoom + cameraMoveToCenter.x), ceil((position.y + camera.position.y) * camera.zoom + cameraMoveToCenter.y) };
		//printf("map: %f, %f\n", startPosition.x, startPosition.y);

		const Vector::Vector2<float> startPosition{ ceil(map.position.x - camera.position.x), ceil(map.position.y - camera.position.y) };
		Rectangle tileRenderScreenPosition; // = { 0, 0, map.textureAtlas.tileSize, map.textureAtlas.tileSize };
		tileRenderScreenPosition.x = startPosition.x;
		tileRenderScreenPosition.y = startPosition.y;
		tileRenderScreenPosition.w = ceil(map.textureAtlas.tileSize);
		tileRenderScreenPosition.h = ceil(map.textureAtlas.tileSize);
		for (int y = 0; y < map.extent.y; y++) {
			for (int x = 0; x < map.extent.x; x++) {
				SDL_RenderCopy (
					renderer, 
					map.textureAtlas.texture, 
					&map.textureAtlas.sprites[map.board[x + (y * map.extent.x)]].spriteTransform,
					&tileRenderScreenPosition
				);
				tileRenderScreenPosition.x += tileRenderScreenPosition.w;
			}
			tileRenderScreenPosition.x = startPosition.x;
			tileRenderScreenPosition.y += tileRenderScreenPosition.h;
		}
	}

	block DestroyTextureAtlas(TextureAtlas& tilemapAtlas) {
		delete[] tilemapAtlas.sprites;
		SDL_DestroyTexture(tilemapAtlas.texture);
	}

	block DestroyMap(Map& map) {
		delete[] map.board;
	}

}