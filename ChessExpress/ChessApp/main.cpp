#include "SDL.h"
#include "Constants.h"
#include "Board.h"
#include "Piece.h"
#include <iostream>
#include <algorithm>
#include "Inputs.h"
#include "SDL_mixer.h"
#include "King.h"

using namespace std;

//Temp Function
void titleSequence(SDL_Renderer* renderer, int sWidth, int sHeight);
void makeMove(SDL_Renderer* renderer, int x, int y);
void startMove(SDL_Renderer* renderer, int x, int y);
void dragPiece(SDL_Renderer* renderer, int x, int y);
void setCheckValue(SDL_Renderer* renderer);

bool titleScreen = true;
bool gameRunning = true;

int main(int argc, char* argv[])
{
	SDL_Init(SDL_INIT_EVERYTHING);
	Mix_Init(0);
	Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024);
	// Initialize SDL_mixer
	if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1) {
		printf("Failed to initialize SDL_mixer: %s\n", Mix_GetError());
		return 1;
	}

	// At this point, the audio device is open and ready to use

	dieA = Mix_LoadWAV("assets/die.wav");
	moveA = Mix_LoadWAV("assets/move.wav");
	introA = Mix_LoadWAV("assets/ChessExpress.wav");
	startA = Mix_LoadWAV("assets/Start.wav");
	checkA = Mix_LoadWAV("assets/checkmate.wav");
	endGameA = Mix_LoadWAV("assets/endGame.wav");

	// Clean up SDL_mixer when you're done
	Mix_CloseAudio();

	if (startA == NULL) {
		printf("Failed to load start sound: %s\n", Mix_GetError());
		return 1;
	}

	if (introA == NULL) {
		printf("Failed to load intro sound: %s\n", Mix_GetError());
		return 1;
	}

	if (dieA == NULL) {
		printf("Failed to load die sound: %s\n", Mix_GetError());
		return 1;
	}

	if (moveA == NULL) {
		printf("Failed to load move sound: %s\n", Mix_GetError());
		return 1;
	}
	//Mix_Volume(60);

	//Window and Renderer creation
	SDL_Window* window = SDL_CreateWindow("Chess Express", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
	SDL_Event event;
	SDL_Surface* icon = SDL_LoadBMP("assets/gameIcon.BMP");
	SDL_SetWindowIcon(window, icon);
	SDL_FreeSurface(icon);


	int introChannel = Mix_PlayChannel(-1, introA, 0);
	if (introChannel == -1) {
		printf("Failed to play die sound: %s\n", Mix_GetError());
	}

	cout << chessExpressASCII << endl;
	titleSequence(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
	while (titleScreen) {
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				titleScreen = false;
				gameRunning = false;
				Mix_FreeChunk(dieA);
				Mix_FreeChunk(moveA);
				SDL_DestroyRenderer(renderer);
				SDL_DestroyWindow(window);
				SDL_Quit();
				return 0;
			}
			if (event.type == SDL_KEYDOWN) {
				//cout << event.key.keysym.sym << endl;
				if (event.key.keysym.sym == SDLK_RETURN) {

					titleScreen = false;
				}
			}
			if (event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) {
				titleSequence(renderer, event.window.data1, event.window.data2);
			}
		}
	}
	cout << lethiweMwendwaASCII << endl ;
	cout << "Librarys used:" << endl << "SDL2, SDL2_Mixer" << endl << endl;

	//Create the board. (Make function to create the board and render pieces in default mode once FEN notation is done.
	int startChannel = Mix_PlayChannel(-1, startA, 0);
	if (startChannel == -1) {
		printf("Failed to play die sound: %s\n", Mix_GetError());
	}

	Board::initBoardTextures(renderer);
	Board::fenSplitter(currentFen);
	Board::fenSetup(renderer, piecePlacement);
	Board::drawBoard(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
	Board::pieceDisplay(renderer);
	setCheckValue(renderer);
	SDL_RenderPresent(renderer);
	SDL_Delay(1500);
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
	cout << fullmoveClock << endl << endl;
	
	// The game loop

	while (gameRunning) {
		//Uint64 start = SDL_GetPerformanceCounter();

		// have menu here.

		//chess game while chess running
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

					//select piece // start move
					startMove(renderer, event.button.x, event.button.y);
					
					break;
				}
				break;
			case SDL_MOUSEBUTTONUP:
				if (event.button.button == SDL_BUTTON_LEFT) {

					makeMove(renderer, event.button.x,event.button.y);

					break;
			case SDL_MOUSEMOTION:

				dragPiece(renderer, event.motion.x, event.motion.y);

				break;
				}

			}
			//Uint64 end = SDL_GetPerformanceCounter();

			//float elapsedMS = (end - start) / (float)SDL_GetPerformanceFrequency() * 1000.0f;

			// Cap to 60 FPS
			//SDL_Delay(10);
		}

	}
	Mix_FreeChunk(dieA);
	Mix_FreeChunk(moveA);
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

