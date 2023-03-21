#include "SDL.h"
#include "Constants.h"
#include "Board.h"
#include "Piece.h"
#include <iostream>
#include <algorithm>
#include "Inputs.h"
#include <cstring>

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


//Temp Function

void titleSequence(SDL_Renderer* renderer);
void titleSequence(SDL_Renderer* renderer) {
	SDL_Surface* imageSurface = NULL;
	imageSurface = SDL_LoadBMP(titleImagePath);

	if (NULL == imageSurface) {
		cout << "SDL error bozo" << SDL_GetError();
	}
	SDL_Rect titleRect{};
	titleRect.x = 0 -((((SCREEN_HEIGHT-200) * 128) / 91 )-SCREEN_WIDTH)/2;
	titleRect.y = 0 - ((SCREEN_HEIGHT - 200) - SCREEN_HEIGHT) / 2;
	titleRect.h = SCREEN_HEIGHT-200;
	titleRect.w = ((SCREEN_HEIGHT-200)*120)/91;
	SDL_Texture* imageTexture = SDL_CreateTextureFromSurface(renderer, imageSurface);
	SDL_FreeSurface(imageSurface);
	SDL_SetRenderDrawColor(renderer, 5, 50, 70, 255);
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, imageTexture, NULL, &titleRect);
	SDL_DestroyTexture(imageTexture);
	SDL_RenderPresent(renderer);
}

bool titleScreen = true;
bool gameRunning = true;

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

	
	titleSequence(renderer);
	SDL_Delay(2000);


	//Create the board. (Make function to create the board and render pieces in default mode once FEN notation is done.
	Board::fenSplitter(currentFen);
	Board::drawBoard(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
	Board::fenDisplay(renderer, piecePlacement);
	SDL_RenderPresent(renderer);

	//SDL_UpdateWindowSurface(window);  (Dont remember what this was about. Read up on what this does)

	//Temporary testing:
	//test code
	
	//cout << piecePlacement << endl;
	//cout << playerTurn << endl;
	//cout << castlingAbility << endl;
	//cout << enPassantTarget << endl;
	//cout << halfmoveClock << endl;
	//cout << fullmoveClock << endl;

	// The game loop
	

	while (gameRunning) {

		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				gameRunning = false;
				break;
			}
			if (event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) {
				//Chess thing lol /*
				Board::drawBoard(renderer, event.window.data1, event.window.data2);
				Board::fenDisplay(renderer, piecePlacement);
				SDL_RenderPresent(renderer);
				//make a function that displays the current board shape. make a fen notation val called "current", 
				//and every time it resizes it redraws from looking at it
			}
			if (event.type == SDL_MOUSEBUTTONDOWN){
				if (event.button.button = SDL_BUTTON_LEFT) {
					if ((findClickedRect(event.button.x, event.button.y))){
						//The code for the drag etc goes here.


						//This is to test that input works

						cout << endl << event.button.x << " " << event.button.y;
						SDL_SetRenderDrawColor(renderer, 10, 70, 150, 10);
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

