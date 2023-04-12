#include "SDL.h"
#include "Constants.h"
#include "Board.h"
#include "Piece.h"
#include <iostream>
#include <algorithm>
#include "Inputs.h"
#include <cstring>
#include "King.h"
using namespace std;

//Temp Function
void titleSequence(SDL_Renderer* renderer, int sWidth, int sHeight);

bool titleScreen = true;
bool gameRunning = true;

int main(int argc, char* argv[])
{
	SDL_Init(SDL_INIT_EVERYTHING);

	//Window and Renderer creation
	SDL_Window* window = SDL_CreateWindow("Chess Express", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
	SDL_Event event;
	SDL_Surface* icon = SDL_LoadBMP("assets/gameIcon.BMP");
	SDL_SetWindowIcon(window, icon);
	SDL_FreeSurface(icon);



	titleSequence(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);

	while (titleScreen) {
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				titleScreen = false;
				gameRunning = false;
				break;
			}
			if (event.type == SDL_KEYDOWN) {
				cout << event.key.keysym.sym << endl;
				if (event.key.keysym.sym == SDLK_RETURN) {

					titleScreen = false;
				}
			}
			if (event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) {
				titleSequence(renderer, event.window.data1, event.window.data2);
			}
		}
	}



	//Create the board. (Make function to create the board and render pieces in default mode once FEN notation is done.
	Board::fenSplitter(currentFen);
	Board::fenSetup(renderer, piecePlacement);
	Board::drawBoard(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
	Board::pieceDisplay(renderer);
	SDL_RenderPresent(renderer);

	//SDL_UpdateWindowSurface(window);  (Dont remember what this was about. Read up on what this does)

	//Temporary testing:
	//test code


	cout << piecePlacement << endl;
	cout << playerTurn << endl;
	cout << castlingAbility << endl;
	cout << enPassantTarget << endl;
	cout << halfmoveClock << endl;
	cout << fullmoveClock << endl;

	// The game loop

	while (gameRunning) {
		//Uint64 start = SDL_GetPerformanceCounter();

		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_QUIT:
				gameRunning = false;

				break;
			case SDL_WINDOWEVENT:
				if (event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) {
					//Chess thing lol /*
					Board::drawBoard(renderer, event.window.data1, event.window.data2);
					Board::pieceDisplay(renderer);
					SDL_RenderPresent(renderer);

					//make a function that displays the current board shape. make a fen notation val called "current", 
					//and every time it resizes it redraws from looking at it
				}

				break;
			case SDL_MOUSEBUTTONDOWN:
				switch (event.button.button) {

				case SDL_BUTTON_LEFT:

					//if ((findClickedRect(event.button.x, event.button.y))){
					//The code for the drag etc goes here.
					//This is to test that input works
					///cout << endl << event.button.x << " " << event.button.y;
					//SDL_SetRenderDrawColor(renderer, 10, 70, 150, 10);
					//SDL_RenderFillRect(renderer, (findClickedRect(event.button.x, event.button.y)));
					//SDL_RenderPresent(renderer);
					//}

					

					if (not(isDragging) && findClickedPiece(event.button.x, event.button.y)) {
						clickedPiece = findClickedPiece(event.button.x, event.button.y);

						//ERROR!!! in how the chess pieces are stored (fixed.)
						//findClickedPiece(event.button.x, event.button.y)->drawPeice(renderer, 3, 3);
						//SDL_RenderPresent(renderer);

						//FIX THIS PART GOOFBALL
						if (not(((playerTurn == 'w' and findClickedPiece(event.button.x, event.button.y)->pieceType & WHITE)) or (playerTurn == 'b' and (findClickedPiece(event.button.x, event.button.y)->pieceType & BLACK)))) {
							break;
						}
						mouseRect.x = event.button.x;
						mouseRect.y = event.button.y;
						mouseRect.h = gameTileSize;
						mouseRect.w = gameTileSize;

						isDragging = true;
						
					}
					break;
				}
				break;
			case SDL_MOUSEBUTTONUP:
				if (event.button.button == SDL_BUTTON_LEFT) {
					if (isDragging) {
						isDragging = false;
						SDL_RenderClear(renderer);
						Board::drawBoard(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);

						if (findClickedRect(event.button.x, event.button.y)) {
							bool freeSpace = not(findClickedPiece(event.button.x, event.button.y));

							int clickedRow;
							int clickedColumn;
							findClickedCords(event.button.x, event.button.y,clickedRow,clickedColumn);
							bool validMove = clickedPiece->isMoveValid(clickedColumn,clickedRow);
							cout << endl << validMove << endl;
							//player turn check

							//if playerturn == 'w'

							if (validMove) {
								if (freeSpace) {
									clickedPiece->placePiece(renderer, event.button.x, event.button.y);
									if (playerTurn == 'w') {
										playerTurn = 'b';
									}
									else if (playerTurn == 'b') {
										playerTurn = 'w';
									}
								}
								else {
									Piece* pieceInTheWay = findClickedPiece(event.button.x, event.button.y);

									if (playerTurn == 'w') {
										if (pieceInTheWay->pieceType & BLACK) {
											//kill piece
											pieceInTheWay->killPeice();
											clickedPiece->placePiece(renderer, event.button.x, event.button.y);
											playerTurn = 'b';

										}
									}
									else if (playerTurn == 'b') {
										// DUDE fix the whole, is 0 thing, lmao

										if ((pieceInTheWay->pieceType & WHITE)) {
											//kill piece
											pieceInTheWay->killPeice();
											clickedPiece->placePiece(renderer, event.button.x, event.button.y);
											playerTurn = 'w';


										}
									}

								}
							}
							
						}
						
						Board::pieceDisplay(renderer);
						SDL_RenderPresent(renderer);

						cout << piecePlacement << endl;
						cout << playerTurn << endl;   // WHEEEE
						cout << castlingAbility << endl;
						cout << enPassantTarget << endl;
						cout << halfmoveClock << endl;
						cout << fullmoveClock << endl;
						
						
					}


					break;
			case SDL_MOUSEMOTION:
				if (isDragging) {

					int mouseX = event.motion.x;
					int mouseY = event.motion.y;

					//SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
					//SDL_RenderClear(renderer);
					mouseRect.x = mouseX - gameTileSize / 2;
					mouseRect.y = mouseY - gameTileSize / 2;

					Board::drawBoard(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
					//laggy
					Board::pieceDisplay(renderer, clickedPiece);
					clickedPiece->drawPeice(renderer, mouseRect);
					SDL_RenderPresent(renderer);


				}
				break;
				}

			}
			//Uint64 end = SDL_GetPerformanceCounter();

			//float elapsedMS = (end - start) / (float)SDL_GetPerformanceFrequency() * 1000.0f;

			// Cap to 60 FPS
			//SDL_Delay(10);
		}
		
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}