void startMove(SDL_Renderer* renderer, int x, int y) {
	if (not(isDragging) && findClickedPiece(x, y) && not checkmate) {
		clickedPiece = findClickedPiece(x, y);

		if (((playerTurn == 'w' and findClickedPiece(x, y)->pieceType & WHITE))
			or (playerTurn == 'b' and (findClickedPiece(x, y)->pieceType & BLACK))) {

			if(((check == true and (clickedPiece->pieceType & TYPE_MASK) == KING))
				or (check != true)) {

				//lift king
				if (check == true) {
					piecesOnBoard[clickedPiece->pieceRow][clickedPiece->pieceColumn] = NULL;
					Board::refreshAllAttackZones();
					piecesOnBoard[clickedPiece->pieceRow][clickedPiece->pieceColumn] = clickedPiece;
					
				}
				mouseRect.x = x;
				mouseRect.y = y;
				mouseRect.h = gameTileSize;
				mouseRect.w = gameTileSize;

				isDragging = true;
			}
			else {
				isDragging = false;
			}

			
		}

		

	}
}
void makeMove(SDL_Renderer* renderer, int x, int y) {
	
	if (isDragging) {
		isDragging = false;
		SDL_RenderClear(renderer);
		Board::drawBoard(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);

		if (findClickedRect(x, y)) {
			bool freeSpace = not(findClickedPiece(x, y));
			int clickedRow;
			int clickedColumn;
			findClickedCords(x, y, clickedRow, clickedColumn);

			bool validMove = false;
			if (freeSpace) {
				if ((clickedPiece->pieceType & TYPE_MASK) != KING ){
					validMove = clickedPiece->isMoveValid(clickedColumn, clickedRow);
				}
				else{
					if (playerTurn == 'w') {
						validMove = whiteKing->isKingMoveSafe(clickedColumn, clickedRow);
					}
					else {
						validMove = blackKing->isKingMoveSafe(clickedColumn, clickedRow);
					}
				}
				
			}
			else {
				validMove = clickedPiece->isKillValid(clickedColumn, clickedRow);
				
			}


			if (validMove) {
				if (not freeSpace) {
					Piece* pieceInTheWay = findClickedPiece(x, y);
					pieceInTheWay->killPeice();
				}

				clickedPiece->placePiece(renderer, x, y);
				Board::pieceDisplay(renderer);
				Board::changeTurn(renderer);
				setCheckValue(renderer);

				if(checkmate){
					int checkmateChannel = Mix_PlayChannel(-1, endGameA, 0);
					if (checkmateChannel == -1) {
						printf("Failed to play move sound: %s\n", Mix_GetError());
					}
				}
				else if (check) {
					int checkChannel = Mix_PlayChannel(-1, checkA, 0);
					if (checkChannel == -1) {
						printf("Failed to play move sound: %s\n", Mix_GetError());
					}
				}
				else if (freeSpace) {
					int moveChannel = Mix_PlayChannel(-1, moveA, 0);
					if (moveChannel == -1) {
						printf("Failed to play move sound: %s\n", Mix_GetError());
					}
				}
				else {
					int dieChannel = Mix_PlayChannel(-1, dieA, 0);
					if (dieChannel == -1) {
						printf("Failed to play die sound: %s\n", Mix_GetError());
					}
				}

				SDL_RenderPresent(renderer);
				SDL_Delay(500);
				Board::drawBoard(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
				Board::toFen();
				cout << piecePlacement << endl;
				cout << playerTurn << endl;
				cout << castlingAbility << endl;
				cout << enPassantTarget << endl;
				cout << halfmoveClock << endl;
				cout << fullmoveClock << endl << endl;
				
			}

		}
		Board::pieceDisplay(renderer);
		SDL_RenderPresent(renderer);
	}


}
void dragPiece(SDL_Renderer* renderer, int x, int y) {
	if (isDragging) {

		int mouseX = x;
		int mouseY = y;
		mouseRect.x = mouseX - gameTileSize / 2;
		mouseRect.y = mouseY - gameTileSize / 2;

		Board::drawBoard(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
		Board::pieceDisplay(renderer, clickedPiece);
		clickedPiece->drawPeice(renderer, mouseRect);
		SDL_RenderPresent(renderer);


	}
}
void setCheckValue(SDL_Renderer* renderer) {
	Board::refreshAllAttackZones();
	if (playerTurn == 'w') {
		if (whiteKing->inDanger(whiteKing->pieceColumn, whiteKing->pieceRow)) {
			if (whiteKing->trapped()) {
				checkmate = true;
				SDL_RenderCopy(renderer, whiteCheckMateTexture, NULL, &statusTile);
				return;
			}
			SDL_RenderCopy(renderer, whiteCheckTexture, NULL, &statusTile);
			check = true;
			return;
		}
		else {
			check = false;
			SDL_RenderCopy(renderer, whiteTurnTexture, NULL, &statusTile);
		}
	}
	else{
		if (blackKing->inDanger(blackKing->pieceColumn, blackKing->pieceRow)) {
			
			if (blackKing->trapped()) {
				checkmate = true;
				SDL_RenderCopy(renderer, blackCheckMateTexture, NULL, &statusTile);
				return;
			}
			SDL_RenderCopy(renderer, blackCheckTexture, NULL, &statusTile);
			check = true;
			return;
		}
		else {
			check = false;
			SDL_RenderCopy(renderer, blackTurnTexture, NULL, &statusTile);
		}
	}
}
