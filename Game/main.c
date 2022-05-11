#include "blocks.h"
#include "render.h"
#include "board.h"

#ifdef _WIN32
#include <SDL.h>
#else
#include "SDL2/SDL.h"
#endif

#include <stdio.h>
#include <time.h>

#define	windowWidth 700
#define windowHeight 900
#define backgroundWidth 440
#define backgroundHeight 860

#define ROWS 22
#define COLS 10

typedef struct cycles {
	int I;
	int J;
	int L;
	int S;
	int T;
	int Z;
} cycles;

cycles cycle_counter = {
	.I = 1,
	.J = 1,
	.L = 1,
	.S = 1,
	.T = 1,
	.Z = 1,
};

struct cell board[ROWS][COLS];

int s[4];
int cell_size=40;
int running=1;
int previous=-1;
int gravity_tick=500;
int ticker=0;
int score=0;

unsigned int lastTime=0, currentTime;

void write_to_file() {
	char name[256];
	FILE* file = fopen("Scores.txt", "a");
	time_t t = time(NULL);
  struct tm tm = *localtime(&t);

	printf("What is your name?:\n");
 	fgets(name, sizeof(name), stdin);

	fprintf(file,"Name: %s",name);
  fprintf(file,"Date: %d-%02d-%02d %02d:%02d:%02d\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
	fprintf(file,"Score: %d\n\n",score);
	printf("Your score has been written to a file!\n");
	return;
}

void update_board(SDL_Renderer* renderer){
	for(int y=2; y<ROWS; y++){
		for(int x=0; x<COLS; x++){
			for (int i=0;i<5;i++) s[i] = COLORS[board[y][x].val][i];
			SDL_SetRenderDrawColor(renderer, s[0], s[1], s[2], s[3]);
			SDL_RenderFillRect(renderer,&board[y][x].r);
			SDL_SetRenderDrawColor(renderer,0,0,0,255);
		}
	}
}

void spawn_random_tetronimo(SDL_Renderer* renderer, SDL_Window* window){
	if (is_falling(board)) return;
	for(int i=0; i<4; i++) for(int j=0; j<4; j++)	if(board[1+i][3+j].val!=0) running = end_game(renderer,window);

	int r = rand()%7;
	while (r==previous) r=rand()%7;
	previous = r;

	switch(r){
		case 0:
			for(int i=0; i<4; i++){
				for(int j=0; j<4; j++){
					board[1+i][3+j].val=I_BLOCK[i][j];
				}
			}
			break;
		case 1:
			for(int i=0; i<4; i++){
				for(int j=0; j<4; j++){
					board[1+i][3+j].val=J_BLOCK[i][j];
				}
			}
			break;
		case 2:
			for(int i=0; i<4; i++){
				for(int j=0; j<4; j++){
					board[1+i][3+j].val=L_BLOCK[i][j];
				}
			}
			break;
		case 3:
			for(int i=0; i<4; i++){
				for(int j=0; j<4; j++){
					board[1+i][3+j].val=O_BLOCK[i][j];
				}
			}
			break;
		case 4:
			for(int i=0; i<4; i++){
				for(int j=0; j<4; j++){
					board[1+i][3+j].val=S_BLOCK[i][j];
				}
			}
			break;
		case 5:
			for(int i=0; i<4; i++){
				for(int j=0; j<4; j++){
					board[1+i][3+j].val=T_BLOCK[i][j];
				}
			}
			break;
		case 6:
			for(int i=0; i<4; i++){
				for(int j=0; j<4; j++){
					board[1+i][3+j].val=Z_BLOCK[i][j];
				}
			}
			break;
	}
	cycle_counter.I=1;
	cycle_counter.J=1;
	cycle_counter.S=1;
	cycle_counter.L=1;
	cycle_counter.T=1;
	cycle_counter.Z=1;
}

void rotate(){
	if(!is_falling(board)) return;

	int x, y, found=0;
	int color;
	for(int i=0; i<ROWS-1; i++){
		for(int j=0; j<COLS; j++){
			if(board[i][j].val<8 && board[i][j].val){
				color=board[i][j].val;
				y=i;
				x=j;
				found=1;
				break;
			}
		}
		if(found) break;
	}
	if(color==4) return;

	for(int i=0; i<4; i++){
		for(int j=0; j<4; j++){
			if(board[y+i][x+j].val!=0 && board[y+i][x+j].val!=color) return;
		}
	}
	clear(y,x,color,board);
	switch(color){
		case 1:
			spawn_tetronimo(I_BLOCK_CYCLE[cycle_counter.I],y,x,board);
			cycle_counter.I = (cycle_counter.I) ? 0 : 1;
			break;
		case 2:
			spawn_tetronimo(J_BLOCK_CYCLE[cycle_counter.J],y,x,board);
			cycle_counter.J++;
			if (cycle_counter.J==4) cycle_counter.J=0;
			break;
		case 3:
			spawn_tetronimo(L_BLOCK_CYCLE[cycle_counter.L],y,x,board);
			cycle_counter.L++;
			if (cycle_counter.L==4) cycle_counter.L=0;
			break;
		case 5:
			spawn_tetronimo(S_BLOCK_CYCLE[cycle_counter.S],y,x,board);
			cycle_counter.S = (cycle_counter.S) ? 0 : 1;
			break;
		case 6:
			spawn_tetronimo(T_BLOCK_CYCLE[cycle_counter.T],y,x,board);
			cycle_counter.T++;
			if (cycle_counter.T==4) cycle_counter.T=0;
			break;
		case 7:
			spawn_tetronimo(Z_BLOCK_CYCLE[cycle_counter.Z],y,x,board);
			cycle_counter.Z = (cycle_counter.Z) ? 0 : 1;
			break;
	}
}

void clear_block(){
	for(int i=ROWS-1; i>0; i--){
		int toClear=1;
		for(int j=0; j<COLS; j++){
			if(board[i][j].val<8) {
				toClear=0;
				break;
			}
		}
		if(toClear){
			ticker++;
			score+=100;
			for(int a=i; a>0; a--){
				for(int j=0; j<COLS; j++){
					board[a][j].val=board[a-1][j].val;
					board[a-1][j].val=0;
				}
			}
		}
	}
	if(ticker==5){
		gravity_tick/=1.2;
		ticker=0;
	}
}

void gravity(SDL_Renderer* renderer, SDL_Window* window){
	clear_block();
	//SETTLE BLOCKS THAT TOUCH THE FLOOR
	for(int j=0; j<COLS; j++){
		if(board[ROWS-1][j].val!=0){
			settle(ROWS-1,j,board);
		}
	}

	//SETTLE BLOCKS THAT TOUCH SETTLED BLOCKS
	for(int i=20; i>1; i--){
		for(int j=0; j<COLS; j++){
			if(board[i+1][j].val!=board[i][j].val && board[i+1][j].val!=0){
				settle(i,j,board);
			}
		}
	}

	for(int i=ROWS-1; i>1; i--){
		for(int j=0; j<COLS; j++){
			if(board[i-1][j].val>=8 || board[i][j].val!=0){
				continue;
			}
			board[i][j].val=board[i-1][j].val;
			board[i-1][j].val=0;
		}
	}
	spawn_random_tetronimo(renderer,window);
}

void time_gravity(SDL_Renderer* renderer, SDL_Window* window){
	currentTime = SDL_GetTicks();
	if (currentTime>lastTime+gravity_tick) {
		gravity(renderer, window);
		lastTime = currentTime;
	}
}

int main(int argc, char* args[]){
	srand(time(NULL));
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Window *window=SDL_CreateWindow("Competitive blocks...",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,windowWidth,windowHeight,SDL_WINDOW_SHOWN);
	SDL_Renderer *renderer=SDL_CreateRenderer(window,-1,0);
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

	SDL_Event event;

	SDL_Rect background;
	float origin[2]={(windowWidth-backgroundWidth)/2.0f,(windowHeight-backgroundHeight)/2.0f};
	background.w=backgroundWidth;
	background.h=backgroundHeight;
	background.x=origin[0];
	background.y=origin[1];

	init_board(origin, board);
	while(running){
		SDL_PollEvent(&event);
		time_gravity(renderer, window);
		switch(event.type){
			case SDL_QUIT:
				running=0;
				break;
			case SDL_KEYDOWN:
				switch(event.key.keysym.sym){
					case SDLK_ESCAPE:
						running=0;
						break;
					case SDLK_LEFT:
						move_block('l',board);
						break;
					case SDLK_RIGHT:
						move_block('r',board);
						break;
					case SDLK_UP:
						rotate();
						break;
					case SDLK_DOWN:
						gravity(renderer, window);
						break;
					case SDLK_SPACE:
						gravity_tick/=2;
						break;
				}
				break;
			default:
				break;
		}

		//----------------------------RENDER----------------------------//
		//-------------------------------------------------------------//
		SDL_SetRenderDrawColor(renderer,0,0,0,255);
		SDL_RenderClear(renderer);
		draw_background(renderer,background);
		update_board(renderer);
		SDL_RenderPresent(renderer);
	}
	end_game(renderer,window);
	printf("You lost!\n");
	printf("Score %d\n",score);
	if (score) write_to_file();
	return 0;
}
