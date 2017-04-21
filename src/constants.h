// CONSTANTS.H

#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "SDL_ttf.h"
#include <iostream>
#include <cstdlib>
#include <sstream>
#include <array>
#include <vector>
#include <chrono>
using std::stringstream;
using std::array;
using std::vector;
using std::string;
using std::cout;
using std::endl;

const int SCREEN_WIDTH = 700;
const int SCREEN_HEIGHT = 700;
const int BALLOON_WIDTH = 140;
const int BALLOON_HEIGHT = 190;

struct plot {
	float x;
	float y;
};