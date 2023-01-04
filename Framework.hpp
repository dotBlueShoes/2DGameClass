#pragma once

// SDL Libraries
#pragma warning(disable:26812)
#include <SDL.h>
#include <SDL_image.h>
#pragma warning(default:26812)

// Standard Libraries
#include <cassert>
#include <array>
#include <vector>

#include <inttypes.h> // for the print macros

// QUICK DEBUG
//#include <iostream>
//#include <fstream>

#define block inline void
#define getter [[nodiscard]] constexpr auto

using std::array;
using std::vector;
using size = size_t;
using uint32 = uint32_t;
using uint64 = uint64_t;
using int32 = int32_t;
using int64 = int64_t;
using uint8 = uint8_t;
using int8 = int8_t;
using sint32 = int32_t;
using any = void*;

using character = const char;

using MainWindow = SDL_Window*;
using Renderer = SDL_Renderer*;
using Rectangle = SDL_Rect;
using TSurface = SDL_Surface*;
using Texture = SDL_Texture*;


#ifdef NDEBUG
const bool debugLayer = false;
#endif
#ifndef NDEBUG
const bool debugLayer = true;
#endif

#define DEBUG if constexpr (debugLayer)