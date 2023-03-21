#include "Board.h"
#include "Constants.h"
#include <iostream>
using namespace std;


Board::Board()
{
}

void Board::drawBoard(SDL_Renderer* renderer, float width, float height) {
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
			SDL_Rect tile;
			tile.x = tileWidthInc;
			tile.y = tileHeightInc;
			tile.h = tileSize;
			tile.w = tileSize;
			
			boardTiles[i][j] = tile;
			SDL_RenderFillRect(renderer, &tile);

			tileWidthInc += tileSize;
		}
		tileHeightInc += tileSize;

	}
	//cout << endl << " Tile*8: " << tileSize * 8 << " Width: " << width << " Height: " << height;


};

void Board::fenSplitter(char fen[]) {
	// fix with meaningful names later
	bool placementDone = false;
	bool turnDone = false;
	bool castlingDone = false;
	bool enPassantDone = false;
	bool halfmoveDone = false;
	int counter = 0;

	for (int i = 0; i < strlen(fen); i++) {

		if (not placementDone) {
			if (fen[i] == ' ') {
				placementDone = true;
				counter = 0;
			}
			else {
				piecePlacement[counter] = fen[i];
				counter += 1;
			}

			
		}
		else if (not turnDone) {
			if (fen[i] == ' ') {
				turnDone = true;
			}
			else {
				playerTurn = fen[i];
			}

		}
		else if (not castlingDone) {
			if (fen[i] == ' ') {
				castlingDone = true;
				counter = 0;
			}
			else {
				castlingAbility[counter] = fen[i];
				counter += 1;
			}
		}
		else if (not enPassantDone) {
			if (fen[i] == ' ') {
				enPassantDone = true;
				counter = 0;
			}
			else {
				enPassantTarget[counter] = fen[i];
				counter += 1;
			}
		}
		else if (not halfmoveDone) {
			if (fen[i] == ' ') {
				halfmoveDone = true;
				counter = 0;
			}
			else {
				halfmoveClock[counter] = fen[i];
				counter += 1;
			}
		}
		else{
			fullmoveClock[counter] = fen[i];
			counter += 1;
		}
	}


}

void Board::fenDisplay(SDL_Renderer* renderer, char fen[])
{

	// For the first part of the 
	int currentRow = 0;
	int currentColumn = 0;
	for (int i = 0; i < strlen(fen); i++) {

		if (isdigit(fen[i])) {
			currentColumn = currentColumn + atoi(&fen[i]);
		}
		else if (fen[i] == '/') {
			currentRow += 1;
			currentColumn = 0;
		}
		else if (fen[i] == ' ') {
			return;
		} 
		else {
			switch (fen[i]) {
			case('r'):
			{
				//Piece::drawPeice(renderer, currentRow, currentColumn, BLACK | ROOK);
				Piece blackRook = { renderer, BLACK | ROOK, currentRow,currentColumn };
				piecesOnBoard[currentRow][currentColumn] = &blackRook;
			}
				break;

			case('n'):
			{
				//Piece::drawPeice(renderer, currentRow, currentColumn, BLACK | KNIGHT);
				Piece blackKnight = { renderer, BLACK | KNIGHT, currentRow,currentColumn };
				piecesOnBoard[currentRow][currentColumn] = &blackKnight;
			}
				break;
			case('b'):
				
			{	
				//Piece::drawPeice(renderer, currentRow, currentColumn, BLACK | BISHOP);
				Piece blackBishop = { renderer, BLACK | BISHOP, currentRow,currentColumn }; 
				piecesOnBoard[currentRow][currentColumn] = &blackBishop;
			}
				break;
			case('q'):
			{
				//Piece::drawPeice(renderer, currentRow, currentColumn, BLACK | QUEEN);
				Piece blackQueen = { renderer, BLACK | QUEEN, currentRow,currentColumn };
				piecesOnBoard[currentRow][currentColumn] = &blackQueen;
			}
				break;
			case('k'): 
			{
				//Piece::drawPeice(renderer, currentRow, currentColumn, BLACK | KING);
				Piece blackKing = { renderer, BLACK | KING, currentRow,currentColumn };
				piecesOnBoard[currentRow][currentColumn] = &blackKing;
			}
				break;
			case('p'):
			{
				//Piece::drawPeice(renderer, currentRow, currentColumn, BLACK | PAWN);
				Piece blackPawn = { renderer, BLACK | PAWN, currentRow,currentColumn };
				piecesOnBoard[currentRow][currentColumn] = &blackPawn;
			}
				break;
			case('R'):
			{
				//Piece::drawPeice(renderer, currentRow, currentColumn, WHITE | ROOK);
				Piece whiteRook = { renderer, WHITE | ROOK, currentRow,currentColumn };
				piecesOnBoard[currentRow][currentColumn] = &whiteRook;
			}
				break;
			case('N'):
			{
				//Piece::drawPeice(renderer, currentRow, currentColumn, WHITE | KNIGHT);
				Piece whiteKnight = { renderer, WHITE | KNIGHT, currentRow,currentColumn };
				piecesOnBoard[currentRow][currentColumn] = &whiteKnight;
			}
				break;
			case('B'):
			{
				//Piece::drawPeice(renderer, currentRow, currentColumn, WHITE | BISHOP);
				Piece whiteBishop = { renderer, WHITE | BISHOP, currentRow,currentColumn };
				piecesOnBoard[currentRow][currentColumn] = &whiteBishop;
			}
				break;
			case('Q'):
			{
				//Piece::drawPeice(renderer, currentRow, currentColumn, WHITE | QUEEN);
				Piece whiteQueen = { renderer, WHITE | QUEEN, currentRow,currentColumn };
				piecesOnBoard[currentRow][currentColumn] = &whiteQueen;
			}
				break;
			case('K'):
			{
				//Piece::drawPeice(renderer, currentRow, currentColumn, WHITE | KING);
				Piece whiteKing = { renderer, WHITE | KING, currentRow,currentColumn };
				piecesOnBoard[currentRow][currentColumn] = &whiteKing;
			}
				break;
			case('P'):
			{
				//Piece::drawPeice(renderer, currentRow, currentColumn, WHITE | PAWN);
				Piece whitePawn = { renderer, WHITE | PAWN, currentRow,currentColumn };
				piecesOnBoard[currentRow][currentColumn] = &whitePawn;
			}
				break;
			}
			currentColumn += 1;
		}
		
	}

}


