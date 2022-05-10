#ifdef _WIN32
#include <SDL.h>
#else
#include "SDL2/SDL.h"
#endif

#include "board.h"
#define ROWS 22
#define COLS 10

void clear(int y, int x, int color, struct cell board[ROWS][COLS]){
	if(board[y][x].val!=color) return;
	board[y][x].val=0;
	clear(y-1,x,color, board);
	clear(y+1,x,color, board);
	clear(y,x-1,color, board);
	clear(y,x+1,color, board);
}

void init_board(float origin[], struct cell board[ROWS][COLS]){
	for(int y=0; y<ROWS; y++){
		for(int x=0; x<COLS; x++){
			board[y][x].r.w=40;
			board[y][x].r.h=40;
			board[y][x].r.x=10+origin[0]+42.0f*x;
			board[y][x].r.y=-83+10+origin[1]+42.0f*y;
		}
	}
}

void settle(int y, int x, struct cell board[ROWS][COLS]){
	if(board[y][x].val==0 || board[y][x].val>=8){
		return;
	}
	board[y][x].val+=8;
	settle(y-1,x,board);
	settle(y+1,x,board);
	settle(y,x+1,board);
	settle(y,x-1,board);
}

int is_falling(struct cell board[ROWS][COLS]){
	for(int i=0; i<ROWS-1; i++)	for(int j=0; j<COLS; j++)	if(board[i][j].val>0 && board[i][j].val<8) return 1;
	return 0;
}

int touch_wall_left(struct cell board[ROWS][COLS]) {
	for(int i=0; i<ROWS-1; i++)	if(board[i][0].val>0 && board[i][0].val<8) return 1;
	return 0;
}

int touch_wall_right(struct cell board[ROWS][COLS]) {
	for(int i=0; i<ROWS-1; i++)	if(board[i][9].val>0 && board[i][9].val<8) return 1;
	return 0;
}

void move_block(char d,struct cell board[ROWS][COLS]){
	switch(d){
		case 'l':
			if(touch_wall_left(board)) break;
			for(int j=1; j<COLS; j++){
				for(int i=0; i<ROWS-1; i++){
					if(board[i][j].val && board[i][j].val<8){
						if(board[i][j-1].val>8) return;
						int index=i+1;
						while(board[index][j].val==board[i][j].val){
							if(board[index][j-1].val>8) return;
							index++;
						}
						board[i][j-1].val=board[i][j].val;
						board[i][j].val=0;
					}
				}
			}
			break;
		case 'r':
			if(touch_wall_right(board)) break;
			for(int j=8; j>=0; j--){
				for(int i=0; i<ROWS-1; i++){
					if(board[i][j].val && board[i][j].val<8){
						if(board[i][j+1].val>8) return;
						int index=i+1;
						while(board[index][j].val==board[i][j].val){
							if(board[index][j+1].val>8) return;
							index++;
						}
						board[i][j+1].val=board[i][j].val;
						board[i][j].val=0;
					}
				}
			}
			break;
	}
}

void spawn_tetronimo(int tetromino[4][4], int y, int x, struct cell board[ROWS][COLS]){
	for(int i=0; i<4; i++){
		for(int j=0; j<4; j++){
			if(board[y+i][x+j].val!=0) continue;
			board[y+i][x+j].val=tetromino[i][j];
		}
	}
}


