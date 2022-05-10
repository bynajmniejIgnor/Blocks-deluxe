#ifndef GUARD_board_h
#define GUARD_board_h
#ifdef _WIN32
#include <SDL.h>
#else
#include "SDL2/SDL.h"
#endif
#define ROWS 22
#define COLS 10
struct cell {	SDL_Rect r;	int val; };

extern void clear(int y, int x, int color, struct cell board[ROWS][COLS]);
extern void init_board(float origin[], struct cell board[ROWS][COLS]);
extern void settle(int y, int x, struct cell board[ROWS][COLS]);
extern void move_block(char d,struct cell board[ROWS][COLS]);
extern void spawn_tetronimo(int tetromino[4][4], int y, int x, struct cell board[ROWS][COLS]);

extern int is_falling(struct cell board[ROWS][COLS]);
extern int touch_wall_left(struct cell board[ROWS][COLS]);
extern int touch_wall_right(struct cell board[ROWS][COLS]);
#endif

