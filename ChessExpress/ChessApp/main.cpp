#include "SDL.h"
#include <iostream>
#include <algorithm>
using namespace std;

const int boardSize = 8;
int SCREEN_WIDTH = 700;
int SCREEN_HEIGHT =400;
SDL_Rect boardTiles[boardSize][boardSize];



int ChessBoard[boardSize][boardSize] = {
{0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0}

};

// chess board coords and find chess board coords
/*
const string ChessBoardCords[boardSize][boardSize] = {
{"8a","8b","8c","8d","8e","8f","8g","8h"},
{"7a","7b","7c","7d","7e","7f","7g","7h"},
{"6a","6b","6c","6d","6e","6f","6g","6h"},
{"5a","5b","5c","5d","5e","5f","5g","5h"},
{"4a","4b","4c","4d","4e","4f","4g","4h"},
{"3a","3b","3c","3d","3e","3f","3g","3h"},
{"2a","2b","2c","2d","2e","2f","2g","2h"},
{"1a","1b","1c","1d","1e","1f","1g","1h"}

};



int findSquareCoords(string coord){
	for (int i = 0 ; i < boardSize; i++){
		for (int j = 0; j < boardSize; j++) {
			if (coord == ChessBoardCords[i][j]) {
				return (i,j);
				break;
			}
		}
	}
}
*/




void drawBoard(SDL_Renderer* renderer, float width, float height) {
	int tileWidthInc;
	int tileSize;
	int tileHeightInc;
	int widthCord;

	// This part checks the width and height of the screen
	if (height < width) {
		tileSize = round(height) / boardSize;
		tileHeightInc = 0 - round(tileSize * 8 - height) / 2;
		widthCord = round((width - height)) / 2;
		//if (tileSize * 8 < min(width, height) {}

	}
	else {
		tileSize = round(width) / boardSize;
		tileHeightInc = 0 - round(width - height) / 2;
		widthCord = round(width - tileSize * 8) / 2;

	}
	
	// SDL_SetRenderDrawColor(renderer, 5, 50, 70, 255);
	SDL_SetRenderDrawColor(renderer, 5, 50, 70, 255);
	SDL_RenderClear(renderer);

	for (int i = 0; i < boardSize; i++) {
		tileWidthInc = widthCord;
		for (int j = 0; j < boardSize; j++) {
			//i is the row, j is the column
			//draw square
			if (((i + j) % 2) == 0) {
				SDL_SetRenderDrawColor(renderer, 232, 226, 198, 255);
			}
			else {
				SDL_SetRenderDrawColor(renderer, 30, 129, 176, 255);
			}	
			SDL_Rect tile = { 
				tile.x = tileWidthInc, 
				tile.y = tileHeightInc, 
				tile.h = tileSize, 
				tile.w = tileSize 
			};
			boardTiles[i][j] = tile;
			SDL_RenderFillRect(renderer, &tile);

			tileWidthInc += tileSize;
		}
		tileHeightInc += tileSize;
		
	}
	cout << endl << " Tile*8: " << tileSize*8 << " Width: " << width << " Height: " << height;

	
};

void drawPeice(SDL_Renderer* renderer, string peiceType, int column, int row){
	SDL_Surface* imageSurface = NULL;
	

	if (peiceType == "bP") {
		imageSurface = SDL_LoadBMP("assets/bP.bmp");
	}
	else if(peiceType == "bQ"){
		imageSurface = SDL_LoadBMP("assets/bQ.bmp");
	}
	else if(peiceType == "bK"){
		imageSurface = SDL_LoadBMP("assets/bK.bmp");
	}
	else if (peiceType == "bN") {
		imageSurface = SDL_LoadBMP("assets/bN.bmp");
	}
	else if (peiceType == "bB") {
		imageSurface = SDL_LoadBMP("assets/bB.bmp");
	}
	else if (peiceType == "bR") {
		imageSurface = SDL_LoadBMP("assets/bR.bmp");
	}
	else if (peiceType == "P") {
		imageSurface = SDL_LoadBMP("assets/P.bmp");
	}
	else if (peiceType == "Q") {
		imageSurface = SDL_LoadBMP("assets/Q.bmp");
	}
	else if (peiceType == "K") {
		imageSurface = SDL_LoadBMP("assets/K.bmp");
	}
	else if (peiceType == "N") {
		imageSurface = SDL_LoadBMP("assets/N.bmp");
	}
	else if (peiceType == "B") {
		imageSurface = SDL_LoadBMP("assets/B.bmp");
	}
	else if (peiceType == "R") {
		imageSurface = SDL_LoadBMP("assets/R.bmp");
	}


	if (NULL == imageSurface) {
		cout << "SDL error bozo" << SDL_GetError();
	}
	SDL_Rect imageRectLocation = boardTiles[column][row];
	
	//SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0");
	SDL_Texture* imageTexture = SDL_CreateTextureFromSurface(renderer, imageSurface);
	SDL_FreeSurface(imageSurface);
	//SDL_SetTextureScaleMode(temTexture, SDL_ScaleModeBest);

	SDL_RenderCopy(renderer, imageTexture, NULL, &imageRectLocation);
	SDL_DestroyTexture(imageTexture);

	
}

