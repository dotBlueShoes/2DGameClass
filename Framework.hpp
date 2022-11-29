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

// QUICK DEBUG
//#include <iostream>
//#include <fstream>

#define block inline void
#define getter constexpr auto

using std::array;
using std::vector;
using size = size_t;
using uint32 = uint32_t;
using uint64 = uint64_t;
using int32 = int32_t;
using int64 = int64_t;
using uint8 = uint8_t;
using int8 = int8_t;

using MainWindow = SDL_Window*;
using Renderer = SDL_Renderer*;
using Rectangle = SDL_Rect;

//using ErrorCode = int;

//template <size count>
//using string = array<const char, count>;