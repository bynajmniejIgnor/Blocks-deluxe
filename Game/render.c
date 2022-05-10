#ifdef _WIN32
#include <SDL.h>
#else
#include "SDL2/SDL.h"
#endif

#include "render.h"

void draw_background(SDL_Renderer* renderer, SDL_Rect backgr){
	SDL_SetRenderDrawColor(renderer,255,255,255,150);
	SDL_RenderFillRect(renderer,&backgr);
}

int end_game(SDL_Renderer* renderer, SDL_Window* window) {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}
