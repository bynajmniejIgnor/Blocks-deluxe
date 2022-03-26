#include <stdio.h>
#include <SDL.h>

typedef struct cell{
	SDL_Rect r;
	int val;
}cell;

int longBoi[4][4]={
	1,1,1,1,
	0,0,0,0,
	0,0,0,0,
	0,0,0,0
};
int revL[4][4]={
	2,0,0,0,
	2,2,2,2,
	0,0,0,0,
	0,0,0,0
};
int L[4][4]={
	0,0,0,3,
	3,3,3,3,
	0,0,0,0,
	0,0,0,0
};
int square[4][4]={
	4,4,0,0,
	4,4,0,0,
	0,0,0,0,
	0,0,0,0
};
int revZigzag[4][4]={
	0,5,5,0,
	5,5,0,0,
	0,0,0,0,
	0,0,0,0
};
int T[4][4]={
	0,6,0,0,
	6,6,6,0,
	0,0,0,0,
	0,0,0,0
};
int zigzag[4][4]={
	7,7,0,0,
	0,7,7,0,
	0,0,0,0,
	0,0,0,0
};

void drawBackground(SDL_Renderer* renderer, SDL_Rect backgr){
	SDL_SetRenderDrawColor(renderer,255,255,255,150);
	SDL_RenderFillRect(renderer,&backgr);
}

cell board[20][10];
int cellSize=40;
void initBoard(SDL_Renderer* renderer, float origin[]){
	for(int y=0; y<20; y++){
		for(int x=0; x<10; x++){
			board[y][x].r.w=cellSize;
			board[y][x].r.h=cellSize;
			board[y][x].r.x=10+origin[0]+42*x;
			board[y][x].r.y=10+origin[1]+42*y;
		}
	}
}
void updateBoard(SDL_Renderer* renderer){
	for(int y=0; y<20; y++){
		for(int x=0; x<10; x++){
			switch(board[y][x].val){
				case 1:
					SDL_SetRenderDrawColor(renderer,0,255,255,255); //cyan long boi
					break;
				case 2:
					SDL_SetRenderDrawColor(renderer,0,0,255,255); //blue rev L
					break;
				case 3:
					SDL_SetRenderDrawColor(renderer,255,144,0,255); //orange L
					break;
				case 4:
					SDL_SetRenderDrawColor(renderer,255,255,0,255); //yellow square
					break;
				case 5:
					SDL_SetRenderDrawColor(renderer,0,255,0,255); //green zgigzag
					break;
				case 6:
					SDL_SetRenderDrawColor(renderer,255,0,255,255); //purple T
					break;
				case 7:
					SDL_SetRenderDrawColor(renderer,255,0,0,255); //red zigzag
					break;
				case 0:
					break;
			}
			SDL_RenderFillRect(renderer,&board[y][x].r);
			SDL_SetRenderDrawColor(renderer,0,0,0,255);

		}
	}
}

void spawnTetrimino(int tetrimino[4][4], int y, int x){
	for(int i=0; i<4; i++){
		for(int j=0; j<4; j++){
			board[y+i][x+j].val=tetrimino[i][j];
		}
	}
}
int main(int argc, char* args[]){
	SDL_Init(SDL_INIT_EVERYTHING);

	int windowWidth=700;
	int windowHeight=900;
	SDL_Window *window=SDL_CreateWindow("Competitive blocks...",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,windowWidth,windowHeight,SDL_WINDOW_SHOWN);
	SDL_Renderer *renderer=SDL_CreateRenderer(window,-1,0);
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

	SDL_Event event;
	int running=1;

	SDL_Rect background;
	int backgroundWidth=440, backgroundHeight=860;
	float origin[2]={(windowWidth-backgroundWidth)/2.0f,(windowHeight-backgroundHeight)/2.0f};
	background.w=backgroundWidth;
	background.h=backgroundHeight;
	background.x=origin[0];
	background.y=origin[1];

	initBoard(renderer,origin);

	spawnTetrimino(longBoi,0,0);
	spawnTetrimino(revL,2,5);
	spawnTetrimino(L,5,1);
	spawnTetrimino(square,7,8);
	spawnTetrimino(revZigzag,10,0);
	spawnTetrimino(T,12,5);
	spawnTetrimino(zigzag,15,3);

	while(running){
		SDL_PollEvent(&event);
		switch(event.type){
			case SDL_QUIT:
				running=0;
				break;
			case SDL_KEYDOWN:
				switch(event.key.keysym.sym){
					case SDLK_SPACE:
						printf("Space pressed\n");
						break;
					case SDLK_ESCAPE:
						running=0;
						break;
				}
				break;
			default:
				break;
		}
		SDL_SetRenderDrawColor(renderer,0,0,0,255);
		SDL_RenderClear(renderer);
		drawBackground(renderer,background);
		updateBoard(renderer);
		SDL_RenderPresent(renderer);
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}