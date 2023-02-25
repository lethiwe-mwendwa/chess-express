#include "SDL.h"
#include <iostream>
#include <algorithm>
using namespace std;

const int boardSize = 8;
int SCREEN_WIDTH = 900;
int SCREEN_HEIGHT = 560;



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
			SDL_RenderFillRect(renderer, &tile);

			tileWidthInc += tileSize;
		}
		tileHeightInc += tileSize;
		
	}
	cout << endl << " Tile*8: " << tileSize*8 << " Width: " << width << " Height: " << height;

	SDL_RenderPresent(renderer);
};


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

	/*

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
	*/

	drawBoard(renderer, SCREEN_WIDTH,SCREEN_HEIGHT);



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
				 
			}
			
		}


	}

	SDL_DestroyWindow(window);

	SDL_Quit();

	return 0;
}