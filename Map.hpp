#pragma once
#include "Framework.hpp" 

#include "Camera.hpp"

namespace Map {

	// TEXTURE ATLAS MAP
	SDL_Texture* textureAtlas;

	const int spritesNumber = 8;
	SDL_Rect sprites[spritesNumber];

	const int tileSize = 32;

	// tilemap position on the world
	SDL_Rect tileRenderScreenPosition = { 0, 0, tileSize, tileSize };

	enum class TileMeaning {
		HorizontalWall = 0,
		VerticalWall = 1,
		ground = 2
	};

	const int mapSizeX = 30;
	const int mapSizeY = 20;

	int map[mapSizeX * mapSizeY];

	const char const sampleMap[] =  {
		'0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '\n',
		'1', '2', '2', '2', '2', '2', '2', '2', '2', '1', '\n',
		'1', '2', '2', '2', '2', '2', '2', '2', '2', '1', '\n',
		'1', '2', '2', '2', '0', '0', '0', '2', '2', '1', '\n',
		'1', '2', '2', '2', '1', '2', '1', '2', '2', '1', '\n',
		'1', '2', '2', '2', '1', '2', '1', '2', '2', '1', '\n',
		'1', '2', '2', '2', '0', '0', '0', '2', '2', '1', '\n',
		'1', '2', '2', '2', '2', '2', '2', '2', '2', '1', '\n',
		'1', '2', '2', '2', '2', '2', '2', '2', '2', '1', '\n',
		'0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '\n',
		'\0'
	};

	const Vector2<float> position { 0, 0 };

	void LoadMapFromString(const char* inputMap) {
		int inputIndex = 0; // range = 111;
		int mapIndex = 0;

		while (inputMap[inputIndex] != '\0') {
			for (; inputMap[inputIndex] != '\n'; inputIndex++) {
				switch (inputMap[inputIndex]) {
					case '0': { map[mapIndex] = 0; break; }
					case '1': { map[mapIndex] = 1; break; }
					case '2': { map[mapIndex] = 2; break; }
					case '3': { map[mapIndex] = 3; break; }
					default : { map[mapIndex] = 0; SDL_Log("Map Load Error %d", inputMap[inputIndex]); }
				}
				mapIndex++;
			}
			inputIndex++;
			//SDL_Log("input %d, map %d", inputIndex, mapIndex);
		}
	}

	ErrorCode Create(SDL_Renderer* renderer) {
		SDL_Surface* tempSurface(IMG_Load("assets/tilemap.png"));
		textureAtlas = SDL_CreateTextureFromSurface(renderer, tempSurface);
		SDL_FreeSurface(tempSurface);

		if (textureAtlas == nullptr) SDL_Log("Unable to load Player Texture");

		// 192x192 sprite_atlas
		// 64x64 sprite

		sprites[0].x = 0;
		sprites[0].y = 0;
		sprites[0].w = 32;
		sprites[0].h = 32;

		sprites[1].x = 32;
		sprites[1].y = 0;
		sprites[1].w = 32;
		sprites[1].h = 32;

		sprites[2].x = 64;
		sprites[2].y = 0;
		sprites[2].w = 32;
		sprites[2].h = 32;

		sprites[3].x = 96;
		sprites[3].y = 0;
		sprites[3].w = 32;
		sprites[3].h = 32;

		sprites[4].x = 0;
		sprites[4].y = 32;
		sprites[4].w = 32;
		sprites[4].h = 32;

		sprites[5].x = 32;
		sprites[5].y = 32;
		sprites[5].w = 32;
		sprites[5].h = 32;

		sprites[6].x = 64;
		sprites[6].y = 32;
		sprites[6].w = 32;
		sprites[6].h = 32;

		sprites[7].x = 96;
		sprites[7].y = 32;
		sprites[7].w = 32;
		sprites[7].h = 32;

		return success;
	}

	ErrorCode Destroy() {
		SDL_DestroyTexture(textureAtlas);
		return success;
	}

	void LogicUpdate(const float& deltaTime) {

	}

	ErrorCode RenderUpdate(SDL_Renderer* const renderer, const Camera::Camera& camera) {
		const Vector2<float> cameraMoveToCenter = Camera::GetCameraScaleMovePosition(camera);
		const Vector2<float> startPosition { ceil((position.x + camera.position.x) * camera.zoom + cameraMoveToCenter.x), ceil((position.y + camera.position.y) * camera.zoom + cameraMoveToCenter.y) };
		//printf("map: %f, %f\n", startPosition.x, startPosition.y);
		tileRenderScreenPosition.x = startPosition.x;
		tileRenderScreenPosition.y = startPosition.y;
		tileRenderScreenPosition.w = ceil(tileSize * camera.zoom);
		tileRenderScreenPosition.h = ceil(tileSize * camera.zoom);
		for (int y = 0; y < mapSizeY; y++) {
			for (int x = 0; x < mapSizeX; x++) {
				SDL_RenderCopy(renderer, textureAtlas, &sprites[map[x + (y * mapSizeX)]], &tileRenderScreenPosition);
				tileRenderScreenPosition.x += tileRenderScreenPosition.w;
			}
			tileRenderScreenPosition.x = startPosition.x;
			tileRenderScreenPosition.y += tileRenderScreenPosition.h;
		}	
		return success;
	}

};