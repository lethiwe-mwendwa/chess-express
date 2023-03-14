#include "SDL.h"
#include "Constants.h"
#include "Board.h"
#include "Piece.h"
#include <iostream>
#include <algorithm>
#include "Inputs.h"
using namespace std;

//Work in progress functions/ideas NB: move away later
/*
* 
* // chess board coords and find chess board points using coords
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

/*
string notationWriter(){
	int fenCount = 0;
	for (int i = 0; i < boardSize; i++) {
		for (int j = 0; j < boardSize; j++) {
			if (chessBoard[i][j] == 0) {
				fenCount += 1;
			}
			else{
				switch(chessBoard[i][j]) {
					case 12:
				}
			}

		}
	}
};

void notationReader() {
};

*/

//Temp Function


void manualCreateBoard(SDL_Renderer* renderer);

int main(int argc, char* argv[])
{
	SDL_Init(SDL_INIT_EVERYTHING);

	//Window and Renderer creation
	SDL_Window* window = SDL_CreateWindow("Chess Express", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
	SDL_Event event;
	SDL_Surface* icon = SDL_LoadBMP("assets/gameIcon.BMP");
	SDL_SetWindowIcon(window, icon);
	SDL_FreeSurface(icon);

	//Create the board. (Make function to create the board and render pieces in default mode once FEN notation is done.
	Board::drawBoard(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
	manualCreateBoard(renderer);
	//Piece::drawPeice(renderer, 5, 5, (WHITE | ROOK));
	SDL_RenderPresent(renderer);

	//SDL_UpdateWindowSurface(window);  (Dont remember what this was about. Read up on what this does)



	// The game loop
	bool gameRunning = true; 

	while (gameRunning) {

		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				gameRunning = false;
				break;
			}
			if (event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) {
				Board::drawBoard(renderer, event.window.data1, event.window.data2);
				//Chess thing lol /*
				manualCreateBoard(renderer);
				//uh yeah /*
				//Piece::drawPeice(renderer, 5, 5, (WHITE | ROOK));
				SDL_RenderPresent(renderer);
				//make a function that displays the current board shape. make a fen notation val called "current"
				
			}
			if (event.type == SDL_MOUSEBUTTONDOWN){
				if (event.button.button = SDL_BUTTON_LEFT) {
					if ((findClickedRect(event.button.x, event.button.y))){

						//The code for the drag goes here.
						SDL_SetRenderDrawColor(renderer, 60, 0, 0, 255);
						SDL_RenderFillRect(renderer, (findClickedRect(event.button.x, event.button.y)));
						SDL_RenderPresent(renderer);
					}

				}

			}
			
		}
	}

	
	SDL_DestroyWindow(window);

	SDL_Quit();

	return 0;
}




void manualCreateBoard(SDL_Renderer* renderer) {

	Piece::drawPeice(renderer, 1, 0,(BLACK | PAWN));
	Piece::drawPeice(renderer, 1, 1, (BLACK | PAWN));
	Piece::drawPeice(renderer, 1, 2, (BLACK | PAWN));
	Piece::drawPeice(renderer, 1, 3, (BLACK | PAWN));
	Piece::drawPeice(renderer, 1, 4,(BLACK | PAWN));
	Piece::drawPeice(renderer, 1, 5,(BLACK | PAWN));
	Piece::drawPeice(renderer, 1, 6,(BLACK | PAWN));
	Piece::drawPeice(renderer, 1, 7,(BLACK | PAWN));

	Piece::drawPeice(renderer, 0, 0, (BLACK | ROOK));
	Piece::drawPeice(renderer, 0, 1, (BLACK | KNIGHT));
	Piece::drawPeice(renderer, 0, 2, (BLACK | BISHOP));
	Piece::drawPeice(renderer, 0, 3, (BLACK | QUEEN));
	Piece::drawPeice(renderer, 0, 4, (BLACK | KING));
	Piece::drawPeice(renderer, 0, 5, (BLACK | BISHOP));
	Piece::drawPeice(renderer, 0, 6, (BLACK | KNIGHT));
	Piece::drawPeice(renderer, 0, 7, (BLACK | ROOK));

	Piece::drawPeice(renderer, 6, 0, (WHITE | PAWN));
	Piece::drawPeice(renderer, 6, 1, (WHITE | PAWN));
	Piece::drawPeice(renderer, 6, 2, (WHITE | PAWN));
	Piece::drawPeice(renderer, 6, 3, (WHITE | PAWN));
	Piece::drawPeice(renderer, 6, 4, (WHITE | PAWN));
	Piece::drawPeice(renderer, 6, 5, (WHITE | PAWN));
	Piece::drawPeice(renderer, 6, 6, (WHITE | PAWN));
	Piece::drawPeice(renderer, 6, 7, (WHITE | PAWN));

	Piece::drawPeice(renderer, 7, 0, (WHITE | ROOK));
	Piece::drawPeice(renderer, 7, 1, (WHITE | KNIGHT));
	Piece::drawPeice(renderer, 7, 2, (WHITE | BISHOP));
	Piece::drawPeice(renderer, 7, 3, (WHITE | QUEEN));
	Piece::drawPeice(renderer, 7, 4, (WHITE | KING));
	Piece::drawPeice(renderer, 7, 5, (WHITE | BISHOP));
	Piece::drawPeice(renderer, 7, 6, (WHITE | KNIGHT));
	Piece::drawPeice(renderer, 7, 7, (WHITE | ROOK));
};


