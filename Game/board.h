#ifdef _WIN32
#include <SDL.h>
#else
#include "SDL2/SDL.h"
#endif
#define ROWS 22
#define COLS 10
#ifndef GUARD_board_h
#define GUARD_board_h
struct cell {	SDL_Rect r;	int val; };

void clear(int, int, int, struct cell[ROWS][COLS]);
void init_board(float origin[], struct cell board[ROWS][COLS]);
void settle(int y, int x, struct cell board[ROWS][COLS]);
void move_block(char,struct cell[ROWS][COLS]);
void spawn_tetronimo(int[4][4], int, int, struct cell[ROWS][COLS]);

int is_falling(struct cell[ROWS][COLS]);
int touch_wall_left(struct cell[ROWS][COLS]);
int touch_wall_right(struct cell[ROWS][COLS]);
#endif

