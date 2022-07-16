#ifndef WORLD2D_LUA_STRUCTURES_GAMECONTROLLER_H
#define WORLD2d_LUA_STRUCTURES_GAMECONTROLLER_H

#include "SDL/SDL_gamecontroller.h"

namespace world2d {
	struct GameController {
		int index;
		SDL_GameController* joy;
	};
}

#endif