#include <stdio.h>
#include <SDL.h>
#include <time.h>

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

int longBoiCycle[2][4][4]={
	1,1,1,1,
	0,0,0,0,
	0,0,0,0,
	0,0,0,0,

	1,0,0,0,
	1,0,0,0,
	1,0,0,0,
	1,0,0,0
};

int revL[4][4]={
	2,0,0,0,
	2,2,2,0,
	0,0,0,0,
	0,0,0,0
};

int revLCycle[4][4][4]={
	2,0,0,0,
	2,2,2,0,
	0,0,0,0,
	0,0,0,0,

	2,2,0,0,
	2,0,0,0,
	2,0,0,0,
	0,0,0,0,

	2,2,2,0,
	0,0,2,0,
	0,0,0,0,
	0,0,0,0,

	0,2,0,0,
	0,2,0,0,
	2,2,0,0,
	0,0,0,0
};
int L[4][4]={
	0,0,3,0,
	3,3,3,0,
	0,0,0,0,
	0,0,0,0
};

int LCycle[4][4][4]={
	0,0,3,0,
	3,3,3,0,
	0,0,0,0,
	0,0,0,0,

	3,0,0,0,
	3,0,0,0,
	3,3,0,0,
	0,0,0,0,

	3,3,3,0,
	3,0,0,0,
	0,0,0,0,
	0,0,0,0,

	3,3,0,0,
	0,3,0,0,
	0,3,0,0,
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

int revZigzagCycle[2][4][4]={
	0,5,5,0,
	5,5,0,0,
	0,0,0,0,
	0,0,0,0,

	5,0,0,0,
	5,5,0,0,
	0,5,0,0,
	0,0,0,0
};
int T[4][4]={
	0,6,0,0,
	6,6,6,0,
	0,0,0,0,
	0,0,0,0
};
int TCycle[4][4][4]={
	0,6,0,0,
	6,6,6,0,
	0,0,0,0,
	0,0,0,0,

	6,0,0,0,
	6,6,0,0,
	6,0,0,0,
	0,0,0,0,

	6,6,6,0,
	0,6,0,0,
	0,0,0,0,
	0,0,0,0,

	0,6,0,0,
	6,6,0,0,
	0,6,0,0,
	0,0,0,0
};
int zigzag[4][4]={
	7,7,0,0,
	0,7,7,0,
	0,0,0,0,
	0,0,0,0
};

int zigzagCycle[2][4][4]={
	7,7,0,0,
	0,7,7,0,
	0,0,0,0,
	0,0,0,0,

	0,7,0,0,
	7,7,0,0,
	7,0,0,0,
	0,0,0,0
};
void drawBackground(SDL_Renderer* renderer, SDL_Rect backgr){
	SDL_SetRenderDrawColor(renderer,255,255,255,150);
	SDL_RenderFillRect(renderer,&backgr);
}

cell board[22][10];
int cellSize=40;

void initBoard(SDL_Renderer* renderer, float origin[]){
	for(int y=0; y<22; y++){
		for(int x=0; x<10; x++){
			board[y][x].r.w=cellSize;
			board[y][x].r.h=cellSize;
			board[y][x].r.x=10+origin[0]+42.0f*x;
			board[y][x].r.y=-83+10+origin[1]+42.0f*y;
		}
	}
}
void updateBoard(SDL_Renderer* renderer){
	for(int y=2; y<22; y++){
		for(int x=0; x<10; x++){
			switch(board[y][x].val){
				case 1:
					SDL_SetRenderDrawColor(renderer,0,255,255,255); //cyan long boi
					break;
				case 9:
					SDL_SetRenderDrawColor(renderer,0,255,255,255); //cyan long boi stable
					break;
				case 2:
					SDL_SetRenderDrawColor(renderer,0,0,255,255); //blue rev L
					break;
				case 10:
					SDL_SetRenderDrawColor(renderer,0,0,255,255); //blue rev L stable
					break;
				case 3:
					SDL_SetRenderDrawColor(renderer,255,144,0,255); //orange L
					break;
				case 11:
					SDL_SetRenderDrawColor(renderer,255,144,0,255); //orange L stable
					break;
				case 4:
					SDL_SetRenderDrawColor(renderer,255,255,0,255); //yellow square
					break;
				case 12:
					SDL_SetRenderDrawColor(renderer,255,255,0,255); //yellow square stable
					break;
				case 5:
					SDL_SetRenderDrawColor(renderer,0,255,0,255); //green zgigzag
					break;
				case 13:
					SDL_SetRenderDrawColor(renderer,0,255,0,255); //green zgigzag stable
					break;
				case 6:
					SDL_SetRenderDrawColor(renderer,255,0,255,255); //purple T
					break;
				case 14:
					SDL_SetRenderDrawColor(renderer,255,0,255,255); //purple T stable
					break;
				case 7:
					SDL_SetRenderDrawColor(renderer,255,0,0,255); //red zigzag
					break;
				case 15:
					SDL_SetRenderDrawColor(renderer,255,0,0,255); //red zigzag stable
					break;
				case 0:
					SDL_SetRenderDrawColor(renderer,0,0,0,255);
					break;
			}
			SDL_RenderFillRect(renderer,&board[y][x].r);
			SDL_SetRenderDrawColor(renderer,0,0,0,255);
		}
	}
}

void spawnTetromino(int tetromino[4][4], int y, int x){
	for(int i=0; i<4; i++){
		for(int j=0; j<4; j++){
			if(board[y+i][x+j].val!=0) continue;
			board[y+i][x+j].val=tetromino[i][j];
		}
	}
}

int isFalling(){
	for(int i=0; i<21; i++){
		for(int j=0; j<10; j++){
			if(board[i][j].val>0 && board[i][j].val<8) return 1;
		}
	}
	return 0;
}
int zigzagcounter=1;
int Tcounter=1;
int revZigzagcounter=1;
int Lcounter=1;
int revLcounter=1;
int longBoicounter=1;
int previous=-1;
void spawnRandomTetromino(){
	if(isFalling()) return;
	int r=rand()%7;
	while(r==previous){
		r=rand()%7;
	}
	previous=r;
	switch(r){
		case 0:
			for(int i=0; i<4; i++){
				for(int j=0; j<4; j++){
					board[1+i][3+j].val=longBoi[i][j];
				}
			}
			break;
		case 1:
			for(int i=0; i<4; i++){
				for(int j=0; j<4; j++){
					board[1+i][3+j].val=revL[i][j];
				}
			}
			break;
		case 2:
			for(int i=0; i<4; i++){
				for(int j=0; j<4; j++){
					board[1+i][3+j].val=L[i][j];
				}
			}
			break;
		case 3:
			for(int i=0; i<4; i++){
				for(int j=0; j<4; j++){
					board[1+i][3+j].val=square[i][j];
				}
			}
			break;
		case 4:
			for(int i=0; i<4; i++){
				for(int j=0; j<4; j++){
					board[1+i][3+j].val=revZigzag[i][j];
				}
			}
			break;
		case 5:
			for(int i=0; i<4; i++){
				for(int j=0; j<4; j++){
					board[1+i][3+j].val=T[i][j];
				}
			}
			break;
		case 6:
			for(int i=0; i<4; i++){
				for(int j=0; j<4; j++){
					board[1+i][3+j].val=zigzag[i][j];
				}
			}
			break;
	}
	longBoicounter=1;
	revLcounter=1;
	revZigzagcounter=1;
	Lcounter=1;
	Tcounter=1;
	zigzagcounter=1;
}

void clear(int y, int x, int color){
	if(board[y][x].val!=color) return;
	board[y][x].val=0;
	clear(y-1,x,color);
	clear(y+1,x,color);
	clear(y,x-1,color);
	clear(y,x+1,color);
}

void rotate(){
	if(!isFalling()) return;

	int x, y, found=0;
	int color;
	for(int i=0; i<21; i++){
		for(int j=0; j<10; j++){
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
	clear(y,x,color);
	switch(color){
		case 1:
			spawnTetromino(longBoiCycle[longBoicounter],y,x);
			if(longBoicounter) longBoicounter=0;
			else longBoicounter=1;
			break;
		case 2:
			spawnTetromino(revLCycle[revLcounter],y,x);
			revLcounter++;
			if(revLcounter==4) revLcounter=0;
			break;
		case 3:
			spawnTetromino(LCycle[Lcounter],y,x);
			Lcounter++;
			if(Lcounter==4) Lcounter=0;
			break;
		case 5:
			spawnTetromino(revZigzagCycle[revZigzagcounter],y,x);
			if(revZigzagcounter) revZigzagcounter=0;
			else revZigzagcounter=1;
			break;
		case 6:
			spawnTetromino(TCycle[Tcounter],y,x);
			Tcounter++;
			if(Tcounter==4) Tcounter=0;
			break;
		case 7:
			spawnTetromino(zigzagCycle[zigzagcounter],y,x);
			if(zigzagcounter) zigzagcounter=0;
			else zigzagcounter=1;
			break;
	}
}

void devMode(){
	system("cls");
	for(int i=0; i<22; i++){
		printf("%d\t",i);
		for(int j=0; j<10; j++){
			printf(" %d ",board[i][j].val);
		}
		printf("\n");
	}
}

int touchWallLeft(){
	for(int i=0; i<21; i++){
		if(board[i][0].val>0 && board[i][0].val<8) return 1;
	}
	return 0;
}
int touchWallRight(){
	for(int i=0; i<21; i++){
		if(board[i][9].val>0 && board[i][9].val<8) return 1;
	}
	return 0;
}

void moveBlock(char d){
	switch(d){
		case 'l':
			if(touchWallLeft()) break;
			for(int j=1; j<10; j++){
				for(int i=0; i<21; i++){
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
			if(touchWallRight()) break;
			for(int j=8; j>=0; j--){
				for(int i=0; i<21; i++){
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



void settle(int y, int x){
	if(board[y][x].val==0 || board[y][x].val>=8){
		return;
	}
	board[y][x].val+=8;
	settle(y-1,x);
	settle(y+1,x);
	settle(y,x+1);
	settle(y,x-1);
}

void clearBlock(){
	int cleared=0;
	for(int i=21; i>0; i--){
		int toClear=1;
		for(int j=0; j<10; j++){
			if(board[i][j].val<8) {
				toClear=0;
				break;
			}
		}
		if(toClear){
			for(int a=i; a>0; a--){
				for(int j=0; j<10; j++){
					board[a][j].val=board[a-1][j].val;
					board[a-1][j].val=0;
				}
			}
		}
	}
}

void gravity(){

	clearBlock();
	//SETTLE BLOCKS THAT TOUCH THE FLOOR
	for(int j=0; j<10; j++){
		if(board[21][j].val!=0){
			settle(21,j);
		}
	}

	//SETTLE BLOCKS THAT TOUCH SETTLED BLOCKS
	for(int i=20; i>1; i--){
		for(int j=0; j<10; j++){
			if(board[i+1][j].val!=board[i][j].val && board[i+1][j].val!=0){
				settle(i,j);
			}
		}
	}

	for(int i=21; i>1; i--){
		for(int j=0; j<10; j++){
			if(board[i-1][j].val>=8 || board[i][j].val!=0){
				continue;
			}
			board[i][j].val=board[i-1][j].val;
			board[i-1][j].val=0;
		}
	}
	spawnRandomTetromino();
	devMode();
}

void resetBoard(){
	for(int i=0; i<22; i++){
		for(int j=0; j<10; j++){
			board[i][j].val=0;
		}
	}
	spawnTetromino(longBoi,2,0);
	spawnTetromino(revL,2,5);
	spawnTetromino(L,5,1);
	spawnTetromino(square,7,8);
	spawnTetromino(revZigzag,10,0);
	spawnTetromino(T,12,5);
	spawnTetromino(zigzag,15,3);
}

unsigned int lastTime=0, currentTime;
int gravityTick=500;

void timeGravity(){
	currentTime = SDL_GetTicks();
	if (currentTime>lastTime+gravityTick) {
		gravity();
		lastTime = currentTime;
	}
}

int main(int argc, char* args[]){

	srand(time(NULL));

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
	while(running){

		//-----------------------------UPDATE---------------------------//
		//-------------------------------------------------------------//
		
		SDL_PollEvent(&event);
		timeGravity();
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
						moveBlock('l');
						break;
					case SDLK_RIGHT:
						moveBlock('r');
						break;
					case SDLK_UP:
						rotate();
						break;
					case SDLK_DOWN:
						gravity();
						break;
					case SDLK_SPACE:
						gravityTick/=2;
						break;
					case SDLK_r:
						resetBoard();
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
		drawBackground(renderer,background);
		updateBoard(renderer);
		SDL_RenderPresent(renderer);
	}
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}