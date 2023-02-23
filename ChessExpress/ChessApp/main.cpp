#include "SDL.h"
using namespace std;

const int boardSize = 8;
const int tileSize = 70;
int SCREEN_WIDTH = 560;
int SCREEN_HEIGHT = 560;

void drawBoard(SDL_Renderer* renderer, int boardSize, int tileSize) {
	int tileHeightInc = 0;

	for (int i = 0; i < boardSize; i++) {
		int tileWidthInc = 0;

		for (int j = 0; j < boardSize; j++) {
			//i is the row, j is the column
			//draw square
			if (((i + j) % 2) == 0) {
				SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			}
			else {
				SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
			}

			SDL_Rect tile = { tile.x = tileWidthInc, tile.y = tileHeightInc, tile.h = tileSize, tile.w = tileSize };
			SDL_RenderFillRect(renderer, &tile);
			tileWidthInc += tileSize;
		}
		tileHeightInc += tileSize;
	}

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

	SDL_Window* window = SDL_CreateWindow("Chess Express", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );

	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

	SDL_Event event;


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

	drawBoard(renderer, boardSize, tileSize);

	SDL_RenderPresent(renderer);

	// HERES THE GAME LOOP WOOO
	bool gameRunning = true;

	while (gameRunning) {

		SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255);

		SDL_RenderClear(renderer);

		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				gameRunning = false;
				break;
			}
		}
	}

	SDL_DestroyWindow(window);

	SDL_Quit();

	return 0;
}