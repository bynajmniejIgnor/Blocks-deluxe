#ifdef _WIN32
#include <SDL.h>
#else
#include "SDL2/SDL.h"
#endif

#ifndef GUARD_render_h
#define GUARD_render_h
void draw_background(SDL_Renderer* renderer, SDL_Rect backgr);
int end_game(SDL_Renderer* renderer, SDL_Window* window);
#endif