//VERY MESSY. Make function for desplaying certain things in specific places.

void titleSequence(SDL_Renderer* renderer, int sWidth, int sHeight ){
	SDL_SetRenderDrawColor(renderer, 5, 50, 70, 255);
	SDL_RenderClear(renderer);
	SDL_Surface* imageSurface = NULL;
	imageSurface = SDL_LoadBMP(titleImagePath);
	if (NULL == imageSurface) {
		cout << "SDL error" << SDL_GetError();
	}

	// You basically need to copy for each image and dupe for each of them for when height
	// is bigger than width, and when width is bigger than height. Just like when you did the
	// chess board

	//the shorter end should be the one determining the size of the contents essentially.


	// Change this later, stop being silly
	SDL_Rect titleRect{};
	

	// the multiplication is how big the image is relative to the screen (side)
	if (sHeight > sWidth) {
		titleRect.w = sWidth * 0.9;
		titleRect.h = ((titleRect.w) * 91) / 120;
	}
	else {

		titleRect.h = sHeight * 0.6;
		titleRect.w = ((titleRect.h) * 120) / 91;
	}



	titleRect.x = 0 + (sWidth-titleRect.w) / 2;
	titleRect.y = 0 + (sHeight-titleRect.h) / 2;
	SDL_Texture* imageTexture = SDL_CreateTextureFromSurface(renderer, imageSurface);
	SDL_FreeSurface(imageSurface);
	SDL_RenderCopy(renderer, imageTexture, NULL, &titleRect);
	SDL_DestroyTexture(imageTexture);

	//Change this later toooooo. Stop summoning magic numbers.
	
	imageSurface = SDL_LoadBMP(pressEnterImagePath);
	if (NULL == imageSurface) {
		cout << "SDL error" << SDL_GetError();
	}

	SDL_Rect startRect{};
	
	// * by 5 then devide
	if (sHeight > sWidth) {
		startRect.w = sWidth * 0.59;
		startRect.h = ((startRect.w) * 16) / 75;
	}
	else {
		
		startRect.h = sHeight * 0.09;
		startRect.w = ((startRect.h) * 75) / 16;
	}
	
	

	startRect.x = 0 + (sWidth - startRect.w) / 2;
	startRect.y = sHeight-startRect.h;
	imageTexture = SDL_CreateTextureFromSurface(renderer, imageSurface);
	SDL_FreeSurface(imageSurface);
	SDL_RenderCopy(renderer, imageTexture, NULL, &startRect);
	SDL_DestroyTexture(imageTexture);
	SDL_RenderPresent(renderer);
	SCREEN_WIDTH = sWidth;
	SCREEN_HEIGHT = sHeight;
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

