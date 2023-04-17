#include "Game.h"
#include "Inputs.h"
#include <iostream>
#include "Board.h"
using namespace std;

void titleSequence(SDL_Renderer* renderer, int sWidth, int sHeight) {

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



	titleRect.x = 0 + (sWidth - titleRect.w) / 2;
	titleRect.y = 0 + (sHeight - titleRect.h) / 2;
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
	startRect.y = sHeight - startRect.h;
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

			//lift and unlift king
			if (check == true and (clickedPiece->pieceType & TYPE_MASK) == KING) {
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
				if (check != true) {
					validMove = clickedPiece->isMoveValid(clickedColumn, clickedRow);
				}
				else if((clickedPiece->pieceType & TYPE_MASK) == KING){
					if (playerTurn == 'w') {
						validMove = whiteKing->isKingMoveSafe(clickedColumn, clickedRow);
					}
					else {
						validMove = blackKing->isKingMoveSafe(clickedColumn, clickedRow);
					}
				}
				else if (clickedPiece->isMoveValid(clickedColumn, clickedRow)) {
					validMove = clickedPiece->moveUnchecks(clickedColumn, clickedRow);

				}
			}
			else {
				validMove = clickedPiece->isKillValid(clickedColumn, clickedRow);

			}


			if (validMove) {
				if (not freeSpace) {
					Piece* pieceInTheWay = findClickedPiece(x, y);
					pieceInTheWay->killPiece();
				}

				clickedPiece->placePiece(x, y);
				clickedPiece->drawPiece(renderer, *clickedPiece->pieceRect);
				Board::pieceDisplay(renderer);
				Board::changeTurn(renderer);
				setCheckValue(renderer);

				if (checkmate) {
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
		clickedPiece->drawPiece(renderer, mouseRect);
		SDL_RenderPresent(renderer);


	}
}

void setCheckValue(SDL_Renderer* renderer) {
	Board::refreshAllAttackZones();
	if (playerTurn == 'w') {
		if (whiteKing->inDanger(whiteKing->pieceColumn, whiteKing->pieceRow)) {
			if (whiteKing->trapped()) {
				checkmate = true;
			}
			else{
				SDL_RenderCopy(renderer, whiteCheckTexture, NULL, &statusTile);
				check = true;
				
			}
			
		}
		else {
			check = false;
			SDL_RenderCopy(renderer, whiteTurnTexture, NULL, &statusTile);
		}
	}
	else {
		if (blackKing->inDanger(blackKing->pieceColumn, blackKing->pieceRow)) {

			if (blackKing->trapped()) {
				checkmate = true;
				
			}
			else {
				SDL_RenderCopy(renderer, blackCheckTexture, NULL, &statusTile);
				check = true;
				
			}
			
		}
		else {
			check = false;
			SDL_RenderCopy(renderer, blackTurnTexture, NULL, &statusTile);
		}
	}
}