int main(int argc, char* argv[])
{
	SDL_Init(SDL_INIT_EVERYTHING);

	/*

	// My attempt at a FEN notation reader
	for (int i; i < 8; i++) {
		for (int j; i < 8; j++) {
			if (ChessBoard[i][j] == 0):
				FENnum

		}
	}
	*/

	SDL_Window* window = SDL_CreateWindow("Chess Express", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
	SDL_Event event;
	//NEW
	
	
	drawBoard(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
	drawPeice(renderer, "bR", 0, 0);
	drawPeice(renderer, "bN", 0, 1);
	drawPeice(renderer, "bB", 0, 2);
	drawPeice(renderer, "bQ", 0, 3);
	drawPeice(renderer, "bK", 0, 4);
	drawPeice(renderer, "bB", 0, 5);
	drawPeice(renderer, "bN", 0, 6);
	drawPeice(renderer, "bR", 0, 7);
	drawPeice(renderer, "bP", 1, 0);
	drawPeice(renderer, "bP", 1, 1);
	drawPeice(renderer, "bP", 1, 2);
	drawPeice(renderer, "bP", 1, 3);
	drawPeice(renderer, "bP", 1, 4);
	drawPeice(renderer, "bP", 1, 5);
	drawPeice(renderer, "bP", 1, 6);
	drawPeice(renderer, "bP", 1, 7);

	drawPeice(renderer, "R", 7, 0);
	drawPeice(renderer, "N", 7, 1);
	drawPeice(renderer, "B", 7, 2);
	drawPeice(renderer, "Q", 7, 3);
	drawPeice(renderer, "K", 7, 4);
	drawPeice(renderer, "B", 7, 5);
	drawPeice(renderer, "N", 7, 6);
	drawPeice(renderer, "R", 7, 7);
	drawPeice(renderer, "P", 6, 0);
	drawPeice(renderer, "P", 6, 1);
	drawPeice(renderer, "P", 6, 2);
	drawPeice(renderer, "P", 6, 3);
	drawPeice(renderer, "P", 6, 4);
	drawPeice(renderer, "P", 6, 5);
	drawPeice(renderer, "P", 6, 6);
	drawPeice(renderer, "P", 6, 7);
	SDL_RenderPresent(renderer);
	//SDL_UpdateWindowSurface(window);

	// HERES THE GAME LOOP WOOO
	bool gameRunning = true; 

	while (gameRunning) {
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				gameRunning = false;
				break;


			}
			if (event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) {

				drawBoard(renderer, event.window.data1, event.window.data2);
				
				//Chess thing lol /*
				drawPeice(renderer, "bR", 0, 0);
				drawPeice(renderer, "bN", 0, 1);
				drawPeice(renderer, "bB", 0, 2);
				drawPeice(renderer, "bQ", 0, 3);
				drawPeice(renderer, "bK", 0, 4);
				drawPeice(renderer, "bB", 0, 5);
				drawPeice(renderer, "bN", 0, 6);
				drawPeice(renderer, "bR", 0, 7);
				drawPeice(renderer, "bP", 1, 0);
				drawPeice(renderer, "bP", 1, 1);
				drawPeice(renderer, "bP", 1, 2);
				drawPeice(renderer, "bP", 1, 3);
				drawPeice(renderer, "bP", 1, 4);
				drawPeice(renderer, "bP", 1, 5);
				drawPeice(renderer, "bP", 1, 6);
				drawPeice(renderer, "bP", 1, 7);

				drawPeice(renderer, "R", 7, 0);
				drawPeice(renderer, "N", 7, 1);
				drawPeice(renderer, "B", 7, 2);
				drawPeice(renderer, "Q", 7, 3);
				drawPeice(renderer, "K", 7, 4);
				drawPeice(renderer, "B", 7, 5);
				drawPeice(renderer, "N", 7, 6);
				drawPeice(renderer, "R", 7, 7);
				drawPeice(renderer, "P", 6, 0);
				drawPeice(renderer, "P", 6, 1);
				drawPeice(renderer, "P", 6, 2);
				drawPeice(renderer, "P", 6, 3);
				drawPeice(renderer, "P", 6, 4);
				drawPeice(renderer, "P", 6, 5);
				drawPeice(renderer, "P", 6, 6);
				drawPeice(renderer, "P", 6, 7);
				//uh yeah /*

				SDL_RenderPresent(renderer);

				//make a function that displays the current board shape. make a fen notation val called "current"
			}

			
		}

	}

	
	SDL_DestroyWindow(window);

	SDL_Quit();

	return 0;
}