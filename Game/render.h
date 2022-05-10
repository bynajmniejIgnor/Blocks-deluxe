#ifdef _WIN32
#include <SDL.h>
#else
#include "SDL2/SDL.h"
#endif

#ifndef GUARD_blocks_h
#define GUARD_blocks_h
extern void draw_background(SDL_Renderer* renderer, SDL_Rect backgr);
extern int end_game(SDL_Renderer* renderer, SDL_Window* window);
#endif
